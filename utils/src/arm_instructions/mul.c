#include "utils.h"

#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <sys/time.h>

void mul(long duration)
{
	struct timeval start, stop;
	gettimeofday(&start, NULL);
	gettimeofday(&stop, NULL);
	while ( (uint)(stop.tv_usec - start.tv_usec) % 1000000 < duration )
	{
		__asm__ (
			"MUL r0, r2, r2;"
			);
		gettimeofday(&stop, NULL);
	}
}
