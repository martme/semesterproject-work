#include <math.h>

void wf_hann(float * in, int N)
{
    int n;
    float w_n;
    for (n = 0; n < N; n++) {
        w_n = 0.5 * ( 1 - cos( 2 * M_PI * n) / ( N-1 ) );
        in[n] *= w_n;
    }
}

void wf_blackman_harris(float * in, int N)
{
    int n;
    float a0, a1, a2, a3, seg1, seg2, seg3, w_n;
    a0 = 0.35875;
    a1 = 0.48829;
    a2 = 0.14128;
    a3 = 0.01168;

    for (n = 0; n < N; n++)
    {
        seg1 = a1 * (float) cos( ((float) 2 * (float) M_PI * (float) n) / ((float) N - (float) 1) );
        seg2 = a2 * (float) cos( ((float) 4 * (float) M_PI * (float) n) / ((float) N - (float) 1) );
        seg3 = a3 * (float) cos( ((float) 6 * (float) M_PI * (float) n) / ((float) N - (float) 1) );
        w_n = a0 - seg1 + seg2 - seg3;
        in[n] *= w_n;
    }
}

void wf_hamming(float * in, int N)
{
    int n;
    float a, b, w_n;
    a = 0.54;
    b = 0.46;
    for (n = 0; n < N; n++){
        w_n = (float) ( a - b * cos( (2*M_PI*n)/(N-1) ) );
        in[n] *= w_n;
    }

}
