#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>


int readline( char * buffer, int max );
int freadline( char * buffer, int max, FILE * source );
void print_time( struct timeval * print );
int read_byte( FILE * source, char * buffer );
void print_hex(void * hex, int length);
char swap_bits( char byte, int one, int two );
void strnclr( char * buffer, int length );
// Ascii to hex
unsigned int atoh( char * string );  
// State of bit, 1 or 0
int bit(void * byte, int bit_index);
void reverse_bits(void * hex, int length);

