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

static void force_cache_miss() 
{
	/* Able to hit 1000 times and never hit L1 or L2 cache, given linear cache strategy */
	
	volatile char *data, tmp;
	int i, size;
	clock_t start;

	size = 1000*L2_SIZE*sizeof(char);
	data = malloc(size);

	start = clock();
	for ( i = 0; i < size; i += L2_SIZE)
	{
		tmp = data[i];
	}
	//free(data);
	printf("Time w/ cache miss:\t%f\n", (double)(clock() - start));
}

static void no_cache_miss() 
{
	/* Able to hit 1000 times and never hit L1 or L2 cache, given linear cache strategy */
	
	volatile char *data, tmp;
	int i, size;
	clock_t start;

	size = 1000*sizeof(char);
	data = malloc(size);

	start = clock();
	for ( i = 0; i < size; i += 1)
	{
		tmp = data[i];
	}
	//free(data);
	printf("Time w/o cache miss:\t%f\n", (double)(clock() - start));
}

void mem(int TIME) {
	force_cache_miss();
	no_cache_miss();

	return;
	struct timeval start, stop;
	gettimeofday(&start, NULL);
	gettimeofday(&stop, NULL);
	while (stop.tv_sec - start.tv_sec < TIME)
	{ 
		force_cache_miss ();
		gettimeofday(&stop, NULL);
	}
	//no_cache_miss ();
}