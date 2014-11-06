#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/time.h>

/*
 * Utility to force cache miss in L1 and L2 cache, based
 * on information derrived from cache_info utility
 */

#define L1_SIZE (32768)     /* Raspberry pi has 32kB L2 cache */
#define L2_SIZE (131072)    /* Raspberry pi has 128kB L2 cache */
#define COUNT (1000)

static void thousand_cache_misses()
{
    /* Access memory 1000 times with high probability not hitting L1 or L2 cache.
     * Can use performance counters to check actuall number of cache misses:
     * $ perf stat -e cache-misses:u bin/main
    */
    srand(4321);
    char *data, tmp;
    int i, r, L;

    /* Allocate memory 1000 times bigger than the L2 cache */
    L = 1000*L2_SIZE*sizeof(char);
    data = malloc( L );

    /* Do 1000 random lookups in the array */
    for ( i = 0; i < COUNT; ++i)
    {
        r = rand();
        tmp = data[r % L];
    }
    free(data);
}

static void thousand_cache_hits()
{
    srand(4321);
    char *data, tmp;
    int i, r, L;

    /* Allocate memory 1000 times bigger than the L2 cache */
    L = 1000*L2_SIZE*sizeof(char);
    data = malloc( L );

    /* Do 1000 random lookups in the array */
    for ( i = 0; i < COUNT; ++i)
    {
        r = rand();
        tmp = data[i % L];
    }
    free(data);
}

void mem(long duration) {
    struct timeval start, stop;
    gettimeofday(&start, NULL);
    gettimeofday(&stop, NULL);
    while ( (uint)(stop.tv_usec - start.tv_usec) % 1000000 < duration )
    {
        thousand_cache_misses ();
        gettimeofday(&stop, NULL);
    }
}
