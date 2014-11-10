#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/kd.h>
/* #include <sys/time.h> */

#define DURATION (330000)

static void begin(char *label);
static void complete(char *label);

int main (int argc, char* argv)
{
	struct timeval stop, start;
	int i;

	/* timeval t -->
	 * tv_usec --> elapsed time in micro seconds
	 * tv_sec --> elapsed time in seconds
	 */

    sleep(2);

	for (i = 0; i < 3; i++)
	{
		begin("nop");
		nop(DURATION);
		complete("nop");

		begin("mem");
		mem(DURATION);
		complete("mem");

        begin("mul");
        mul(DURATION);
        complete("mul");

        begin("add");
        add(DURATION);
        complete("add");
	}
	return 0;
}

static void begin(char *label)
{
	printf("[ ] %s", label);
	fflush(stdout);
}
static void complete(char *label)
{
	printf("\r[+] %s\n", label);
    fflush(stdout);
}

