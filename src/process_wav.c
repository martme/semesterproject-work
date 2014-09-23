#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <complex.h>
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

#define WINDOW_SIZE (2048)

/* For inspiration: http://www.labbookpages.co.uk/audio/wavFiles.html */
static int fftw_transform(float* data, int n);
static int render_sndfile (char * sndfilepath);


int process_wav(char* filename)
{
    render_sndfile(filename);
    return 0;
}

static int render_sndfile (char * sndfilepath)
{
    SNDFILE *sndfile;
    SF_INFO sndinfo;
    float avg, *window;
    uint64_t i, j, w, num_windows;

    memset (&sndinfo, 0, sizeof (sndinfo)) ;

    sndfile = sf_open (sndfilepath, SFM_READ, &sndinfo) ;
    if (sndfile == NULL)
    {
        fprintf (stderr, "Error : failed to open file '%s' : \n%s\n", sndfilepath, sf_strerror (NULL)) ;
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

    // printf("sample rate\t: %d Hz\n", sndinfo.samplerate);
    // printf("num frames \t: %lld\n", sndinfo.frames);

    // printf("%s\n", "Allocating buffer ...");
    float * buffer = malloc(sndinfo.channels*sndinfo.frames * sizeof(float));
    if (buffer == NULL)
    {
        fprintf(stderr, "Could not allocate memory for data \n");
        sf_close(sndfile);
        return 1;
    }
    // printf("%s\n", "Allocating buffer completed.");

    // printf("%s\n", "Reading frames ...");
    long num_frames = sf_readf_float(sndfile, buffer, sndinfo.frames);
    // printf("%s\n", "Reading frames completed.");

    if (num_frames != sndinfo.frames)
    {
        fprintf(stderr, "Did not read enough frames for source\n");
        sf_close(sndfile);
        free(buffer);
        return 1;
    }


    /*printf("Read %ld frames, Sample rate: %d, Lenght: %fs\n",
        num_frames, sndinfo.samplerate, (float)num_frames/sndinfo.samplerate);
    */
    sf_close(sndfile);


    num_windows = sndinfo.frames / WINDOW_SIZE;

    window = malloc( WINDOW_SIZE*sizeof(float) );
    for (w = 0ull; w < num_windows; w++) {
        // avg = 0;
        j = 0;
        for (i = 0; i < sndinfo.channels*WINDOW_SIZE; i += sndinfo.channels)
        {
            window[j++] = buffer[w*WINDOW_SIZE + i];

            /* Print time domain */
            // avg += buffer[w*WINDOW_SIZE + i];
            // printf("%f ", buffer[w*WINDOW_SIZE + i]);
        }
        fftw_transform(window, WINDOW_SIZE);

        /* Print time domain */
        // printf("\n");
        // avg /= (float) WINDOW_SIZE;
        // printf("%f\n", avg);
    }



    free(window);
    free(buffer);
    return 0;

} /* render_sndfile */



static int fftw_transform(float* in, int n)
{
    int i, nc;
    fftwf_complex *out;
    fftwf_plan plan_forward;

    nc = n/2 + 1;
    out = fftwf_malloc( sizeof(fftwf_complex) * nc );
    plan_forward = fftwf_plan_dft_r2c_1d(n, in, out, FFTW_ESTIMATE);
    fftwf_execute(plan_forward);

    for (i = 0; i < n/2 + 1; i++)
    {
        float value = (float) sqrtf( creal(out[i])*creal(out[i]) + cimag(out[i])*cimag(out[i]) );
        printf("%f ", value);
    }
    printf("\n");
    fflush(stdout);
    fftwf_destroy_plan(plan_forward);
    fftwf_free(out);

    return 0;
}

