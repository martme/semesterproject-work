#include <math.h>

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
