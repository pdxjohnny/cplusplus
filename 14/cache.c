#include "cache.h"

/*
Direct-Mapped Cache - doing this
512 lines in cache
block size is 64 bytes
Valid bit, first bit check if data is valid
Tag first 17 bits,label that says what was stored in the cache
index middle 9 bits, 2^9 is 512 so the index selects the line
address of byte in block last 6 bits
when you get the memory at the index the tag will be dropped out
as the first 17 bits out 64 bytes make sure the tag is the same
use index to find line
read line
compare tag
if same hit
if different miss and go out to main memory and store it here
*/

struct cache_holder * cache_create(char ** argv)
{
    struct cache_holder * cache = (struct cache_holder *)malloc(sizeof(struct cache_holder));
    cache->sets = atoi(argv[1]);
    cache->lines = atoi(argv[2]);
    cache->size = atoi(argv[3]);
    cache->hit = atoi(argv[4]);
    cache->miss = atoi(argv[5]);
    // Get the bits corresponding to each
    ADDRESS_DATA_TYPE sets = cache_reverse_pow(cache->sets, 2);
    ADDRESS_DATA_TYPE lines = cache_reverse_pow(cache->lines, 2);
    ADDRESS_DATA_TYPE size = cache_reverse_pow(cache->size, 2);
    // Check for the correct arguments
    if ( cache->sets && cache->lines &&
        cache->size && cache->hit &&
        cache->miss && sets && lines && size )
    {
        cache->index_bits = sets + lines;
        cache->addr_bits = size;
        cache->tag_bits = TOTAL_ADDRESS_BITS - cache->index_bits - cache->addr_bits;
        // Add the bytes needs for lookup
        cache->size += VALID_TAG_BYTES;
        cache_init(cache);
    }
    else
    {
        errno = EINVAL;
        free(cache);
        cache = 0x0U;
    }
    return cache;
}

ADDRESS_DATA_TYPE cache_reverse_pow(double num, int needs_to_be)
{
    int i;
    for (i = 0U; num > 1; ++i)
    {
        num /= needs_to_be;
    }
    // If it divided evenly it whould be one
    if ( num == 1 )
    {
        return i;
    }
    // Otherwise it wasn't correct
    return 0U;
}

void cache_delete(struct cache_holder * cache)
{
    cache_destroy(cache);
    return;
}

void cache_init(struct cache_holder * cache)
{
    char *** cache_array = (char ***)malloc(sizeof(char ***) * cache->sets);
    int i, j;
    for (i = 0; i < cache->sets; ++i)
    {
        cache_array[i] = (char **)malloc(sizeof(char **) * cache->lines);
        for (j = 0; j < cache->lines; ++j)
        {
            cache_array[i][j] = (char *)malloc(sizeof(char *) * cache->size);
        }
    }
    cache->cache = cache_array;
    return;
}

void cache_destroy(struct cache_holder * cache)
{
    int i, j;
    char *** cache_array = cache->cache;
    for (i = 0; i < cache->sets; ++i)
    {
        for (j = 0; j < cache->lines; ++j)
        {
            free(cache_array[i][j]);
        }
        free(cache_array[i]);
    }
    free(cache_array);
    free(cache);
    cache = 0x0U;
    return;
}

char cache_lookup(struct cache_holder * cache, void * address)
{
    char hit = 0x0;
    struct cache_addr parsed = cache_create_addr(cache, address);
    char * at_index = cache_find(cache, parsed.index);
    ADDRESS_DATA_TYPE valid = cache_valid(cache, at_index);
    ADDRESS_DATA_TYPE tag = cache_tag_with_valid(cache, at_index);
    // Hit return the byte, well we cant really do that because
    // the byte might be null and then the caller would think it
    // missed
    if ( valid && tag == parsed.tag )
    {
        hit = 1;
    }
    // Miss, set the valid bit and tag at this index
    else
    {
        cache_replace(cache, at_index, &parsed);
    }
    // Lookup
    return hit;
}

