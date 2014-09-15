#!/usr/bin/python
import sys
import matplotlib.pyplot as plt
import numpy as np
from pylab import *

def main(argv):
    with open('sample_w512.txt') as f:
        lines = [line.rstrip() for line in f]

    Z = [ [float(z) for z in line.split(" ")] for line in lines ]

    W = 512.0      # window size    (is 2048.0 in raw.txt and sample.txt)
    Fs = 44100.0    # sample frequency

    dt = W/Fs       # timestep
    df = Fs/W       # frequency step

    Y, X = np.mgrid[slice( 0, len(Z) * dt, dt ),
                    slice( 0, len(Z[0]) * df, df )]


    color = colormap()
    z_min, z_max = np.abs(Z).min(), np.abs(Z).max()
    #z_min = 0
    z_max = 100
    print "min: " + str(z_min)
    print "max: " + str(z_max)
    plt.pcolor(X, Y, Z, cmap=color, vmin=z_min, vmax=z_max) #cmap = 'binary'
    plt.axis([X.min(), X.max(), Y.min(), Y.max()])
    plt.show()

def colormap():
    import matplotlib as mpl
    cmap = mpl.colors.ListedColormap([(0.0, x, 0.0, 0) for x in np.linspace(0, 1, 255)])
    return cmap


if __name__ == '__main__':
    #colormap()
    print np.linspace(1, 0, 10)
    main(sys.argv[1:])


