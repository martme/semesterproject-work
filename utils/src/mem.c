#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/time.h>

/*
 * Utility to force cache miss in L1 and L2 cache, based
 * on information derrived from cache_info utility
 */

/* Size of both L1 and L2 is 32768 bytes */
#define L1_SIZE (32768)
#define L2_SIZE (262144)
#define L3_SIZE (8388608)

static void force_cache_miss()
{
    /* Access memory 1000 times with high probability not hitting L1 or L2 cache.
     * Can use performance counters to check actuall number of cache misses:
     * $ perf stat -e cache-misses:u bin/main
    */

    srand(4321);
    char *data, tmp;
    int i, size;
    clock_t start;

    size = 1000*L2_SIZE*sizeof(char);
    data = malloc(size);

    //start = clock();
    for ( i = 0; i < size; i += L2_SIZE)
    {
    	tmp = data[rand() % size];
    }
    free(data);
    //printf("Time w/ cache miss:\t%f\n", (double)(clock() - start));
}

static void no_cache_miss()
{
    /* Access memory 1000 times with high probability not hitting L1 or L2 cache */

    char *data, tmp;
    int i, size;
    clock_t start;

    size = 1000*sizeof(char);
    data = malloc(size);

    //start = clock();
    for ( i = 0; i < size; i += 1)
    {
        tmp = data[i];
    }
    free(data);
    //printf("Time w/o cache miss:\t%f\n", (double)(clock() - start));
}

void mem() {
	struct timeval start, stop;
	gettimeofday(&start, NULL);
	gettimeofday(&stop, NULL);
	while ( (uint)(stop.tv_usec - start.tv_usec) % 1000000 < 500000 )
	{
		force_cache_miss ();
		gettimeofday(&stop, NULL);
	}
}
