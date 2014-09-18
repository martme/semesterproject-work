#include "main.h"

#include "portaudio.h"
#include "sndfile.h"
#include <stdio.h>
#include <math.h>

int main(void)
{
    /*
    Look at
        http://www.mega-nerd.com/libsndfile/ with examlpes at
        http://www.mega-nerd.com/libsndfile/tools/
        install using: brew install libsndfile
    */

    plot_wav();
    /*signal_dump();*/

    /*ampl_dump();*/
    return 0;
}
