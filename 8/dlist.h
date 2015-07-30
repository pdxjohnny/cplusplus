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

// The class which wraps the data with next and previous pointers.
#include "list_el.h"


/*
	Class: dlist
	Use: Stores all of the list_els and methods to
		acess and insert them into a linked list;
*/
template <class data_value>
class dlist
{
public:
	// Constructor and deconstructor
	dlist<data_value>();
	~dlist<data_value>();
	// Allows access to the elements by their position
	data_value *operator[]( unsigned int num );
	// Method to access the head of the list
	list_el<data_value> *get_head( void );
	// Method to access the tail of the list
	list_el<data_value> *get_tail( void );
	// Returns the number of elements in the list
	unsigned int size( void );
	// Inserts a data of the list type into the list
	int insert( data_value *data );
	// NOT YET IMPLEMENTED
	// Fixes the list on list_el deletion
	// void list_el_deleted( unsigned int position );
private:
	// Used to store the first element in the list
	list_el<data_value> *head;
	// Used to store the last element in the list
	list_el<data_value> *tail;
	// Used to store the number of elements in the list
	unsigned int list_size;
};

// Include the methods for the dlist class.
#include "dlist.cpp"
// This is intentionally included
/*
	Explination:
	I understand that I'm not supposed to include cpp files
	but I don't know how else to make this work.
	The point of this is to be able to put anything in the
	dlist. However if the implementaion of the list_el and
	dlist fuctions are not included in whatever the program
	may be it cannot, to my knowledge, take full advantage
	of the use of templates. My understanding of templates
	is that they are a placeholder for the compilier to then
	create a new instance of the class / struct where a
	template was used and insert the data type that was
	used in the template's place. If I compile all the .o
	files together then it can't use any data type because
	when the dlist.o file was compiled it didn't know all
	the data types that might replace the template in the
	full implementation of the program.

	If you could help me understand a way to get around this
	then I'd appricate hearing it beacuse I couldn't find
	anything other than puting a:
	template class dlist<data_type>;
	for every data_type I want a dlist of at the end of this
	or the .cpp file of this. Which defeats the purpose of
	this. I'm sure there is a way because I can have vecotrs
	of anything, I just haven't figured it out.

	Edit: I talked to Karla and she said this is the only way
*/
