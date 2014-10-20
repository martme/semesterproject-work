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
#define WINDOW_OVERLAP (3)

/* For inspiration: http://www.labbookpages.co.uk/audio/wavFiles.html */
static int process_sndfile(char * sndfilepath);
static void apply_window(float *in, int N);
static void convert_to_dB(float *arr, int N);
static void dump_spectrum(float *arr, int N);
static void dump_metadata(char* filename, int W, int Fs);

static float* power_spectrum(float *in, int N);
static void smooth_spectrum (float **frequency_response, int N, int L);
static void smooth_spectrum_reverse (float **frequency_response, int N, int L);

int process_wav(char* filename)
{
    return process_sndfile(filename);
}

static int process_sndfile (char * sndfilepath)
{
    SNDFILE *sndfile;
    SF_INFO sndinfo;
    float avg, *window, *spectrum, **frequency_response;
    int o, samples_in_spectrum = WINDOW_SIZE / 2 + 1;
    uint64_t i, j, w, num_windows, ctr;

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

    dump_metadata(sndfilepath, WINDOW_SIZE, sndinfo.samplerate);


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
    window = malloc( WINDOW_SIZE * sizeof(float) );

    frequency_response = malloc( num_windows * WINDOW_OVERLAP * sizeof(float*) );

    ctr = 0;
    for (w = 0ull; w < num_windows; w++)
    {
        for (o = 0; o < WINDOW_OVERLAP; o++)
        {
            j = 0;
            for (i = 0; i < sndinfo.channels*WINDOW_SIZE; i += sndinfo.channels)
            {
                window[j++] = buffer[w*WINDOW_SIZE + o*(WINDOW_SIZE/WINDOW_OVERLAP) + i]; /* o*(WINDOW_SIZE/2) equals stride of half a window */
            }

            spectrum = power_spectrum(window, WINDOW_SIZE);
            frequency_response[ctr++] = spectrum;
            //dump_spectrum(spectrum, samples_in_spectrum);
        }
    }
    // printf ("ctr: %d\n", (int)ctr);

    smooth_spectrum_reverse(frequency_response, ctr, samples_in_spectrum);
    for (i = 10; i < ctr - 10; i++) // Skip 10 first and last windows
    {
        dump_spectrum(frequency_response[i], samples_in_spectrum);
    }



    free(frequency_response);
    free(spectrum);
    free(window);
    free(buffer);
    return 0;

} /* render_sndfile */


/* Subtract averaged 1 previous samples from next sample */
static void smooth_spectrum (float **frequency_response, int N, int L)
{
    int i, j;
    for (i = 1; i < N; i++)
    {
        for (j = 0; j < L; j++)
        {
            frequency_response[i][j] -= frequency_response[i-1][j];
            if (frequency_response[i][j] < 0)
            {
                frequency_response[i][j] = 0;
            }
        }
    }
}
static void smooth_spectrum_reverse (float **frequency_response, int N, int L)
{
    int i, j;
    for (i = N-1; i > 0; i--)
    {
        for (j = 0; j < L; j++)
        {
            frequency_response[i][j] -= frequency_response[i-1][j];
            if (frequency_response[i][j] < 0)
            {
                frequency_response[i][j] = 0;
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
    wf_blackman_harris(in, N);
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
