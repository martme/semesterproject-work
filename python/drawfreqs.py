#!/usr/bin/python
import sys
import matplotlib.pyplot as plt
import numpy as np
from pylab import *

def main(argv):

    W = float(sys.stdin.readline().rstrip())
    Fs = float(sys.stdin.readline().rstrip())
    lines = [line.rstrip() for line in sys.stdin]
    Z = [ [ (float(z)) for z in line.split(" ")] for line in lines[2:] ]
    #Z = np.multiply(np.log10(Z), 20) # convert to dB

    print "W:\t%f\nFs:\t%f" % (W, Fs)

    dt = W/(2*Fs)   # timestep --> only progress half a window at the time
    df = Fs/W       # frequency step

    Y, X = np.mgrid[slice( 0, len(Z) * dt, dt ),
                    slice( 0, len(Z[0]) * df, df )]

    #color = colormap()
    color = plt.get_cmap("seismic");
    #Z = np.abs(Z)
    z_min, z_max = np.abs(Z).min(), np.abs(Z).max()
    #z_min = 0
    #z_max = .0001
    print "min:\t%f" % z_min
    print "max:\t%f" % z_max
    print "mean:\t%f" % np.mean(Z)
    print "std:\t%f" % np.std(Z)
    print "median:\t%f" % np.median(Z)

    #z_max = np.mean(Z)+np.std(Z)
    z_max = 50*np.median(Z)
    #z_max = np.mean(Z)
    #z_min = Z.min()/5
    #z_max = 0

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


