
#include <stdio.h>
#include <stdlib.h>


/*
 * Utility to force cache miss in L1 and L2 cache, based
 * on information derrived from cache_info utility
 */

#define L1_SIZE (32768)
#define L2_SIZE (262144)
#define COUNT (1000)

int main()
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
