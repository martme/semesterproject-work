#include "utils.h"

#include <stdio.h>
#include <sys/time.h>

void nop(int TIME)
{
	struct timeval start, stop;
	gettimeofday(&start, NULL);
	gettimeofday(&stop, NULL);
	while (stop.tv_sec - start.tv_sec < TIME) 
	{
		__asm__ (
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			"rep; nop;"
			);
		gettimeofday(&stop, NULL);
	}
}