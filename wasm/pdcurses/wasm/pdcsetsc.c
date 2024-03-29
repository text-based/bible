/* Public Domain Curses */

/*man-start**************************************************************

  Name:                                                         pdcsetsc

  Synopsis:
        int PDC_set_blink(bool blinkon);
        void PDC_set_title(const char *title);

  Description:
        PDC_set_blink() toggles whether the A_BLINK attribute sets an
        actual blink mode (TRUE), or sets the background color to high
        intensity (FALSE). The default is platform-dependent (FALSE in
        most cases). It returns OK if it could set the state to match 
        the given parameter, ERR otherwise. Current platforms also 
        adjust the value of COLORS according to this function -- 16 for 
        FALSE, and 8 for TRUE.

        PDC_set_title() sets the title of the window in which the curses
        program is running. This function may not do anything on some
        platforms. (Currently it only works in Win32 and X11.)

  Portability                                X/Open    BSD    SYS V
        PDC_set_blink                           -       -       -
        PDC_set_title                           -       -       -

**man-end****************************************************************/


#include <curspriv.h>

#include <emscripten.h>

EM_JS(void, js_curses_curs_on, (void));
EM_JS(void, js_curses_curs_off, (void));


/*
Called from curs_set(). Changes the appearance of the cursor -- 0 turns
it off, 1 is normal (the terminal's default, if applicable, as
determined by SP->orig_cursor), and 2 is high visibility. The exact
appearance of these modes is not specified.
*/
int PDC_curs_set(int visibility)
{
    int ret_vis;

    PDC_LOG(("PDC_curs_set() - called: visibility=%d\n", visibility));

    ret_vis = SP->visibility;

    SP->visibility = visibility;

    if (visibility)
        js_curses_curs_on();

        // TODO
        // EM_ASM(term.cursorOn());
    else
        js_curses_curs_off();

        // TODO
        // EM_ASM(term.cursorOff());

    return ret_vis;
}

/*
Other functions
*/
void PDC_set_title(const char *title)
{
    PDC_LOG(("PDC_set_title() - called:<%s>\n", title));

//    SDL_WM_SetCaption(title, title);
}

int PDC_set_blink(bool blinkon)
{
    COLORS = 16;

    return blinkon ? ERR : OK;
}
