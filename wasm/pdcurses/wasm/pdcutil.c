/* Public Domain Curses */

#include <curspriv.h>

#include <emscripten.h>

EM_JS(void, await_timeout, (int ms));


/*
Emits a short audible beep. If this is not possible on your platform,
you must set SP->audible to FALSE during initialization (i.e., from
PDC_scr_open() -- not here); otherwise, set it to TRUE. This function is
called from beep().
*/
void PDC_beep(void)
{
    PDC_LOG(("PDC_beep() - called\n"));
    /* FIXME */
}

/*
This is the core delay routine, called by napms(). It pauses for about
(the X/Open spec says "at least") ms milliseconds, then returns. High
degrees of accuracy and precision are not expected (though desirable, if
you can achieve them). More important is that this function gives back
the process' time slice to the OS, so that PDCurses idles at low CPU
usage
*/
void PDC_napms(int ms)
{
    await_timeout(ms);

    PDC_LOG(("PDC_napms() - called: ms=%d\n", ms));
}

/*
Returns a short string describing the platform, such as "DOS" or "X11".
This is used by longname(). It must be no more than 100 characters; it
should be much, much shorter (existing platforms use no more than 5).
*/
const char *PDC_sysname(void)
{
    return "wasm";
}
