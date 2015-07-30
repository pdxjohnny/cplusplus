#include "gen.h"
#include "cache.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

// Contants
#ifndef NUM_INPUTS
    #define NUM_INPUTS 4
#endif

#ifndef MAX_STRING
    #define MAX_STRING 10
#endif

// The help message
const char USAGE_MESSAGE [] = "Usage %s <S> <E> <B> <H> <M>\n"
"\tS = the number of sets\n"
"\tE = the number of lines\n"
"\tB = the block size in bytes\n"
"\tH = the hit time in cycles\n"
"\tM = the miss time in cycles\n";
// Failed to create cache message
const char CACHE_CREATE_FAILED [] = "Failed to create cache, check that your"
" set, line, and block size numbers are powers of two."
" And that all of your agruments are non zero numbers.\n";
// All the adderesses to find
unsigned int find_addr [NUM_INPUTS];

// Reads in the addresses to find
void read_addresses()
{
    int i;
    char input_addr [NUM_INPUTS][MAX_STRING];
    for ( i = 0; i < NUM_INPUTS; ++i )
    {
        readline( input_addr[i], MAX_STRING - 1 );
    }
    for ( i = 0; i < NUM_INPUTS; ++i )
    {
        find_addr[i] = atoh(input_addr[i]);
        if (errno)
        {
            fprintf(stderr, "ERROR: %s\n", strerror(errno));
            exit(errno);
        }
    }
    return;
}

void test_addresses(struct cache_holder * cache)
{
    int i;
    int hits = 0;
    int misses = 0;
    for (i = 0; i < NUM_INPUTS; ++i)
    {
        if ( cache_lookup(cache, &find_addr[i]) )
        {
            ++hits;
        }
        else
        {
            ++misses;
        }
    }
    double miss_rate = 0;
    int cycles = (hits * cache->hit) + (misses * cache->miss);
    // Print results
    printf("Number of hits = %d\n", hits);
    printf("Number of misses = %d\n", misses);
    // Don't divide by 0
    if ( hits || misses )
    {
        miss_rate = (double)misses / (double)(hits + misses);
        miss_rate *= 100;
    }
    printf("Miss rate = %4.2f %%\n", miss_rate);
    printf("Total cycles = %d\n", cycles);
}

int main ( int argc, char ** argv )
{
    // Check for right amount of args
    if ( argc < 6 )
    {
        printf(USAGE_MESSAGE, argv[0]);
        exit(0);
    }
    // Create the cache
    struct cache_holder * cache = cache_create(argv);
    if ( cache )
    {
        // Read in the addresses to find
        read_addresses();
        // Test all the addresses
        test_addresses(cache);
        // Destroy cache when done
        cache_destroy(cache);
    }
    // Failed to create the cache print error
    else
    {
        if (errno)
        {
            fprintf(stderr, "ERROR: %s\n", strerror(errno));
        }
        fprintf(stderr, CACHE_CREATE_FAILED);
    }
    return 0;
}

