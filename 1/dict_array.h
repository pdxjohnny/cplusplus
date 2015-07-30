/*
	Author: John Andersen
	Date: 11/4/2014
	Description: dict_array class with use of templates to allow any kind
		of data to be stored in a n array of fixed size sorted by key.
*/

#include <iostream>
#include <cstdio>
#include <cstring>

// For NULL
#ifndef NULL
	#define NULL 0
#endif


#ifndef DICT_ARRAY_SIZE
	#define DICT_ARRAY_SIZE 3


/*
	Class: dict_array
	Use: This class contains arrays of keys and values and
		lairs the keys with the values and sort them on key
*/
template <typename data_type>
class dict_array
{
public:
	// Inistialises data members
	dict_array();
	// Inistialises data members
	dict_array( unsigned int max );
	// Deletes the data it holds
	~dict_array();
	// Inistialises data members
	void init( unsigned int max );
	// Resets all the data members
	void reset( void );
	// Returns the array_size
	int size( void );
	// If array is full
	bool full( void );
	// If the key is present
	bool contains( char * key );
	// Returns all the keys
	char ** keys( void );
	// Removes a key, vleuas value untouched
	bool remove( char * key );
	// Sorts based on keys
	int sort( void );
	// If a key is alpabeticly higher than the final key
	bool belongs( char * key );
	// Copys the last key
	char * pop_key( void );
	// Pointer to the last value
	data_type * pop( void );
	// Gets the index, in terms of what is used
	data_type * get( unsigned int index );
	// Gets the key
	data_type * get( char * key );
	// Adds a new key and sorts
	data_type * insert( char * key );
	// Prints the keys and values
	void print( void );
	// Get members, shorthand for get methods
	data_type * operator[]( char * key );
	data_type * operator[]( unsigned int index );


private:
	// Array of data
	data_type * array;
	// Keys
	char ** item_keys;
	// Open positions
	bool * open;
	// The size of the array
	unsigned int max_size;
	// The number of items in the array
	unsigned int array_size;
	// The position in the array
	unsigned int first_open;
};

// Include all of the methods for getting and setting variables.
#include "dict_array.cpp"
// This is intentionally included, explination in is dlist.h

#endif