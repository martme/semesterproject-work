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

    title   = sys.stdin.readline().strip()          # filepath to sndfile
    overlap = float(sys.stdin.readline().rstrip())  # window overlap
    W       = float(sys.stdin.readline().rstrip())  # window size
    Fs      = float(sys.stdin.readline().rstrip())  # sampling frequency
    lines   = [line.rstrip() for line in sys.stdin]
    Z       = [ [ (float(z)) for z in line.split(" ")] for line in lines[2:] ]

    Z = np.log10(Z)

    dt = W/(overlap*Fs) # timestep --> only progress part of a window at the time
    df = Fs/W           # frequency step

    Y, X = np.mgrid[slice( 0, len(Z) * dt, dt ),
                    slice( 0, len(Z[0]) * df, df )]

    print "min:\t%f"    % np.min(Z)
    print "max:\t%f"    % np.max(Z)
    print "mean:\t%f"   % np.mean(Z)
    print "median:\t%f" % np.median(Z)
    print "std:\t%f"    % np.std(Z)

    # vary these parameters to enhance subtle changes in plot
    z_min = np.median(Z)
    z_max = np.median(Z) + 2*np.std(Z)

    plt.title(title)
    plt.pcolor(np.array(X), np.array(Y), np.array(Z), cmap=colormap(), vmin=z_min, vmax=z_max)
    plt.axis([X.min(), X.max(), Y.min(), Y.max()])
    plt.show()

def colormap():
    import matplotlib as mpl
    return mpl.colors.ListedColormap([(0.0, x, 0.0, 1) for x in np.linspace(0, 1, 255)])

if __name__ == '__main__':
    main(sys.argv[1:])