char * cache_find(struct cache_holder * cache, int index)
{
    char * found = 0x0U;
    int set = index % cache->sets;
    int line = index % cache->lines;
    found = cache->cache[set][line];
    return found;
}

struct cache_addr cache_create_addr(struct cache_holder * cache, void * address)
{
    struct cache_addr parsed;
    parsed.tag = cache_tag(cache, address);
    parsed.index = cache_index(cache, address);
    parsed.addr = cache_address(cache, address);
    return parsed;
}

ADDRESS_DATA_TYPE cache_valid(struct cache_holder * cache, void * address)
{
    ADDRESS_DATA_TYPE index = 0x0U;
    if (address)
    {
        index = ((ADDRESS_DATA_TYPE *)address)[0];
        // Get rid of all but the first bit
        index >>= TOTAL_ADDRESS_BITS - VALID_BIT;
    }
    return index;
}

ADDRESS_DATA_TYPE cache_tag_with_valid(struct cache_holder * cache, void * address)
{
    ADDRESS_DATA_TYPE index = 0x0U;
    if (address)
    {
        index = ((ADDRESS_DATA_TYPE *)address)[0];
        // Get rid of the valid bit
        index <<= VALID_BIT;
        index >>= (TOTAL_ADDRESS_BITS - cache->tag_bits);
    }
    return index;
}

ADDRESS_DATA_TYPE cache_tag(struct cache_holder * cache, void * address)
{
    ADDRESS_DATA_TYPE index = 0x0U;
    if (address)
    {
        index = ((ADDRESS_DATA_TYPE *)address)[0];
        index >>= TOTAL_ADDRESS_BITS - cache->tag_bits;
    }
    return index;
}

ADDRESS_DATA_TYPE cache_index(struct cache_holder * cache, void * address)
{
    ADDRESS_DATA_TYPE index = 0x0U;
    if (address)
    {
        index = ((ADDRESS_DATA_TYPE *)address)[0];
        index <<= cache->tag_bits;
        index >>= (cache->tag_bits + cache->addr_bits);
    }
    return index;
}

ADDRESS_DATA_TYPE cache_address(struct cache_holder * cache, void * address)
{
    ADDRESS_DATA_TYPE index = 0x0U;
    if (address)
    {
        index = ((ADDRESS_DATA_TYPE *)address)[0];
        index <<= (cache->tag_bits + cache->index_bits);
        index >>= (cache->tag_bits + cache->index_bits);
        // Added to fix array offset
        index += VALID_TAG_BYTES;
    }
    return index;
}

void cache_replace(struct cache_holder * cache, char * at_index, struct cache_addr * address)
{
    ADDRESS_DATA_TYPE valid_bit = 0x01U;
    valid_bit <<= cache->tag_bits;
    // Add the valid bit to the front of the tag
    ADDRESS_DATA_TYPE replace = valid_bit | address->tag;
    // Shift all the way to the right
    replace <<= (TOTAL_ADDRESS_BITS - cache->tag_bits - VALID_BIT);
    // Write it in front of the byte array
    ((ADDRESS_DATA_TYPE *)at_index)[0] = replace;
}

void cache_print(struct cache_holder * cache)
{
    printf("cache->sets:\t%d\n", cache->sets);
    printf("cache->lines:\t%d\n", cache->lines);
    printf("cache->size:\t%d\n", cache->size);
    printf("cache->hit:\t%d\n", cache->hit);
    printf("cache->miss:\t%d\n", cache->miss);
    printf("cache->tag_bits:\t%d\n", cache->tag_bits);
    printf("cache->index_bits:\t%d\n", cache->index_bits);
    printf("cache->addr_bits:\t%d\n", cache->addr_bits);
}

void cache_print_addr(struct cache_addr * address)
{
    printf("address->tag:\t%08x\t%d\n", address->tag, address->tag);
    printf("address->index:\t%08x\t%d\n", address->index, address->index);
    printf("address->addr:\t%08x\t%d\n", address->addr, address->addr);
}
