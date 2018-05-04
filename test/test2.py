"""Reports every 5 seconds about your idle time and the state of the screensaver."""

import xss, time

while 1:
    info = xss.get_info()
    print(time.asctime(), "Idle: %sms" % info.idle, end=' ') 
    if info.state == xss.ScreenSaverOn:
        print("(screensaver on for %sms)" % info.til_or_since)
    elif info.state == xss.ScreenSaverOff:
        print("(will turn on screensaver in %sms)" % info.til_or_since)
    elif info.state == xss.ScreenSaverCycle:
        print("(screensaver cycling)")
    else:
        print("(screensaver disabled)")
    time.sleep(5)
