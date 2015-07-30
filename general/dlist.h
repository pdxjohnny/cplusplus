/*
	Author: John Andersen
	Date: 11/8/2014
	Description: dlist class with use of list_el class
		Templates are used to store any data type in the
		list
*/


// For NULL
#ifndef NULL
	#define NULL 0
#endif

// So we know if we are using a dlist
#ifndef DLIST
	#define DLIST 1
#endif

// The class which wraps the data with next and previous pointers.
#include "list_el.h"


/*
	Class: dlist
	Use: Stores all of the list_els and methods to
		acess and insert them into a linked list;
*/
template <typename data_type>
class dlist
{
public:
	// Constructor and deconstructor
	dlist<data_type>();
	~dlist<data_type>();
	// Allows access to the elements by their position
	data_type &operator[]( unsigned int num );
	// Method to access the head of the list
	list_el<data_type> *get_head( void );
	// Method to access the tail of the list
	list_el<data_type> *get_tail( void );
	// Returns the number of elements in the list
	unsigned int size( void );
	// Inserts a data of the list type into the list
	int insert( data_type *data );
	// Removes an element from the array
	bool remove( unsigned int num );
private:
	// Used to store the first element in the list
	list_el<data_type> *head;
	// Used to store the last element in the list
	list_el<data_type> *tail;
	// Used to store the number of elements in the list
	unsigned int list_size;
};

// Include the methods for the dlist class.
#include "dlist.cpp"
// This needs to be included so that the
// template will be replaced with the data_type
// that is being used at compile time
