from .xss import *

__version__ = "2.1"
__author__ = "David McClosky (dmcc@bigaterisk.com)"
__credits__ = "Made with help from Drew Perttula (drewp@bigasterisk.com)"
__doc__ = """Python interface to XScreenSaver information

PyXSS is a Pythonic interface to the XScreenSaverInfo struct.  It can
tell you the following bits of information (and a bit more):
    - Current X idle time in milliseconds
    - Whether the screensaver is currently on, off, or disabled
    - How many milliseconds the screensaver has been on for, or how many it
      will take for it to be activated.

It cannot actually activate or deactivate the screensaver.
(You can do that by typing 'xset s on' and then 'xset s [time]' where time
is the time in seconds that the screensaver should activate in.

Note that this module is not an interface to JWZ's fine screensaver
package, but the extension in XFree86 instead.

Example
=======
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

xss.get_info() returns an xss.XScreenSaverInfo object.  The object is
the SWIGged version of this struct:

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

class IdleTracker:
    """Keeps track of idle times, screensaver state, and tells
    you when you to querying it for the next idle time.  All times
    are in milliseconds.  IdleTracker indicates a change in state when
    your idle time exceeds a certain threshold.  See also XSSTracker."""
    def __init__(self, when_idle_wait=5000, when_disabled_wait=120000,
        idle_threshold=60000):
        """when_idle_wait is the interval at which you should poll when
        you are already idle.  when_disabled_wait is how often you should
        poll if information is unavailable (default: 2 minutes).  
        idle_threshold is the number of seconds of idle time to constitute
        being idle."""
        self.when_idle_wait = when_idle_wait
        self.idle_threshold = idle_threshold
        # we start with a bogus last_state.  this way, the first call to
        # check_idle will report whether we are idle or not.  all subsequent
        # calls will only tell you if the screensaver state has changed
        self.last_state = None
    def check_idle(self):
        """Returns a tuple:
        (state_change, suggested_time_till_next_check, idle_time)
        
        suggested_time_till_next_check and idle_time is in milliseconds.
        state_change is one of:
            None - No change in state
            "idle" - user is idle (idle time is greater than idle threshold)
            "unidle" - user is not idle (idle time is less than idle threshold)
            "disabled" - idle time not available

        Note that "disabled" will be returned every time there is an error."""
        try:
            self.info = get_info()
        except RuntimeError: # XSS can raise a RuntimeError if the
                             # XSS extension cannot be found.
            return ("disabled", self.when_disabled_wait, 0)

        idle = self.info.idle

        if idle > self.idle_threshold: # if we meet the threshold for being
                                       # idle, we are now idle
            current_state = 'idle'
            # we use the standard polling interval
            wait_time = self.when_idle_wait
        else:                          # otherwise, we are not idle
            current_state = 'unidle'
            # wait time is however long it will take for us to go over the 
            # idle threshold
            wait_time = self.idle_threshold - idle

        # check to see if our new state is actually a change
        change = None
        if self.last_state != current_state:
            change = current_state

        self.last_state = current_state
        return (change, wait_time, self.info.idle)

class XSSTracker:
    """Keeps track of idle times, screensaver state, and tells you
    when you to querying it for the next idle time.  All times are
    in milliseconds.  XSSTracker indicates a change in state when your
    screensaver activates.  See also IdleTracker."""
    def __init__(self, when_idle_wait=5000, when_disabled_wait=120000):
        """when_idle_wait is the interval at which you should poll when
        you are already idle.  when_disabled_wait is how often you should
        poll if the screensaver is disabled and you are using XSS for
        your idle threshold.
        
        If you set idle_threshold to 'xss', it will say that your
        threshold for becoming idle is whenever the screensaver activates.
        If you don't use the XScreenSaver extension or otherwise want
        a different idle threshold, you can specify it in milliseconds."""
        self.when_idle_wait = when_idle_wait
        self.when_disabled_wait = when_disabled_wait
        # we start by assuming the screen saver is disabled.  this way, the
        # first call to check_idle will report whether the screensaver is
        # active.  all subsequent calls will only tell you if the screensaver
        # state has changed
        self.last_state = xss.ScreenSaverDisabled
    def check_idle(self):
        """Returns a tuple:
        (state_change, suggested_time_till_next_check, idle_time)
        
        suggested_time_till_next_check and idle_time is in milliseconds.
        state_change is one of:
            None - No change in state
            "idle" - screensaver has turned on since user is now idle
            "unidle" - screensaver has turned off since user is no longer idle
            "disabled" - screensaver is disabled or extension not present

        Note that if the screensaver is disabled, it will return "disabled"
        every time."""
        try:
            self.info = get_info()
        except RuntimeError: # XSS can raise a RuntimeError if the
                             # XSS extension cannot be found.
            return ("disabled", self.when_disabled_wait, 0)

        state = self.info.state

        # if we're disabled, we tell them that. the polling interval for
        # disabledness is when_disabled_wait, which defaults to 2 minutes.
        if state == ScreenSaverDisabled:
            self.last_state = state
            return ("disabled", self.when_disabled_wait, 0)
        
        # wait_time is how long they should wait before polling again.
        if state == ScreenSaverOff:
            # if the screen saver is off, til_or_since will tell us
            # how long it will take to be activated (whether it will
            # be activated depends on whether the user is idle for that
            # period of time)
            wait_time = self.info.til_or_since
        else:
            # otherwise, the screensaver is on.  we don't when we will
            # become unidle, but the when_idle_wait tells us the poll
            # interval (default is 5 seconds)
            wait_time = self.when_idle_wait

        # change is whether or not we have changed.  if we have, we use
        # a string to describe the change
        if state != self.last_state:
            if state == ScreenSaverOff: # if we've changed from On to Off
                                            # they're not idle anymore
                change = 'unidle'
            else:
                change = 'idle' # if we've changed from Off to On, they've gone
                                # idle
        else: # otherwise, they haven't changed state
            change = None

        self.last_state = state
        return (change, wait_time, self.info.idle)

if __name__ == "__main__":
    # this demo shows how you might write a simple poller
    import time
    i = IdleTracker(idle_threshold=5000)
    while 1:
        info = i.check_idle()
        print(time.asctime(), info, end=' ')
        # don't poll more often than 2 seconds
        wait_time = max(info[1] / 1000, 2) 
        print("wait:", wait_time)
        time.sleep(wait_time)
