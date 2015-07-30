/*
	Author: John Andersen
	Date: 11/5/2014
	Description: General functions I always use
*/
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cctype>
#include <sys/ioctl.h>
#include <unistd.h>


#ifndef GEN
	#define GEN 1

// General functions I always use
namespace gen
{
	// So I don't have to define in every program
	const unsigned int STRING_SIZE = 255;
	// A class for naming functions
	// class functions;
	// Capitalises the first letter of every word
	void capitalize( char *cap_me );
	// Make every letter in a string lowercase
	void tolower( char * lower );
	// Capitalises every letter in a string
	void toupper( char * cap_me );
	// Capitalises a char by reference
	void toupper( char & cap_me );
	// Clears a string
	void strclr( char *clear );
	// Removes all instances of a character in a string
	void remove_char( char * input, char remove_char );
	// Removes all of a leading charater
	void remove_leading( char * input, char remove_char );
	// Removes all whitespace in a string
	void remove_whitespace( char * input );
	// Removes all double, triple, etc spaces
	void remove_multi_whitespace( char * input );
	// Calls remove_multi_whitespace and capitalize
	void error_check( char * input );
	// Splits a line into two baised on the delim
	void split_line( const char * line, char * first, char * second, const char delim );
	// Askes yes or no, true if yes / y
	bool confirm();
	// Prints "ask" then gets a response and stores it in "response"
	void get_line( const char * ask, char * response, unsigned int response_size );
	// Checks if the string is a number data type
	bool number( char * string );
	// Checks if all values in a string are numbers
	bool is_int( char * string );
	// Checks if all values in a string are numbers or decimal point
	bool is_float( char * string );
	// Counts the occurences of a char in a string
	int count( char * string, const char delim );
	// Formats csv columns
	void add_to_csv( int column_position, int column_count, char * string, char * add, const char delim );
	// Creates a line across the screen
	void line( const char character );
	// Forks off and returns true if its the child
	int thread( void );
	// Adds up the ascii values of chars in an string
	int strval( char * string );
	// Selects appropriate function to call or exits
	// bool handle_input( gen::functions );
}

namespace color
{
	const char normal[] = "\e[m";
	const char black[] = "\e[30m";
	const char red[] = "\e[31m";
	const char green[] = "\e[32m";
	const char yellow[] = "\e[33m";
	const char purple[] = "\e[34m";
	const char pink[] = "\e[35m";
	const char blue[] = "\e[36m";
	const char grey[] = "\e[90m";
	const char lightred[] = "\e[91m";
	const char lightgreen[] = "\e[92m";
	const char lightyellow[] = "\e[93m";
	const char lightpurple[] = "\e[94m";
	const char lightpink[] = "\e[95m";
	const char lightblue[] = "\e[96m";
}

namespace highlight
{
	const char normal[] = "\e[m";
	const char black[] = "\e[40m";
	const char red[] = "\e[41m";
	const char green[] = "\e[42m";
	const char yellow[] = "\e[44m";
	const char purple[] = "\e[44m";
	const char pink[] = "\e[45m";
	const char blue[] = "\e[46m";
	const char grey[] = "\e[100m";
	const char lightred[] = "\e[101m";
	const char lightgreen[] = "\e[102m";
	const char lightyellow[] = "\e[103m";
	const char lightpurple[] = "\e[104m";
	const char lightpink[] = "\e[105m";
	const char lightblue[] = "\e[106m";
}

#endif