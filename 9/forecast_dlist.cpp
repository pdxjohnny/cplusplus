/*
	Author: John Andersen
	Date: 11/8/2014
	Description: dlist class methods
*/

#include "dlist.h"
#include "forecast.h"


/*
	Class: dlist
	Method: insert
	Use: Inserts into the list based on the val
		That's only because I want to leave it
		like this for now. The val isn't nesisary
*/
template <>
int dlist<forecast>::insert( forecast * data )
{
	// Allocate memory for a new list_el object
	list_el<forecast> *newcurr = new list_el<forecast>;
	// Set the data of the new list_el to the data passed in
	newcurr->set_data( data );
	// Set the val of the new list_el object to the size of the list
	newcurr->set_val( this->size() );

	// If head is NULL we know that this is the first element in the list
	if ( head == NULL )
	{
		// Set the begining of the list to newcurr
		head = newcurr;
		// Set the end of the list to newcurr
		tail = newcurr;
		// This is because it is the only element in the list
	}
 	// If the value of newcurr is less that that of head then we know that
 	// newcurr should become head
	else if ( 0 <= strcmp( head->get_data()->weather(), data->weather() ) )
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
	else if ( 0 > strcmp( tail->get_data()->weather(), data->weather() ) )
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
		list_el<forecast> * walker;
		// Make that walker the head of the list
		walker = head;
		// As long as the value of newcurr is greater than
		// that of the next element we need to keep walking
		while( 0 > strcmp( walker->get_data()->weather(), data->weather() ) )
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
