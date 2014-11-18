#include "main.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#include <complex.h>
#include <fftw3.h>
#include <sndfile.h>

#define WINDOW_SIZE (4096) /* Higher value --> better frequency granularity / worse time granularity */
#define SMOOTHING_DEPTH (100)
#define WINDOW_OVERLAP (1)

/* For inspiration: http://www.labbookpages.co.uk/audio/wavFiles.html */
static int process_sndfile(char * sndfilepath);
static void apply_window(float *in, int N);
static void convert_to_dB(float *arr, int N);
static void dump_spectrum(float *arr, int N);
static void dump_metadata(char* filename, int W, int Fs);

static float* power_spectrum(float *in, int N);
static void smooth_spectrum (float **spectrum, int N, int L);
static void smooth_spectrum_reverse (float **spectrum, int N, int L);

int process_wav(char* filename)
{
    return process_sndfile(filename);
}


static int process_sndfile (char * sndfilepath)
{
    SNDFILE *sndfile;
    SF_INFO sndinfo;
    float *window, **spectrum;
    long i, j, w, num_w, ctr;
    int o, num_c;

    memset (&sndinfo, 0, sizeof (sndinfo)) ;

    sndfile = sf_open (sndfilepath, SFM_READ, &sndinfo) ;
    if (sndfile == NULL)
    {
        fprintf (stderr, "Error : failed to open file '%s' : \n%s\n", sndfilepath, sf_strerror (NULL)) ;
        return 1;
    }

    // Check format - 24bit PCM
    // printf("%#x\n", sndinfo.format);
    if ( !( sndinfo.format == (SF_FORMAT_WAVEX | SF_FORMAT_PCM_24)  ||   // For Knowles
            sndinfo.format == (SF_FORMAT_WAV   | SF_FORMAT_PCM_24) ) )     // For Zoom H4n
    {
        fprintf(stderr, "Input should be 24bit WAV\n");
        sf_close(sndfile);
        return 1;
    }

    // Check channels - sterio
    if (sndinfo.channels > 2) {
        fprintf(stderr, "Wrong number of channels; got more than two.\n");
        sf_close(sndfile);
        return 2;
    }

    /* Print relevant sndfile metadata to stdout */
    dump_metadata(sndfilepath, WINDOW_SIZE, sndinfo.samplerate);

    float * buffer = malloc(sndinfo.channels*sndinfo.frames * sizeof(float));
    if (buffer == NULL)
    {
        fprintf(stderr, "Could not allocate memory for data \n");
        sf_close(sndfile);
        return 1;
    }

    long num_frames = sf_readf_float(sndfile, buffer, sndinfo.frames);
    if (num_frames != sndinfo.frames)
    {
        fprintf(stderr, "Did not read enough frames for source\n");
        sf_close(sndfile);
        free(buffer);
        return 1;
    }
    sf_close(sndfile);

    /*************************************
     ***** Start processing sndfile ******
     *************************************/


    /* Number of c_i in frequency response spectrum */
    num_c = WINDOW_SIZE / 2 + 1;
    /* Number of frames per window */
    num_w = sndinfo.frames / WINDOW_SIZE;
    window = malloc( WINDOW_SIZE * sizeof(float) );
    spectrum = malloc( num_w * WINDOW_OVERLAP * sizeof(float*) );

    ctr = 0;
    /* For every whole window in the samples */
    for (w = 0; w < num_w; w++)
    {
        /* For every partial window within the window (compute with overlap) */
        for (o = 0; o < WINDOW_OVERLAP; o++)
        {
            j = 0;
            /* For the samples making up this window */
            //for (i = 0; i < sndinfo.channels*WINDOW_SIZE; i += sndinfo.channels) // Left channel
            for (i = 1; i < sndinfo.channels*WINDOW_SIZE; i += sndinfo.channels) // Right channel
            {
                /* Assign sample to correct position in window */
                window[j++] = buffer[i + (w*WINDOW_SIZE) + o*(WINDOW_SIZE/WINDOW_OVERLAP)];
            }
            spectrum[ctr++] = power_spectrum(window, WINDOW_SIZE);
        }
    }

    // smooth_spectrum_reverse(spectrum, ctr, num_c);
    //for (i = 10; i < ctr - 10; i++) // Skip 10 first and last windows
    for (i = 0; i < ctr; i++)
    {
        /* Print the frequency response components for this window */
        dump_spectrum(spectrum[i], num_c);
    }



    free(spectrum);
    free(window);
    free(buffer);
    return 0;

} /* render_sndfile */


/* Subtract averaged 1 previous samples from next sample */
static void smooth_spectrum (float **spectrum, int N, int L)
{
    int i, j;
    for (i = 1; i < N; i++)
    {
        for (j = 0; j < L; j++)
        {
            spectrum[i][j] -= spectrum[i-1][j];
            if (spectrum[i][j] < 0)
            {
                spectrum[i][j] = 0;
            }
        }
    }
}


static void smooth_spectrum_reverse (float **spectrum, int N, int L)
{
    int i, j;
    for (i = N-1; i > 0; i--)
    {
        for (j = 0; j < L; j++)
        {
            spectrum[i][j] -= spectrum[i-1][j];
            if (spectrum[i][j] < 0)
            {
                spectrum[i][j] = 0;
            }
        }
    }
}


static float* power_spectrum(float *in, int N)
{
    /* 1. Collect N samples where N is a power of 2 */
    int i, nc;
    fftwf_complex *out;
    fftwf_plan plan_forward;
    nc = N/2 + 1;

    float *result = malloc( sizeof (float) * nc );

    /* 2. Apply a soutable window function to the samples */
    apply_window(in, N);

    /* 3. Pass windowed samples to an FFT routine */
    out = fftwf_malloc( sizeof( fftwf_complex ) * nc );
    plan_forward = fftwf_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);
    fftwf_execute(plan_forward);

    /* 4. Calculate the squared magnitude of the FFT output bins (re * re + im * im) */
    for (i = 0; i < nc; i++)
    {
        /* Normalization here?? */
        result[i] = (float) sqrt( (float)creal(out[i])*creal(out[i]) + cimag(out[i])*cimag(out[i]) );
    }

    /* 5. (optional) Calculate 10 * log10 of each magnitude squared output bin to get a value in dB */
    //convert_to_dB(result, nc);

    fftwf_destroy_plan(plan_forward);
    fftwf_free(out);

    return result;
}


static void apply_window(float *in, int N)
{
    wf_hamming(in, N);
    //wf_blackman_harris(in, N);
    //wf_hann(in, N);
}


static void convert_to_dB(float *arr, int N)
{
    int i;
    for (i = 0; i < N; i++)
    {

        //printf("%f ", arr[i]);
        arr[i] = (float) 10*log10(arr[i]); /* 20 or 10 * log10 ???? */
    }
    //printf("\n");
}

static void dump_metadata(char* filename, int W, int Fs)
{
    printf("%s\n", filename);
    printf("%d\n", WINDOW_OVERLAP);
    printf("%d\n", W);
    printf("%d\n", Fs);
}


static void dump_spectrum(float *arr, int N)
{
    int i;
    for (i = 0; i < N; i++){
        printf("%f ", arr[i]);
    }
    printf("\n");
    /* Flush output buffer to remove buffer delay in pipe */
    fflush(stdout);
}
