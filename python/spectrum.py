#!/usr/bin/python
from utility import pcm2float

import sys
import matplotlib.pyplot as plt
import numpy as np
import scipy.io.wavfile as wav
import scipy.signal as signal
import pylab


def plot_spectrum(W, Fs, Z):

    dt = float(W)/(Fs)   # timestep --> only progress half a window at the time
    df = float(Fs)/W       # frequency step

    print dt
    print df


    Y, X = np.mgrid[slice( 0, len(Z) * dt, dt ),
                    slice( 0, len(Z[0]) * df, df )]


    Z = np.multiply(np.log10(Z), -1) # convert to dB

    #cmap = plt.get_cmap("seismic");
    cmap = colormap()
    z_min, z_max = np.min(Z), np.max(Z)/2
    print z_min
    print z_max
    #z_max = 50*np.median(Z)
    plt.pcolor(np.array(X), np.array(Y), np.array(Z), cmap=cmap, vmin=z_min, vmax=z_max) #cmap = 'binary'
    plt.axis([X.min(), X.max(), Y.min(), Y.max()])
    plt.show()



def read_wav(argv):
    if (len(argv) != 2):
        print "Usage: spectrum.py <sndfile.wav> <window size>"
        return

    filename = argv[0]
    W = int(argv[1])


    (Fs, samples) = wav.read(filename)
    print ("sampling rate = {} Hz, length = {} samples, channels = {}".format(Fs, *samples.shape))
    samples = normalize(samples)

    Z = []
    for o in xrange(len(samples) / W):
        f, Pxx_den = signal.periodogram([ np.mean(samples[o+i]) for i in xrange(W) ], Fs) #power density spectrum
        Z.append(Pxx_den)

    print len(Z)
    print len(Z[0])
    plot_spectrum(W, Fs, Z)


    #x = Z[100]
    #plt.semilogy(f, Pxx_den) # logarithmic axis
    #plt.ylim([1e-7, 1e2])
    #plt.xlabel("frequency [Hz]")
    #plt.ylabel("PSD, [V**2/Hz]")
    #plt.show()


def normalize(samples):
    return pcm2float(samples, "float32")


def colormap():
    import matplotlib as mpl
    cmap = mpl.colors.ListedColormap([(0.0, x, 0.0, 1) for x in np.linspace(0, 1, 255)])
    return cmap


if __name__ == '__main__':
    #colormap()
    #main(sys.argv[1:])
    read_wav(sys.argv[1:])



