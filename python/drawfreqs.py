#!/usr/bin/python
import sys
import matplotlib.pyplot as plt
import numpy as np

def main(argv):
    with open('raw.txt') as f:
        lines = [line.rstrip() for line in f]

    Z = [ [float(z) for z in line.split(" ")] for line in lines ]

    W = 2048.0      # window size
    Fs = 44100.0    # sample frequency

    dt = W/Fs       # timestep
    df = Fs/W       # frequency step

    Y, X = np.mgrid[slice( 0, len(Z) * dt, dt ),
                    slice( 0, len(Z[0]) * df, df )]

    z_min, z_max = -np.abs(Z).max(), np.abs(Z).max()
    plt.pcolor(X, Y, Z, cmap='RdBu', vmin=z_min, vmax=z_max)
    plt.axis([X.min(), X.max(), Y.min(), Y.max()])
    plt.show()

if __name__ == '__main__':
    main(sys.argv[1:])


