#include "gen.h"



// Reads a line into a buffer from stdin
int readline( char * buffer, int max )
{
    // Index in buffer array
    int i;
    // Current character
    char tmp;
    // Read until newline or max - 1 for NULL terminate
    for ( i = 0; i < max - 1; ++i )
    {
        // Read in a character
        read( STDIN_FILENO, & tmp, 1 );
        // If we are at a newline then we are done
        if ( tmp == '\n' )
        {
            break;
        }
        // Other wise copy charaters into the buffer
        else
        {
            buffer[ i ] = tmp;
        }
    }
    // Remove the newline from stdin
    while ( tmp != '\n' )
    {
        read( STDIN_FILENO, & tmp, 1 );
    }
    // NULL terminate
    buffer[ i ] = '\0';
    // Length of string
    return i;
}



// Reads a line into a buffer from the file pointer
int freadline( char * buffer, int max, FILE * source )
{
    // Index in buffer array
    int i;
    // Current character
    char tmp;
    // Read until newline or max - 1 for NULL terminate
    for ( i = 0; i < max - 1; ++i )
    {
        // Read in a character
        tmp = fgetc( source );
        // If we are at a newline then we are done
        if ( tmp == '\n' || tmp == EOF )
        {
            break;
        }
        // Other wise copy charaters into the buffer
        else
        {
            buffer[ i ] = tmp;
        }
    }
    // Remove the newline from stdin
    while ( tmp != '\n' && tmp != EOF )
    {
        fgetc( source );
    }
    // NULL terminate
    buffer[ i ] = '\0';
    // Length of string
    return i;
}



// Prints the time in a user friendly way
void print_time( struct timeval * print )
{
    int hours = 0;
    int minutes = 0;
    int seconds = (int) print->tv_sec;
    if ( seconds > 60 )
    {
        minutes = seconds / 60;
        seconds = seconds % 60;
    }
    if ( minutes > 60 )
    {
        hours = minutes / 60;
        minutes = minutes % 60;
    }
    // print hours:minutes:seconds.useconds
    printf("%02d:%02d:%02d.%ld", hours, minutes, seconds, print->tv_usec );
    return;
}

int read_byte( FILE * source, char * buffer )
{
    int curr_read = 0;
    if (!feof(source))
    {
        curr_read = fread( buffer, sizeof( *buffer ), 1, source );
    }
    return curr_read;
}

void print_hex(void * hex, int length)
{
    int i;
    // Walk through the length given
    for (i = length - 1; i >= 0; --i)
    {
        unsigned char current = ((unsigned char *)hex)[i];
        // Divide by 16 to get the first four bytes
        char first = (current / 16);
        // Mod by 16 to get the first four bytes
        char second = (current % 16);
        // Do some ascci table magic
        if ( first <= 9 )
            first += 48;
        else
            first += 55;
        if ( second <= 9 )
            second += 48;
        else
            second += 55;
        // Put the chars into stdout
        putchar(first);
        putchar(second);
    }
    return;
}

char swap_bits( char byte, int one, int two )
{
    char tmp_1, tmp_2, swap;
    int hex_1 = 0x1 << one;
    int hex_2 = 0x1 << two;
    tmp_1 = byte & hex_1;
    tmp_1 = tmp_1 >> abs( one - two );
    tmp_2 = byte & hex_2;
    tmp_2 = tmp_2 << abs( one - two );
    if ( tmp_1 == 0 && tmp_2 != 0 )
    {
        byte = byte ^ hex_2;
    }
    if ( tmp_2 == 0 && tmp_1 != 0 )
    {
        byte = byte ^ hex_1;
    }
    swap = tmp_1 | tmp_2;
    byte = swap | byte;
    return byte;
}

void strnclr( char * buffer, int length )
{
    int i;
    for ( i = 0; i < length; ++i )
    {
        buffer[i] = 0;
    }
    return;
}

unsigned int atoh( char * string )
{
    int i;
    // For the loop
    int curr_hex;
    char curr_char;
    int mult;
    // The return value
    unsigned int as_hex = 0x0U;
    // Length of the string
    int length = strnlen(string, sizeof(int) * 2);
    // printf("sizeof string %d\t", sizeof(int) * 2);
    // // Walk through the length given
    for (i = 0; i < length; ++i)
    {
        curr_char = string[i];
        // If not within range
        if ( !((curr_char >= 'a' && curr_char <= 'f') ||
            (curr_char >= 'A' && curr_char <= 'F') ||
            (curr_char >= '0' && curr_char <= '9')) )
        {
            errno = EFAULT;
            return 0x0U;
        }
        else if ( curr_char >= 'a' && curr_char <= 'f' )
        {
            curr_hex = string[i] - 'a' + 10;
        }
        else if ( curr_char >= 'A' && curr_char <= 'F' )
        {
            curr_hex = string[i] - 'A' + 10;
        }
        else
        {
            curr_hex = string[i] - '1' + 1;
        }
        mult = sizeof(int) * ((sizeof(int) * 2) - i - 1);
        curr_hex <<= mult;
        as_hex |= curr_hex;
    }
    mult = sizeof(int) * ((sizeof(int) * 2) - length);
    as_hex >>= mult;
    errno = 0;
    return as_hex;
}

int bit(void * byte, int bit_index)
{
    unsigned int mask = 0x1 << bit_index;
    unsigned int bit = ((unsigned int *)byte)[0] & mask;
    return bit;
}

void reverse_bits(void * hex, int length)
{
    int i, j;
    // Walk through the length given
    for (i = length - 1; i >= 0; --i)
    {
        unsigned char current = ((unsigned char *)hex)[i];
        for (j = 0; j < 8; ++j)
        {
            current = swap_bits(((unsigned char *)hex)[i], 7 - j, j);
            printf("byte: %02x\tnum: %d\tswap: %d\t%d\n", current, i, 7 -j, j);
            /* code */
        }
    }
    return;
}

