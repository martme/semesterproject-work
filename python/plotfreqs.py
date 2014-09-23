#!/usr/bin/python

#inspired by http://glowingpython.blogspot.no/2011/08/how-to-plot-frequency-spectrum-with.html
import sys
from pylab import plot, show, title, xlabel, ylabel, subplot

def plot_freqs(Y, Fs, W):
    step = Fs/W
    X = [i*step for i in xrange(len(Y))]

    plot (X, Y, 'r')
    xlabel("Freq (Hz)")
    ylabel("Something")

def main(argv):
    Fs = 48000.0    # SAMPLE_RATE
    W = 2048.0      # FRAMES_PER_BUFFER  (is 2048.0 in raw.txt and sample.txt)
    with open("sample_w512_db.txt") as samples:
        #for _ in xrange(2400):
        #    samples.readline()
        Y = [float(y) for y in samples.readline().rstrip().split(" ")]
    plot_freqs(Y, Fs, W)
    show()

if __name__ == '__main__':
    main(sys.argv[1:])


