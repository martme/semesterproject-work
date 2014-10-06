
#include <stdio.h>
#include <sys/time.h>
/* #include <sys/time.h> */

#define TIME_PER_OPERATION (2)

static void init(struct timeval *start, struct timeval *stop);
static int time_elapsed (struct timeval start, struct timeval stop);

int main (int argc, char* argv) 
{	
	struct timeval stop, start;
	


	/* timeval t -->
	 * tv_usec --> elapsed time in micro seconds 
	 * tv_sec --> elapsed time in seconds
	 */

	printf("Looping micro instructions for %d seconds each\n", TIME_PER_OPERATION);

	printf("[ ] nop");
	fflush(stdout);

	init(&start, &stop);
	while (time_elapsed(start, stop) < TIME_PER_OPERATION) 
	{
		__asm__ (
			"nop"
			);
		gettimeofday(&stop, NULL);
	}
	printf("\r[-] nop\n");


	printf("[ ] mul");
	fflush(stdout);

	init(&start, &stop);
	while (time_elapsed(start, stop) < TIME_PER_OPERATION) 
	{
		__asm__ (
			"mul %ebx;"
			);
		gettimeofday(&stop, NULL);
	}
	printf("\r[-] mul\n");

	init(&start, &stop);
	while (time_elapsed(start, stop) < TIME_PER_OPERATION) 
	{
		__asm__ (
			"hlt;"
			);
		break;
		gettimeofday(&stop, NULL);
	}
	printf("\r[-] mul\n");





	return 0;
}

static void init(struct timeval *start, struct timeval *stop) 
{
	gettimeofday(&(*start), NULL);
	gettimeofday(&(*stop), NULL);
}

static int time_elapsed (struct timeval start, struct timeval stop)
{
	return stop.tv_sec - start.tv_sec;
}