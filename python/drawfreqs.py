#!/usr/bin/python
import sys
import matplotlib.pyplot as plt
import numpy as np
from pylab import *

def main(argv):

    if (len(argv) > 0):
        foo = double(argv[0])
    else:
        foo = 50;

    W = float(sys.stdin.readline().rstrip())
    Fs = float(sys.stdin.readline().rstrip())
    lines = [line.rstrip() for line in sys.stdin]
    Z = [ [ (float(z)) for z in line.split(" ")] for line in lines[2:] ]
    #Z = np.multiply(np.log10(Z), 20) # convert to dB
    Z = np.log10(Z)
    print "W:\t%f\nFs:\t%f" % (W, Fs)

    dt = W/(2*Fs)   # timestep --> only progress half a window at the time
    df = Fs/W       # frequency step

    Y, X = np.mgrid[slice( 0, len(Z) * dt, dt ),
                    slice( 0, len(Z[0]) * df, df )]

    color = colormap()
    #color = plt.get_cmap("seismic");


    print "min:\t%f" % np.min(Z)
    print "max:\t%f" % np.max(Z)
    print "mean:\t%f" % np.mean(Z)
    print "std:\t%f" % np.std(Z)
    print "median:\t%f" % np.median(Z)

    #z_min = np.min(Z)
    #z_max = 5*np.median(Z)

    z_max = 0
    z_min = np.median(Z)

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


