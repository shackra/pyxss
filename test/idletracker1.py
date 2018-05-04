import time, sys
# this is a simple test of IdleTracker and XSSTracker

last_arg = sys.argv[-1]
try:
    threshold = int(last_arg)
except ValueError:
    threshold = None

if threshold:
    from xss import IdleTracker
    print("Using IdleTracker, threshold=%dms" % threshold)
    tracker = IdleTracker(idle_threshold=threshold)
else:
    from xss import XSSTracker
    print("Using XSSTracker")
    tracker = XSSTracker()

while 1:
    info = tracker.check_idle()
    print(time.asctime(), end=' ') 
    print("Change: %s, suggested wait time: %s, idle time: %s" % info)
    wait_time = info[1] / 1000.0
    time.sleep(wait_time)
