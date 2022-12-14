import { Terminal } from 'xterm';
import { FitAddon } from 'xterm-addon-fit';
import { curses } from './curses.js';
import * as Asyncify from 'asyncify-wasm';

export const loadWasm = (domElement, {altdata}) => {
  const ctx = {};

  const utf8Encode = new TextEncoder();
  const utf8Decoder = new TextDecoder();
  ctx.altdata = Array.from(utf8Encode.encode(altdata));

  const createTerminal = () => {
    const fitAddon = new FitAddon();
    const terminal = new Terminal({ scrollback: 0 });
  
    // On container resize terminal will "fit"
    terminal.loadAddon(fitAddon);
    const onWindowSize = () => {
      fitAddon.fit();
    }
    window.addEventListener('resize', onWindowSize, false);
  
    terminal.open(domElement);
    onWindowSize();
  
    return terminal;
  }
  

  var asmLibraryArg = {
    ...curses(ctx),
    proc_exit: (status) => {
      throw new Error("Exit with status: " + status);
    },
    fd_close: () => {},
    fd_write: (fd, iovs, iovsLen, nread) => {
      console.log("fd_write", {fd, iovs, iovsLen, nread});
      if(fd !== 2) {
        throw new Error('fd_write: fd != stderr');
      }
    
      const view = new DataView(ctx.buffer);
      view.setUint32(nread, 0, true);
  
      // create a UInt8Array for each buffer
      const buffers = Array.from({ length: iovsLen }, (_, i) => {
          const ptr = iovs + i * 8;
          const buf = view.getUint32(ptr, true);
          const bufLen = view.getUint32(ptr + 4, true);
  
          return new Uint8Array(ctx.buffer, buf, bufLen);
      });

      // print each buffer
      buffers.forEach(buf => {
        if (buf.length) {
          console.log("⛑️ ", utf8Decoder.decode(buf));
        }
        view.setUint32(nread, view.getUint32(nread, true) + buf.length, true);
      });

      return 1; // return 1 for success
    },
    environ_sizes_get: () => {},
    environ_get: () => {},
    fd_seek: () => {},
    fd_read: (fd, iovs, iovsLen, nread) => {
      // console.log({fd, iovs, iovsLen, nread})
      // only care about 'stdin'
      if(fd !== 0)
        throw new Error('fd_read: fd != 0');

      const view = new DataView(ctx.buffer);
      view.setUint32(nread, 0, true);
  
      // create a UInt8Array for each buffer
      const buffers = Array.from({ length: iovsLen }, (_, i) => {
          const    ptr = iovs + i * 8;
          const    buf = view.getUint32(ptr, true);
          const bufLen = view.getUint32(ptr + 4, true);
  
          // console.log({ptr, buf, bufLen})
          return new Uint8Array(ctx.buffer, buf, bufLen);
      });

      // fill each buffer with altdata
      buffers.forEach(buf => {
        let i;
        for (i = 0; i<buf.length; i++) {
          if (ctx.altdata.length === 0) {
            break;
          }
          buf[i] = ctx.altdata.shift();
        }
        view.setUint32(nread, view.getUint32(nread, true) + i, true);
      });
      
      return 0;
    },
  };
  
  var importObject = {
    "env": asmLibraryArg,
    "wasi_snapshot_preview1": asmLibraryArg
  };
  
  return fetch("./wasm/bible.wasm?t="+(new Date()).getTime())
    .then((response) => response.arrayBuffer())
    .then((bytes) => Asyncify.instantiate(bytes, importObject))

    .then((module) => {
      ctx.buffer = module.instance.exports.memory.buffer;
      ctx.term = createTerminal();
      ctx.term.focus();
      ctx.inputchar = null;

      ctx.term.onResize(({ cols, rows }) => {
        ctx.term.cols = cols;
        ctx.term.rows = rows;
      });

      ctx.term.onKey((keyEvt) => {
        const { key } = keyEvt;
        const chars = new TextEncoder().encode(key);
        chars.forEach(c => {
          ctx.inputchar = c;
        });
      });

      module.instance.exports.wasm_init();
    });
}

