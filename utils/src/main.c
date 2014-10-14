
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/kd.h>
/* #include <sys/time.h> */


static void begin(char *label);
static void complete(char *label);
/*static void byreference(void (*foo)(int));
*/

int main (int argc, char* argv)
{
	struct timeval stop, start;
	int i;

	/* timeval t -->
	 * tv_usec --> elapsed time in micro seconds
	 * tv_sec --> elapsed time in seconds
	 */

	for (i = 0; i < 3; i++)
	{
		begin("nop");
		nop();
		complete("nop");

		begin("mem");
		mem();
		complete("mem");
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
}

