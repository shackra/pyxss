"""A Tix widget which tells and shows you how much time you have left before the
screensaver will activate."""

import xss
from tkinter.tix import *

class IdleMeter(Meter):
    def __init__(self, master, *args, **kw):
        Meter.__init__(self, master, *args, **kw)
        self.master = master
        self.after(0, self.update_xss)
    def update_xss(self):
        self.info = xss.get_info()
        if self.info.state == xss.ScreenSaverOff:
            total = float(self.info.idle + self.info.til_or_since)
            self.configure(value=self.info.idle / total,
                text="%.1fs left, idle for %.1fs" % \
                     (self.info.til_or_since / 1000.0, 
                      self.info.idle / 1000.0))
            self.fade()
        self.after(100, self.update_xss)
    def fade(self):
        self['fillcolor'] = colorfade(blue, red, float(self['value']))

def colorfade(low, high, percent):
    """Given two functions in #ABCDEF notation and a percent between 0
    and 1, this will calculate an intermediate color."""
    out = [int(l + percent * (h - l)) for h, l in zip(high,low)]
    col = "#%02X%02X%02X" % tuple(out)
    return col

def colortotuple(anytkobj, colorname):
    """Pass any tk object and a color name, like "yellow", returns a
    color tuple suitable for colorfade."""
    rgb = anytkobj.winfo_rgb(colorname)
    return [v / 256 for v in rgb]

info_check = xss.get_info()
if info_check.state == xss.ScreenSaverDisabled:
    print("Your screensaver is disabled.  Use 'xset s on' to enable it.")
    import sys
    sys.exit()

root = Tk()
blue = colortotuple(root, "blue")
red = colortotuple(root, "red")
root.wm_geometry("175x25")
meter = IdleMeter(root)
meter.pack(fill=BOTH, expand=1)
mainloop()
