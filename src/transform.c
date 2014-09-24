#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <complex.h>
#include <fftw3.h>

/*
    Inspired by ex2 from http://people.sc.fsu.edu/~jburkardt/c_src/fftw3/fftw3_prb.c
    FFT Spectrum Analysis in C explained: http://stackoverflow.com/questions/10627517/wav-file-analysis-c-libsndfile-fftw3
*/

static float blackman_harris(int n, int N);
static float to_decibel(float x);

void dump_fftw(const float* data, int n)
{
    int i, nc;
    float normalizer;
    float * in = fftwf_malloc(sizeof(float)*n);
    for (i = 0; i < n; i++)
    {
        in[i] = 0 + data[i];
    }
    fftwf_complex *out;
    fftwf_plan plan_forward;

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
        float db_normalized_value = to_decibel(value);
        printf("%f ", value);
    }
    printf("\n");
    fflush(stdout);
    fftwf_destroy_plan(plan_forward);
    fftwf_free(out);
}


static float blackman_harris(int n, int N)
{
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
