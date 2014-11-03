#include "utils.h"

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <sys/time.h>

void add(long duration)
{
	struct timeval start, stop;
	gettimeofday(&start, NULL);
	gettimeofday(&stop, NULL);
	while ( (uint)(stop.tv_usec - start.tv_usec) % 1000000 < duration )
	{
		__asm__ (
			"ADD r0 r0 r0;"
			);
		gettimeofday(&stop, NULL);
	}
}
