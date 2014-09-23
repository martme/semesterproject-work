#!/usr/bin/python
import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

from sys import stdin
from time import sleep
from collections import deque


# plot class
class AnalogPlot:
    """
        Plot real time data
    """
    def __init__(self, maxlen):
        self.ctr = 0
        self.maxlen = maxlen;
        self.ax = deque(range(maxlen), maxlen=maxlen)
        self.ay = deque([0]*maxlen, maxlen=maxlen)

    def add(self, x, y):
        self.ax.append(x)
        self.ay.append(y)

    def update(self, frame, a0, a1):
        try:
            _y = (float)(stdin.readline().rstrip())
            _x = self.inc_ctr()
            self.add(_x, _y)
            a0.set_data(range(self.maxlen), self.ax)
            a1.set_data(range(self.maxlen), self.ay)
        except KeyboardInterrupt:
            print("\nExiting")
            sys.exit(0)
        except ValueError:
            print("Skipping line")

        return a0


    def inc_ctr(self):
        self.ctr = self.ctr + 1
        return self.ctr

    def debug(self):
        print self.ay

def main():
    plot = AnalogPlot(100)
    fig = plt.figure()
    ax = plt.axes(xlim=(0, 100), ylim=(-0.01,0.01))
    a0, = ax.plot([], [])
    a1, = ax.plot([], [])
    anim = animation.FuncAnimation(fig, plot.update, fargs=(a0, a1),interval=1)
    plt.show()


if __name__ == '__main__':
    main()
