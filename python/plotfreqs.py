#!/usr/bin/python

#inspired by http://glowingpython.blogspot.no/2011/08/how-to-plot-frequency-spectrum-with.html
import sys
from numpy import sin, linspace, pi
from pylab import plot, show, title, xlabel, ylabel, subplot
from scipy import fft, arange

def plotSpectrum(y,Fs):
    # Plots a Single-Sided Amplitude Spectrum of y(t)
    n = len(y) # length of the signal
    k = arange(n)
    T = n/Fs
    frq = k/T # two sides frequency range
    frq = frq[range(n/2)] # one side frequency range

    Y = fft(y)/n # fft computing and normalization
    Y = Y[range(n/2)]


    print Y
    plot(frq,abs(Y),'r') # plotting the spectrum
    xlabel('Freq (Hz)')
    ylabel('|Y(freq)|')

def plot_freqs(Y, Fs, W):
    step = Fs/W
    X = [i*step for i in xrange(len(Y))]

    plot (X, Y, 'r')
    xlabel("Freq (Hz)")
    ylabel("Something")

def main(argv):
    Fs = 44100.0    # SAMPLE_RATE
    W = 2048.0      # FRAMES_PER_BUFFER
    Y = [float(y) for y in sys.stdin.readline().rstrip().split(" ")]
    plot_freqs(Y, Fs, W)
    show()

if __name__ == '__main__':
    main(sys.argv[1:])


