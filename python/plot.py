#!/usr/bin/python
import sys, math, random, time
import matplotlib.pyplot as plt
from sys import stdin
from collections import deque

def main(argv):
    #skip textual output
    text_lines = 0
    for _ in xrange(2):
        print "pipe says: " + str(stdin.readline().rstrip())

    plt.axis([0, 100, -0.5, 0.5])
    plt.ion()
    plt.grid(True)
    plt.show()

    x = deque();
    y = deque([], maxlen=10000); # iterable, maxlen

    _x = 0;
    while (True):
        try:
            _y = float(stdin.readline().rstrip())
            print _y
            plt.scatter(_x, _y)
            plt.draw()
            _x = (_x+1) % 100
        except KeyboardInterrupt:
            sys.stdout.flush()
            return -1

if __name__ == '__main__':
    main(sys.argv[1:])


