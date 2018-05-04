## What is PyXSS?
PyXSS is a Pythonic interface to the XScreenSaver info.  It can tell you the following bits of
information (and a little more):

- Current X idle time in milliseconds
- Whether the screensaver is currently on, off, or disabled
- How many milliseconds the screensaver has been on for, or how many it will take for it to be activated.

## Install
Type `python setup.py install` as root.  If SWIG is found, it will be used.  You need a somewhat
recent version of SWIG (1.3.15 or later should be fine).  ~~However, there's nothing wrong with
using the pre-SWIGged stuff. (Should SWIG break, you should disable the check for SWIG in setup.py
to force usage of the included SWIG-generated files.~~

## Example

    >>> import xss
    >>> info = xss.get_info()
    >>> print info.idle
    10
    >>> print info.state
    0
    >>> print info.state == xss.ScreenSaverDisabled
    0
    >>> print info.state == xss.ScreenSaverOff
    1

`xss.get_info()` returns an `xss.XScreenSaverInfo` object.  The object is the SWIGged version of
this struct:

    typedef struct {
        Window  window;     /* screen saver window - may not exist */
        int     state;      /* ScreenSaverOff, ScreenSaverOn, ScreenSaverDisabled*/
        int     kind;       /* ScreenSaverBlanked, ...Internal, ...External */
        unsigned long    til_or_since;   /* time til or since screen saver */
        unsigned long    idle;      /* total time since last user input */
        unsigned long   eventMask; /* currently selected events for this client */
    } XScreenSaverInfo;

The window attribute will be useless.  For state and kind, you can test the values against their
named values (i.e. `print(info.state == xss.ScreenSaverOff)`)

More examples can be seen in the `test/` directory.

## About XScreenSaver
The XScreenSaver that I'm referring to in this document is the X11
extensions, not the screensaver package by Jamie Zawinski.  I believe
that Jamie Zawinski's XScreenSaver uses the extension, though.

Idle time should always be available, but if the X11 screensaver is
disabled (perhaps with 'xset s off', you won't have any interesting values
for til_or_since and state will be ScreenSaverDisabled.  You can remedy
this by turning on the screensaver with 'xset s on' and 'xset s [timeout]'

## Author
David McClosky (dmcc@bigasterisk.com)
Webpage: http://bebop.bigasterisk.com

## Thanks To
Lots of SWIG help and debugging from Drew Perttula (drewp@bigasterisk.com)

## License
GNU Public License, version 2
