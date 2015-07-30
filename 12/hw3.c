#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>


int readline( char * buffer, int max );
int freadline( char * buffer, int max, FILE * source );
void print_time( struct timeval * print );
int read_byte( FILE * source, char * buffer );
void print_hex( char * hex, int length );
char swap_bits( char byte, int one, int two );
void strnclr( char * buffer, int length );
void stage_1( char * encypted, char * decypted );
void stage_2( char * encypted, char * decypted );
void stage_3( char * encypted, char * decypted );
void change( char * encrypt );
int pow( int base, int raise );


int pow( int base, int raise )
{
    int i, res = 1;
    for ( i = 0; i < raise; ++i )
    {
        res *= base;
    }
    return res;
}


// Reads a line into a buffer from stdin
int readline( char * buffer, int max )
{
	// Index in buffer array
	int i, j = 1;
	// Current character
	char tmp;
	// Read until newline or max - 1 for NULL terminate
	for ( i = 0; i < max - 1 && j; ++i )
	{
		// Read in a character
		j = read( STDIN_FILENO, & tmp, 1 );
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
		j = read( STDIN_FILENO, & tmp, 1 );
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

void print_hex( char * hex, int length )
{
    int i;
    for ( i = 0; i < length; ++i )
    {
        printf("%02x", hex[i]);
        if ( ( i + 1 ) % 2 == 0 )
        {
            printf(" ");
        }
    }
    return;
}

char swap_bits( char byte, int one, int two )
{
    char tmp_1, tmp_2, swap;
    int hex_1 = pow(2, one);
    int hex_2 = pow(2, two);
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


void stage_1( char * encypted, char * decypted )
{
    // c0, c1, c2, c3
    // ‘a’ to ‘d’: Swap bytes c0 and c3.
    decypted[0] = encypted[3];
    decypted[1] = encypted[1];
    decypted[2] = encypted[2];
    decypted[3] = encypted[0];
    return;
}

void stage_2( char * encypted, char * decypted )
{
    // b7, b6, b5, b4, b3, b2, b1, b0
    // ‘m’ to ‘p’: Swap bits b5 and b1, Swap bits b4 and b0.
    int i;
    // char tmp, mask_1 = 0x30, mask_2 = 0x03;
    for ( i = 0; i < 4; ++i )
    {
        decypted[i] = swap_bits(encypted[i], 5, 1);
        decypted[i] = swap_bits(decypted[i], 4, 0);
    }
    return;
}

void stage_3( char * encypted, char * decypted )
{
    // c0, c1, c2, c3
    // ‘a’ to ‘d’: XOR bytes c0 and c3 with k3.
    char k = 'd';
    decypted[0] = encypted[0] ^ k;
    decypted[1] = encypted[1];
    decypted[2] = encypted[2];
    decypted[3] = encypted[3] ^ k;
    return;
}

void change( char * encrypt )
{
    char decrypt [4];
    stage_1( encrypt, decrypt );
    stage_2( decrypt, encrypt );
    stage_3( encrypt, decrypt );
    strncpy( encrypt, decrypt, 5 );
    return; 
}


#ifndef MAX_STRING
    #define MAX_STRING 2048
#endif

int read_file( FILE * source, char * buffer )
{
    int num_read = 0;
    char current;
    char encrypt [4], decrypt [4];
    while (!feof(source) && read_byte( source, &current ) > 0 && num_read < MAX_STRING )
    {
        // Read one byte
        encrypt[ num_read % 4 ] = current;
        ++num_read;
        if ( ( num_read % 4 ) == 0 )
        {
            change( encrypt );
            strcat(buffer, encrypt);
            strnclr( encrypt, 4 );
        }
    }
    if ( ( num_read % 4 ) != 0 )
    {
        stage_2( encrypt, decrypt );
        strcat(buffer, decrypt);
    }
    return num_read;
}

int main ( int argc, char ** argv )
{
	char filename [5];
	if ( argc < 2 )
    {
        printf("Usage %s file_to_decrypt\n", argv[0]);
        exit(0);
    }
    strncpy( filename, argv[1], 5 );
	FILE * source = fopen(filename, "rb");
	if (!source)
	{
		printf("Failed to open \"%s\"\n", filename );
		return 1;
	}
	else
    {
        char message [ MAX_STRING ];
        if ( read_file( source, message ) )
        {
            printf("%s", message);
        }
    }
    fclose(source);
    return 0;
}



