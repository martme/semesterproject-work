
#ifndef main_h
#define main_h

int process_wav(char* filename);

/* Window functions */
void wf_hann(float * in, int N);
void wf_blackman_harris(float * in, int N);

#endif
