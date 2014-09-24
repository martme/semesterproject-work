#!/usr/bin/python
import sys
import matplotlib.pyplot as plt
import numpy as np
from pylab import *

def main(argv):
    #with open('samples/10k-20k_48kHz_w512.txt') as f:
    #with open('../samples/dumps/96kHz-24bit_whistle_w2048_transformed.dat') as f:
    #with open('../samples/dumps/96kHz-24bit_indiana_jones_whistle_w2048_transformed.dat') as f:
    #with open('../samples/dumps/96kHz-24bit_big_freq_range_w2048_transformed.dat') as f:
    with open('samples/dump.dat') as f:

        lines = [line.rstrip() for line in f]

    W = float(lines[0].rstrip(" "))     # window size
    Fs = float(lines[1].rstrip(" "))    # sample frequency


    Z = [ [ abs(float(z)) for z in line.split(" ")] for line in lines[2:] ]
    #Z = np.log10(Z)

    dt = W/Fs       # timestep
    df = Fs/W       # frequency step

    Y, X = np.mgrid[slice( 0, len(Z) * dt, dt ),
                    slice( 0, len(Z[0]) * df, df )]

    color = colormap()
    z_min, z_max = np.abs(Z).min(), np.abs(Z).max()
    #z_min = 0
    #z_max = 20
    print "min: " + str(z_min)
    print "max: " + str(z_max)

    plt.pcolor(np.array(X), np.array(Y), np.array(Z), cmap=color, vmin=z_min, vmax=z_max) #cmap = 'binary'
    plt.axis([X.min(), X.max(), Y.min(), Y.max()])
    plt.show()

def colormap():
    import matplotlib as mpl
    cmap = mpl.colors.ListedColormap([(0.0, x, 0.0, 1) for x in np.linspace(0, 1, 255)])
    return cmap


if __name__ == '__main__':
    #colormap()
    main(sys.argv[1:])


