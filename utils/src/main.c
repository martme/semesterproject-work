
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <linux/kd.h>
/* #include <sys/time.h> */

#define TIME_PER_OPERATION (1)

static void begin(char *label);
static void complete(char *label);
/*static void byreference(void (*foo)(int));
*/

int main (int argc, char* argv) 
{	
	struct timeval stop, start;

	/* timeval t -->
	 * tv_usec --> elapsed time in micro seconds 
	 * tv_sec --> elapsed time in seconds
	 */

	begin("nop");
	nop(TIME_PER_OPERATION);
	complete("nop");

	begin("mul");
	mul(TIME_PER_OPERATION);
	complete("mul");

	begin("add");
	add(TIME_PER_OPERATION);
	complete("add");

	begin("nop");
	nop(TIME_PER_OPERATION);
	complete("nop");

	begin("mul");
	mul(TIME_PER_OPERATION);
	complete("mul");

	begin("add");
	add(TIME_PER_OPERATION);
	complete("add");
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
