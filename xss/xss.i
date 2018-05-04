/* Python XScreenSaver access: lets you access some of the XScreenSaver
   functionality in Python.  Note that is my first SWIGged module and also
   that I know almost nothing about X11 programming.

   Also, there's nothing Python-specific in here.  If someone wants to use
   SWIG to make modules for other languages, it should be very easy.

   Hacked together by David McClosky  (dmcc@bigasterisk.com)
   Made with help from Drew Perttula (drewp@bigasterisk.com)
   
   ChangeLog:
   - Reworked on 4.3.2003 to work better with updated SWIG and to use
     crossplatform exceptions.
   - Started sometime around 9.22.2002 */

%module xss

%{
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/scrnsaver.h>
%}

/* from X11/extensions/scrnsaver.h */
typedef struct {
    Window  window;	    /* screen saver window - may not exist */
    int	    state;	    /* ScreenSaverOff, ScreenSaverOn, ScreenSaverDisabled*/
    int	    kind;	    /* ScreenSaverBlanked, ...Internal, ...External */
    unsigned long    til_or_since;   /* time til or since screen saver */
    unsigned long    idle;	    /* total time since last user input */
    unsigned long   eventMask; /* currently selected events for this client */
} XScreenSaverInfo;

/* from X11/extensions/saver.h */
#define ScreenSaverOff          0
#define ScreenSaverOn           1
#define ScreenSaverCycle        2
#define ScreenSaverDisabled     3

#define ScreenSaverBlanked      0
#define ScreenSaverInternal     1
#define ScreenSaverExternal     2

%include "exception.i"
%exception get_info {
  $action
  if (!result) {
     SWIG_exception(SWIG_RuntimeError, "Couldn't query screensaver extension.");
     return NULL;
  }
}

%inline %{

int event_base, error_base;
static XScreenSaverInfo *mit_info;

Display *dpy;
int screen;
Window root;

XScreenSaverInfo* get_info(void) {
    if (XScreenSaverQueryExtension(dpy, &event_base, &error_base)) {
            mit_info = XScreenSaverAllocInfo();
            XScreenSaverQueryInfo(dpy, root, mit_info);
            return mit_info;
    } else {
        return NULL;
    }
}

%} // end %inline

%init %{
    dpy = XOpenDisplay("");
    screen = DefaultScreen(dpy);
    root = RootWindow(dpy, screen);
%}

// vi:syntax=c
