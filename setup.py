#!/usr/bin/env python

import os
import sys
from distutils.core import Extension, setup
from distutils.sysconfig import get_python_lib


"""The purpose of this module was to let Python access X11 idle times.
It does little more than that:

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

Other attributes are:

typedef struct {
    Window  window;     /* screen saver window - may not exist */
    int     state;      /* ScreenSaverOff, ScreenSaverOn, ScreenSaverDisabled*/
    int     kind;       /* ScreenSaverBlanked, ...Internal, ...External */
    unsigned long    til_or_since;   /* time til or since screen saver */
    unsigned long    idle;      /* total time since last user input */
    unsigned long   eventMask; /* currently selected events for this client */
} XScreenSaverInfo;

The window attribute will be useless.  For state and kind, you can test the
values against their named values
(i.e. "print info.state == xss.ScreenSaverOff")

As of version 2.1, we now include IdleTracker and XSSTracker, which are
higher level interfaces.  Both keep track of the current idle time and tell
you whether the user became idle or unidle since the last poll, when the
next poll should take place, and the current idle time in milliseconds.
IdleTracker is based on some threshold for idle time, while XSSTracker
announces that the user is idle when the screensaver activates.  An example
poller can be found at the end of this file (xss/__init__.py)."""


def have_swig(print_config=1):
    """Returns whether SWIG can be found using the 'which' command"""
    if print_config: print("Checking for SWIG...", end=' ')

    # TODO: the following might not be too portable
    swig = os.popen('which swig', 'r')
    if print_config:
        # this prints the location of SWIG, removing the carriage return
        print(swig.read()[:-1])

    # if they have SWIG (return value of close() is exit code)
    return not swig.close()


print_config = 1
if sys.argv[-1] == 'setup.py':
    print("To install, run 'python setup.py install'")
    print_config = 0

if have_swig(print_config=print_config):
    extension_file = 'xss/xss.i'
else:
    # This project is so damn old that is better to use SWIG for the bindings
    # than trying to compile the included xss.c file.
    raise OSError("SWIG not installed, please install it and try again")

xss_module = Extension(
    name='xss', sources=[extension_file], libraries=['Xss', 'Xext'])

setup(
    name='PyXSS',
    version="2.1.1",
    description="Python Interface to XScreenSaver",
    long_description=__doc__,
    author="David McClosky",
    author_email="dmcc@bigasterisk.com",
    maintainer="Jorge Javier Araya Navarro",
    maintainer_email="jorge@esavara.cr",
    keywords=['X11', 'screensaver', 'XFree86', 'idle'],
    platforms=['POSIX/X11'],
    url="http://bebop.bigasterisk.com/python",
    license="GPLv2",
    packages=['xss'],
    ext_modules=[xss_module])
