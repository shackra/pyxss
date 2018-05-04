"""Uses ASCII art to graph your activity based on idle time.  The output will
be smoothed."""

import time
import xss
last = 0

def draw_idle():
    global last
    info = xss.get_info()
    seconds = info.idle
    seconds = min(100, seconds)
    movavg = (0.05 * seconds) + (0.95 * last)
    
    last = min(80, movavg)
    opposite = 80 - int(last)
    print(opposite, '*' * opposite)

while 1:
    draw_idle()
    time.sleep(0.1)
