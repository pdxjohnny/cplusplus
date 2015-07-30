/*
	Author: John Andersen
	Date: 11/5/2014
	Description: General functions I always use
*/
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cctype>


#ifndef GENERAL_INCLUDED
	#define GENERAL_INCLUDED TRUE
#endif

// General functions I always use
namespace gen
{
	// So I don't have to define in every program
	const unsigned int STRING_SIZE = 255;
	// Capitalises the first letter of every word
	void capitalize( char *cap_me );
	// Capitalises every letter in a string
	void toupper( char *cap_me );
	// Capitalises a char by reference
	void toupper( char &cap_me );
	// Clears a string
	void strclr( char *clear );
	// Removes all instances of a character in a string
	void remove_char( char *input, char remove_char );
	// Removes all of a leading charater
	void remove_leading( char *input, char remove_char );
	// Removes all whitespace in a string
	void remove_whitespace( char *input );
	// Removes all double, triple, etc spaces
	void remove_multi_whitespace( char *input );
	// Calls remove_multi_whitespace and capitalize
	void error_check( char *input );
	// Splits a line into two baised on the delim
	void split_line( const char *line, char *first, char *second, const char delim );
	// Askes yes or no, true if yes / y
	bool confirm();
	// Prints "ask" then gets a response and stores it in "response"
	void get_line( const char *ask, char* response, unsigned int response_size );
}
