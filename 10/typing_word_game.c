// #include "gen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>


#define WORDS_LENGTH 9
const char * const words[] = { "The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog" };
int used_words [ WORDS_LENGTH ];
int starting_index;

// Prototypes
int readline( char * buffer, int max );
int random_word( void );
void guess( const char * word, struct timeval * total );
void init( void );
void print_time( struct timeval * print );

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

// Picks the index of a word at random from words array
int random_word( void )
{
	// I had a loop here and an array of words used
	// but I saw that a decreaing mod was also acceptable
	// I did an increasing one. I think this is what you meant.
	int index = starting_index % WORDS_LENGTH;
	++starting_index;
	return index;
	// Old version, changed because probably uses rand too much
	// but it creates a more random sequence
	/*
	int used = 1;
	int index = rand() % words_length;
	while ( used )
	{
		if ( !used_words[ index ] )
		{
			used_words[ index ] = 1;
			used = 0;
		}
		else
		{
			index = rand() % words_length;
		}
	}
	return index;
	*/
}

// Asks the user to guess a word and adds the time it took
// them to guess on to total
void guess( const char * word, struct timeval * total )
{
	// Holds the start and end times as well as the difference
	// in them which will be added to the total
	struct timeval start, end, diff;
	// Whether the word was typed correctly
	int correct = 0;
	// User input string
	char input [ 100 ];
	// Get the time this trail started
	gettimeofday( & start, NULL );
	// Ask until the user types the correct word
	do
	{
		// Fromat the question
		sprintf( input, "Type: \"%s\": ", word );
		// Ask the question / to type
		write( STDOUT_FILENO, input, strlen( input ) );
		// Get the users input
		readline( input, strlen( word ) + 1 );
		// Make sure it is the right word
		if ( 0 == strncmp( word, input, strlen( word ) ) )
		{
			// If correct then loop exits
			correct = 1;
		}
	}
	while ( !correct );
	// Check when they got it right
	gettimeofday( & end, NULL );
	// See how long it took to get the word right
	timersub( & end, & start, & diff );
	// Add how long this word took to the total
	timeradd( total, & diff, total );
	return;
}

// Set all indecies to 0 for not used yet
// used for old verion of random word
void init( void )
{
	int i;
	// Loop through set all to 0
	for ( i = 0; i < WORDS_LENGTH; ++i )
	{
		used_words[ i ] = 0;
	}
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

int main( int argc, char const *argv[] )
{
	// Used in old random method
	// init();
	// For the number of  words guessed
	int i;
	// How long it took
	struct timeval length;
	// For seeding rand
	gettimeofday( & length, NULL );
	// Seed rand with call to srand
	srand( length.tv_usec );
	// Set values to zero, because this will
	// now hold the differnece
	length.tv_sec = 0;
	length.tv_usec = 0;
	// Set the starting index for new random method
	starting_index = rand() % WORDS_LENGTH;
	// Guess / type all the words
	for ( i = 0; i < WORDS_LENGTH; ++i )
	{
		// Make the user type a random word
		guess( words[ random_word() ], & length );
	}
	// Tell them how long they took
	printf( "You took " );
	print_time( & length );
	printf( "\n" );
	// Return clean exit
	return 0;
}

