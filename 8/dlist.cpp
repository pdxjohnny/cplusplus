/*
	Author: John Andersen
	Date: 11/8/2014
	Description: dlist class methods
*/

// #include "dlist.h"
// This is intentionally commented out
// explination in is dlist.h


/*
	Class: dlist
	Method: Constructor
	Use: Initializes the members
*/
template <class data_value>
dlist<data_value>::dlist()
{
	// Set the head and tail pionters to NULL
	// because there is no list yet
	this->head = NULL;
	this->tail = NULL;
	// Set the list size to 0 because there is
	// no list yet
	this->list_size = 0;
};


/*
	Class: dlist
	Method: deconstructor
	Use: Deletes all the list_el's in the list
		These will delete the data they contain
*/
template <class data_value>
dlist<data_value>::~dlist()
{
	// Create a pointer to walk the list
	list_el<data_value> *walker = this->get_head();
	// Create a pointer to delete items in the list
	list_el<data_value> *deallocator = NULL;
	// Walk until the end or the number is reached
	while ( walker )
	{
		// Make the deallocator the walker
		deallocator = walker;
		// Make the walker the next litem in the list
		walker = walker->get_next();
		// Delete the list_el
		// Deleting it will call its deconstructor
		// and delete the data it points to
		delete deallocator;
	}
};


/*
	Class: dlist
	Operator: []
	Use: Gets the element that is that number in the list
*/
template <class data_value>
data_value *dlist<data_value>::operator[]( unsigned int num )
{
	// Create a pointer to walk the list
	list_el<data_value> *walker = this->get_head();
	// Walk until the end or the number is reached
	for ( unsigned int i = 0; walker && i < num; ++i )
	{
		// Make the walker the next litem in the list
		walker = walker->get_next();
	}
	// Return the data of the walker not the list_el
	return walker->get_data();
}


/*
	Class: dlist
	Method: get_head
	Use: Returns the pointer to head
*/
template <class data_value>
list_el<data_value> *dlist<data_value>::get_head( void )
{
	return this->head;
}


/*
	Class: dlist
	Method: get_tail
	Use: Returns the pointer to tail
*/
template <class data_value>
list_el<data_value> *dlist<data_value>::get_tail( void )
{
	return this->tail;
}


/*
	Class: dlist
	Method: size
	Use: Returns the number of elements in the list
*/
template <class data_value>
unsigned int dlist<data_value>::size( void )
{
	return this->list_size;
}


/*
	Class: dlist
	Method: insert
	Use: Inserts into the list based on the val
		That's only because I want to leave it
		like this for now. The val isn't nesisary
*/
template <class data_value>
int dlist<data_value>::insert( data_value *data )
{
	// Allocate memory for a new list_el object
	list_el<data_value> *newcurr = new list_el<data_value>;
	// Set the data of the new list_el to the data passed in
	newcurr->set_data( data );
	// Set the val of the new list_el object to the size of the list
	newcurr->set_val( this->size() );
	// Create x and set it to the value of newcurr
	// This just makes the code read better
	unsigned int x = newcurr->get_val();

	// If head is NULL we know that this is the first element in the list
	if( head == NULL )
	{
		// Set the begining of the list to newcurr
		head = newcurr;
		// Set the end of the list to newcurr
		tail = newcurr;
		// This is because it is the only element in the list
	}
 	// If the value of newcurr is less that that of head then we know that
 	// newcurr should become head
	else if( x <= head->get_val() )
	{
		// newcurr needs to know that the next element is the current head
		newcurr->set_next(head);
		// newcurr needs to know that nothing is smaller than it
		newcurr->set_prev(NULL);
		// head needs to know that there is now something smaller than it
		head->set_prev(newcurr);
		// The head of the list becomes newcurr because it is the
		// smallest element
		head = newcurr;
	}
 	// If the value of newcurr is greater than the tail then it is the tail
	else if( x > tail->get_val() )
	{
		// The tail needs to know that newcurr is larger than it
		tail->set_next(newcurr);
		// newcurr needs to know that tail is smaller than it
		newcurr->set_prev(tail);
		// newcurr needs to know that there is nothing larger than it
		newcurr->set_next(NULL);
		// The newcurr becomes the tail because it is the largest element
		tail = newcurr;
	}
	// If the value of newcurr is somewhere inbetween then we need to
	// find when in the list it belongs
	else
	{
		// Create a walker to go through the list
		list_el<data_value> *walker;
		// Make that walker the head of the list
		walker = head;
		// As long as the value of newcurr is greater than
		// that of the next element we need to keep walking
		while( x > walker->get_val() )
		{
			// Make the walker thenext element in the list
			walker = walker->get_next();
		}
		// The loop exits when the value of newcurr is no longer
		// bigger than the value of the element which walker is.
		// This means that it belongs at this spot in the list
		// because it is greater than the previous walkers number
		// and smaller than the current number

		// The item before the walker should now point to the
		// list_el which is nuwcurr as the next value in the list
		// becaues newcurr is larger than it
		walker->get_prev()->set_next(newcurr);
		// Then newcurr needs to know that the element before it
		// is the current / walker elements previous because the
		// newcurr is larger than it
		newcurr->set_prev(walker->get_prev());
		// The newcurr also needs to know what is bigger han it
		// which is the current element walker points to
		newcurr->set_next(walker);
		// Finally walker needs to know that newcurr is the element
		// which comes before it
		walker->set_prev(newcurr);
	}

	// Increment the size of the list because we just added an element
	++this->list_size;

	// Return how many elsements are in the list
	return this->list_size;
}
