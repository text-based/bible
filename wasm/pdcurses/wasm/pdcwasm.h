#pragma once

#include <curspriv.h>

void js_curses_gotoyx(const int row, const int col);
int js_curses_get_cursor_mode(void);
int js_curses_check_key(void);
int js_curses_get_key(void);
int js_curses_get_rows(void);
int js_curses_get_cols(void);
void js_curses_flushinp(void);
void js_curses_scr_close(void);
void js_curses_scr_open(void);
void js_curses_curs_on(void);
void js_curses_curs_off(void);
void js_curses_simulateinfiniteloop_error(void);
void js_curses_resize_screen(const int nrows, const int ncols);
void js_curses_transform_line(int lineno, int x, int len, const void *srcp, short fg, short bg);
void await_timeout(int ms);
void browser_log(void* msg);
