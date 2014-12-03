#include "main.h"
#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
    /*
    Look at
        http://www.mega-nerd.com/libsndfile/ with examlpes at
        http://www.mega-nerd.com/libsndfile/tools/
        install using: brew install libsndfile
    */

    if (argc != 2)
    {
        printf("Usage: %s <soundfile.wav>\n", argv[0]);
        return 1;
    }
    else if (argc == 2)
    {
        process_wav(argv[1]);
    }
    return 0;
}
