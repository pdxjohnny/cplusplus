/*
	Author: John Andersen
	Date: 01/15/2015
	Description: dict class with use of list_el class
		Templates are used to store any data type in the
		list
*/


// For NULL
#ifndef NULL
	#define NULL 0
#endif

// So we know if we are using a dict
#ifndef DICT_DICT_ARRAY
	#define DICT_DICT_ARRAY 1


#include <cstdio>
#include <cstdlib>
#include <cstring>

// The class which wraps the data with next and previous pointers.
#include "list_el.h"
// The dictionarys
#include "dict_array.h"


/*
	Class: dict_dict_array
	Use: Stores all of the list_els and methods to
		acess and insert them into a linked list;
*/
template <typename data_type>
class dict_dict_array
{
public:
	// Constructor and deconstructor
	dict_dict_array<data_type>();
	~dict_dict_array<data_type>();
	// Allows access to the elements by their position
	data_type & operator[]( unsigned int num );
	// Allows access by key value
	data_type & operator[]( char * key );
	// Allows access to the elements by their position
	data_type & get( int num );
	// Allows access by key value
	data_type & get( char * key );
	// Check if index is present
	bool contains( unsigned int num );
	// Check if key is present
	bool contains( char * key );
	// Method to access the head of the list
	list_el< dict_array <data_type> > *get_head( void );
	// Method to access the tail of the list
	list_el< dict_array <data_type> > *get_tail( void );
	// Returns the number of elements in the list
	unsigned int size( void );
	// Returns the keys of the elements in the list
	char ** keys( void );
	// Prints the keys and values
	void print( void );
	// Inserts a data of the list type into the list
	data_type * insert( char * key ); //, data_type data );
	// Appends a node of the end of the list
	data_type * append( char * key ); //, data_type data );
	// Removes an element from the array
	bool remove( char * key );
	// Meant to be overloaded for a specialised insance
	unsigned int save_file( char * file_name, const char delim );
	// Meant to be overloaded for a specialised insance
	unsigned int load_file( char * file_name, const char delim );
private:
	// Used to store the first element in the list
	list_el< dict_array <data_type> > * head;
	// Used to store the last element in the list
	list_el< dict_array <data_type> > * tail;
	// Used to store the number of elements in the list
	unsigned int list_size;
	// Append or insert
	int should_append;
};

// Include the methods for the dict_dict_array class.
#include "dict_dict_array.cpp"
// This needs to be included so that the
// template will be replaced with the data_type
// that is being used at compile time

#endif