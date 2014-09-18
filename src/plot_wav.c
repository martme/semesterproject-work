#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <fftw3.h>
#include <sndfile.h>

/*
struct SF_INFO
{   sf_count_t  frames ;
    int         samplerate ;
    int         channels ;
    int         format ;
    int         sections ;
    int         seekable ;
} ;
*/

/* For inspiration: http://www.labbookpages.co.uk/audio/wavFiles.html */

static int render_sndfile (const char * sndfilepath);
static int render_sndfile (const char * sndfilepath)
{
    SNDFILE *sndfile ;
    SF_INFO sndinfo ;
    uint64_t i;

    memset (&sndinfo, 0, sizeof (sndinfo)) ;

    sndfile = sf_open (sndfilepath, SFM_READ, &sndinfo) ;
    if (sndfile == NULL)
    {
        printf ("Error : failed to open file '%s' : \n%s\n", sndfilepath, sf_strerror (NULL)) ;
        return 1;
    }

     // Check format - 16bit PCM
    if (sndinfo.format != (SF_FORMAT_WAV | SF_FORMAT_PCM_24))
    {
        fprintf(stderr, "Input should be 24bit Wav\n");
        sf_close(sndfile);
        return 1;
    }

    // Check channels - sterio
    if (sndinfo.channels != 2) {
        fprintf(stderr, "Wrong number of channels does not equal sterio sound\n");
        sf_close(sndfile);
        return 2;
    }

    printf("sample rate\t: %d Hz\n", sndinfo.samplerate);
    printf("num frames \t: %lld\n", sndinfo.frames);

    printf("%s\n", "Allocating buffer ...");
    float * buffer = malloc(sndinfo.channels*sndinfo.frames * sizeof(float));
    if (buffer == NULL)
    {
        fprintf(stderr, "Could not allocate memory for data \n");
        sf_close(sndfile);
        return 1;
    }
    printf("%s\n", "Allocating buffer completed.");

    printf("%s\n", "Reading frames ...");
    long num_frames = sf_readf_float(sndfile, buffer, sndinfo.frames);
    printf("%s\n", "Reading frames completed.");

    if (num_frames != sndinfo.frames)
    {
        fprintf(stderr, "Did not read enough frames for source\n");
        sf_close(sndfile);
        free(buffer);
        return 1;
    }


    printf("Read %ld frames, Sample rate: %d, Lenght: %fs\n",
        num_frames, sndinfo.samplerate, (float)num_frames/sndinfo.samplerate);
    sf_close(sndfile);


    for (i = 0ull; i < sndinfo.channels*sndinfo.frames; i += sndinfo.channels)
    {
        printf("%f\n", buffer[i]);
    }

    free(buffer);
    return 0;

} /* render_sndfile */

void plot_wav(void)
{
    const char * path = "samples/96kHz-24bit_indiana_jones_whistle.wav";
    render_sndfile(path);
}

