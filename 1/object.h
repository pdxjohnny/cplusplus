/*
	Author: John Andersen
	Date: 01/15/2015
	Description: object class definition
*/

#include "gen.h"
#include "dict.h"
#include "dict_dict_array.h"
#include <cstdio>
#include <fstream>

/*
	Class: object
	Use: Holds a object and the scource is it assinged to
*/
class object
{
public:
	~object();
	// Returns the weather source
	char *weather( void );
	// Gives access to a member
	void * operator[]( char * key );
	// Parses a csv string into data members
	void from_string( char * key,  char * value, const char delim );
	// Sets the value to the appropriate dictionary
	bool set( char * key, char * value );
	bool set( char * key, int value );
	bool set( char * key, float value );
	// Use: Tests if value is present
	bool contains( char * key );
	// Prompts user for the values of data members
	void prompt( char * keys, char delim );
	// Creates a string of the class in json format
	void print( void );
	// Length of the value if ine string format
	unsigned int value_length( char * key );
	// Length of all the values for the given keys
	unsigned int length_of_values( char * keys, char delim );
	// Converts value to string and formats
	void value_string( char * value, char * key );
	// Creates a string of the class in csv format
	char * to_string( char * format, char delim );
	// Removes a key value pair
	void remove( char * key );
	// Adds up all the sizes of dictionaries
	int size( void );
	// The length of all the keys seperated by a delim
	unsigned int keys_length( void );
	// All the keys seperated by a delim
	char * keys( const char delim );
	// All the keys in an array
	char ** keys( void );
protected:
	// Int data types
	dict_dict_array<int> ints;
	// Float data types
	dict_dict_array<float> floats;
	// String data types
	dict_dict_array<char *> strings;
	/*
	// Int data types
	dict<int> ints;
	// Float data types
	dict<float> floats;
	// String data types
	dict<char *> strings;
	*/
};
