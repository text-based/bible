/* Public Domain Curses */
/*man-start**************************************************************

  Name:                                                         clipboard

  Synopsis:
        int PDC_getclipboard(char **contents, long *length);
        int PDC_setclipboard(const char *contents, long length);
        int PDC_freeclipboard(char *contents);
        int PDC_clearclipboard(void);

  Description:
        PDC_getclipboard() gets the textual contents of the system's 
        clipboard. This function returns the contents of the clipboard 
        in the contents argument. It is the responsibilitiy of the 
        caller to free the memory returned, via PDC_freeclipboard().
        The length of the clipboard contents is returned in the length 
        argument.

        PDC_setclipboard copies the supplied text into the system's 
        clipboard, emptying the clipboard prior to the copy.

        PDC_clearclipboard() clears the internal clipboard.

  Return Values:
        indicator of success/failure of call.
        PDC_CLIP_SUCCESS        the call was successful
        PDC_CLIP_MEMORY_ERROR   unable to allocate sufficient memory for 
                                the clipboard contents
        PDC_CLIP_EMPTY          the clipboard contains no text
        PDC_CLIP_ACCESS_ERROR   no clipboard support

  Portability                                X/Open    BSD    SYS V
        PDC_getclipboard                        -       -       -
        PDC_setclipboard                        -       -       -
        PDC_freeclipboard                       -       -       -
        PDC_clearclipboard                      -       -       -

**man-end****************************************************************/

#include <curspriv.h>

#include <stdlib.h>


int PDC_getclipboard(char **contents, long *length)
{
    PDC_LOG(("PDC_getclipboard() - called\n"));

    /* FIXME */
    return PDC_CLIP_ACCESS_ERROR;
}

int PDC_setclipboard(const char *contents, long length)
{
    PDC_LOG(("PDC_setclipboard() - called\n"));

    /* FIXME */
    return PDC_CLIP_ACCESS_ERROR;
}

int PDC_freeclipboard(char *contents)
{
    PDC_LOG(("PDC_freeclipboard() - called\n"));

    /* FIXME */
    return PDC_CLIP_ACCESS_ERROR;
}

int PDC_clearclipboard(void)
{
    PDC_LOG(("PDC_clearclipboard() - called\n"));

    return PDC_CLIP_ACCESS_ERROR;
}
