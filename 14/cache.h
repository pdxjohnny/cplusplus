#include "gen.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>


#ifndef ADDRESS_DATA_TYPE
    #define ADDRESS_DATA_TYPE unsigned int
#endif
#ifndef ADDR_BYTES
    #define ADDR_BYTES (sizeof(ADDRESS_DATA_TYPE))
#endif
#ifndef BITS_IN_BYTE
    #define BITS_IN_BYTE 8
#endif
#ifndef TOTAL_ADDRESS_BITS
    #define TOTAL_ADDRESS_BITS (BITS_IN_BYTE * ADDR_BYTES)
#endif
#ifndef VALID_BIT
    #define VALID_BIT 1
#endif
#ifndef VALID_TAG_BYTES
    // Add an ADDRESS_DATA_TYPE to the front of line
    #define VALID_TAG_BYTES ADDR_BYTES
#endif


// To hold the arguments
struct cache_holder
{
    int sets;
    int lines;
    int size;
    int hit;
    int miss;
    ADDRESS_DATA_TYPE addr_bits;
    ADDRESS_DATA_TYPE index_bits;
    ADDRESS_DATA_TYPE tag_bits;
    // cache[set][line][bytes]
    char *** cache;
};

struct cache_addr
{
    ADDRESS_DATA_TYPE addr;
    ADDRESS_DATA_TYPE index;
    ADDRESS_DATA_TYPE tag;
};

struct cache_holder * cache_create(char ** argv);
ADDRESS_DATA_TYPE cache_reverse_pow(double num, int needs_to_be);
void cache_delete(struct cache_holder * cache);
void cache_init(struct cache_holder * cache);
void cache_destroy(struct cache_holder * cache);
char cache_lookup(struct cache_holder * cache, void * address);
char * cache_find(struct cache_holder * cache, int index);
struct cache_addr cache_create_addr(struct cache_holder * cache, void * address);
ADDRESS_DATA_TYPE cache_valid(struct cache_holder * cache, void * address);
ADDRESS_DATA_TYPE cache_tag_with_valid(struct cache_holder * cache, void * address);
ADDRESS_DATA_TYPE cache_tag(struct cache_holder * cache, void * address);
ADDRESS_DATA_TYPE cache_index(struct cache_holder * cache, void * address);
ADDRESS_DATA_TYPE cache_address(struct cache_holder * cache, void * address);
// Sets the tag and valid bits, would pull in from higher level
void cache_replace(struct cache_holder * cache, char * at_index, struct cache_addr * address);


void cache_print(struct cache_holder * cache);
void cache_print_addr(struct cache_addr * address);

