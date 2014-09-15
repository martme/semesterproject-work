#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include <complex.h>
#include <fftw3.h>
#include "portaudio.h"

#define SAMPLE_RATE         (44100)
#define PA_SAMPLE_TYPE      paFloat32
#define FRAMES_PER_BUFFER   (512) /* orig 64 */ /* 2048 = 2^11 -> N = 11 */

typedef float SAMPLE;



static void real_1d_fft(const float* in, int n);
static float to_decibel(float x);
static int index_of_freq(int freq);
static float blackman_harris(int n, int N);


static int dumpCallback( const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData );



static int gNumNoInputs = 0;
/* This routine will be called by the PortAudio engine when audio is needed.
 ** It may be called at interrupt level on some machines so don't do anything
 ** that could mess up the system like calling malloc() or free().
 */
static int dumpCallback( const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData )
{
    SAMPLE *out = (SAMPLE*)outputBuffer;
    const SAMPLE *in = (const SAMPLE*)inputBuffer;
    unsigned int i;
    (void) timeInfo; /* Prevent unused variable warnings. */
    (void) statusFlags;
    (void) userData;

    float sum = 0;

    real_1d_fft(in, framesPerBuffer);
    if ( inputBuffer == NULL ) {
        for (i = 0; i < framesPerBuffer; i++)
        {
            *out++ = 0; /* nothing on left */
        }
        gNumNoInputs++;
    }
    else
    {
        for (i = 0; i < framesPerBuffer; i++)
        {
            //printf("%f\n", *in); /* print left */
            sum += *in;
            *out++ = *in++; /* play left */
        }
    }

    /*
    printf("%f\n", 2*sum/(float)framesPerBuffer);
    fflush(stdout);
    */
    return paContinue;
}

static void real_1d_fft(const float* data, int n)
{
    /*
    Inspired by ex2 from http://people.sc.fsu.edu/~jburkardt/c_src/fftw3/fftw3_prb.c
    FFT Spectrum Analysis in C explained: http://stackoverflow.com/questions/10627517/wav-file-analysis-c-libsndfile-fftw3

    */
    int i, nc;
    float normalizer;

    /* From stack overflow :s */
    /*
    int k, N;
    N = FRAMES_PER_BUFFER;
    for(k = 0; k < N; k++)
    {
        if(k == 0){
            normalizer = blackman_harris(k, N);
        }
        else {
            normalizer = blackman_harris(k, N);
        }
    }
    normalizer = normalizer * (float) N/2;
    printf("%f\n", normalizer);
    */

    float * in = fftwf_malloc(sizeof(float)*n);
    for (i = 0; i < n; i++)
    {
        in[i] = 0 + data[i];
    }
    fftwf_complex *out;
    fftwf_plan plan_forward;
    //fftwf_plan plan_backward

    nc = n/2 + 1;
    out = fftwf_malloc( sizeof(fftwf_complex) * nc );
    plan_forward = fftwf_plan_dft_r2c_1d(n, in, out, FFTW_ESTIMATE);
    fftwf_execute(plan_forward);

    for (i = 0; i < n/2 + 1; i++)
    {
        /* TODO: If correct: precompute normalizer for fast lookup */
        normalizer = blackman_harris(i, n) * (float) (n/2); /* Me thinks, contradict Stack Overflow .. */
        float value = (float) sqrtf( creal(out[i])*creal(out[i]) + cimag(out[i])*cimag(out[i]) );
        float normalized_value = value / normalizer;
        //float db_normalized_value = to_decibel(normalized_value);
        printf("%f ", normalized_value);
    }
    printf("\n");
    fflush(stdout);
    fftwf_destroy_plan(plan_forward);
    fftwf_free(out);
}


static float blackman_harris(int n, int N)
{
    /* N represents width in samples (window), [n is sample in window?????] */
    /* http://en.wikipedia.org/wiki/Window_function */
    float a0, a1, a2, a3, seg1, seg2, seg3, w_n;
    a0 = 0.35875;
    a1 = 0.48829;
    a2 = 0.14128;
    a3 = 0.01168;

    seg1 = a1 * (float) cos( ((float) 2 * (float) M_PI * (float) n) / ((float) N - (float) 1) );
    seg2 = a2 * (float) cos( ((float) 4 * (float) M_PI * (float) n) / ((float) N - (float) 1) );
    seg3 = a3 * (float) cos( ((float) 6 * (float) M_PI * (float) n) / ((float) N - (float) 1) );

    w_n = a0 - seg1 + seg2 - seg3;
    return w_n;
}

static float to_decibel(float x)
{
    return fabs ( 20.0f * log10f( x ) );
}

static int index_of_freq(int freq)
{
    return freq * SAMPLE_RATE / FRAMES_PER_BUFFER;
}


/*******************************************************************/
int signal_dump(void)
{
    PaStreamParameters inputParameters, outputParameters;
    PaStream *stream;
    PaError err;

    err = Pa_Initialize();
    if( err != paNoError ) goto error;

    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (inputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default input device.\n");
        goto error;
    }
    inputParameters.channelCount = 1;       /* mono input */
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default output device.\n");
        goto error;
    }
    outputParameters.channelCount = 1;       /* mono output */
    outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(
                        &stream,
                        &inputParameters,
                        &outputParameters,
                        SAMPLE_RATE,
                        FRAMES_PER_BUFFER,
                        0, /* paClipOff, */  /* we won't output out of range samples so don't bother clipping them */
                        dumpCallback,
                        NULL );
    if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;

    printf("Hit ENTER to stop program.\n");
    getchar();
    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;

    printf("Finished. gNumNoInputs = %d\n", gNumNoInputs );
    Pa_Terminate();
    return 0;

error:
    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    return -1;
}
