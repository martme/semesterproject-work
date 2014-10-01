#include "main.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <complex.h>
#include <fftw3.h>
#include <sndfile.h>

#define WINDOW_SIZE (1024)

/* For inspiration: http://www.labbookpages.co.uk/audio/wavFiles.html */
static float* power_spectrum(float *in, int N);
static int process_sndfile(char * sndfilepath);
static void apply_window(float *in, int N);
static void convert_to_dB(float *arr, int N);
static void dump_spectrum(float *arr, int N);
static void dump_metadata(int W, int Fs);

int process_wav(char* filename)
{
    process_sndfile(filename);
    return 0;
}

static int process_sndfile (char * sndfilepath)
{
    SNDFILE *sndfile;
    SF_INFO sndinfo;
    float avg, *window, *spectrum;
    int samples_in_spectrum = WINDOW_SIZE / 2 + 1;
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

    dump_metadata(WINDOW_SIZE, sndinfo.samplerate);

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
    for (w = 0ull; w < num_windows; w++)
    {
        j = 0;
        for (i = 0; i < sndinfo.channels*WINDOW_SIZE; i += sndinfo.channels)
        {
            window[j++] = buffer[w*WINDOW_SIZE + i];
        }
        spectrum = power_spectrum(window, WINDOW_SIZE);
        dump_spectrum(spectrum, samples_in_spectrum);

        /* Calculate spectrum with 50% overlap */
        if (w + 1 >= num_windows) continue;

        j = 0;
        for (i = 0; i < sndinfo.channels*WINDOW_SIZE; i += sndinfo.channels)
        {
            window[j++] = buffer[w*WINDOW_SIZE + WINDOW_SIZE/2 + i];
        }
        spectrum = power_spectrum(window, WINDOW_SIZE);
        dump_spectrum(spectrum, samples_in_spectrum);
    }


    free(spectrum);
    free(window);
    free(buffer);
    return 0;

} /* render_sndfile */


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
    //wf_blackman_harris(in, N);
    wf_hann(in, N);
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

static void dump_metadata(int W, int Fs)
{
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
