/*
	Author: John Andersen
	Date: 11/4/2014
	Description: list_el class with use of templates to allow any kind
		of data to be stored in a linked list.
*/


// For NULL
#ifndef NULL
	#define NULL 0
#endif


/*
	Class: list_el
	Use: This class wraps its member, data
		It added pointers to list_el's of the
		Same data type for use in dlist
*/
template <class data_value>
class list_el
{
public:
	// Inistialises pointers
	list_el();
	// Deletes the data it holds
	~list_el();
	// Set the private variables
	void set_val( unsigned int val);
	void set_data( data_value *data );
	void set_next( list_el<data_value> *next);
	void set_prev( list_el<data_value> *prev);

	// Get the private variables
	unsigned int get_val(void);
	data_value *get_data(void);
	list_el<data_value> *get_next(void);
	list_el<data_value> *get_prev(void);

private:
	// The position in the list
	unsigned int val;
	// The data which this wraps
	data_value *data;
	// The next element in the list
	list_el<data_value> *next;
	// The previous element in the list
	list_el<data_value> *prev;
};

// Include all of the methods for getting and setting variables.
#include "list_el.cpp"
// This is intentionally included, explination in is dlist.h
