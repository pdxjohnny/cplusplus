/*
	Author: John Andersen
	Date: 01/15/2015
	Description: dict_dict_array class methods
*/

// #include "dict_dict_array.h"
// This is intentionally commented out
// explination in is dict_dict_array.h


/*
	Class: dict_dict_array
	Method: Constructor
	Use: Initializes the members
*/
template <typename data_type>
dict_dict_array<data_type>::dict_dict_array()
{
	// Set the head and tail pionters to NULL
	// because there is no list yet
	this->head = NULL;
	this->tail = NULL;
	// Set the list size to 0 because there is
	// no list yet
	this->list_size = 0;
	// Append unless otherwise specified
	this->should_append = 0;
};


/*
	Class: dict_dict_array
	Method: deconstructor
	Use: Deletes all the list_el's in the list
		These will delete the data they contain
*/
template <typename data_type>
dict_dict_array<data_type>::~dict_dict_array()
{
	// Create a pointer to walk the list
	list_el< dict_array <data_type> > * walker = this->get_head();
	// Create a pointer to delete items in the list
	list_el< dict_array <data_type> > * deallocator = NULL;
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
	Class: dict_dict_array
	Operator: []
	Use: Gets the element that is that number in the list
*/
template <typename data_type>
data_type & dict_dict_array<data_type>::operator[]( unsigned int num )
{
	return this->get( num );
}


/*
	Class: dict_dict_array
	Operator: []
	Use: Gets the element that is that number in the list
*/
template <typename data_type>
data_type & dict_dict_array<data_type>::operator[]( char * key )
{
	return this->get( key );
}


/*
	Class: dict_dict_array
	Operator: []
	Use: Gets the element that is that number in the list
*/
template <typename data_type>
data_type & dict_dict_array<data_type>::get( int num )
{
	// Create a pointer to walk the list
	list_el< dict_array <data_type> > * walker = this->get_head();
	// Create a pointer to the data type which we will return
	data_type * found = NULL;
	// The position in all of the arrays
	int position = 0;
	// Walk until the end or the number is reached
	while ( walker && !found )
	{
		// Look for the tiem in the array
		if ( num - position < walker->get_data()->size() )
		{
			found = walker->get_data()->get( num - position );
		}
		// Make the walker the next item in the list
		position += walker->get_data()->size();
		walker = walker->get_next();
	}
	if ( !found )
	{
		char key[11];
		sprintf( key, "%d", num );
		if ( this->should_append )
		{
			found = this->append( key );
		}
		else
		{
			found = this->insert( key );
		}
	}
	return * found;
}



/*
	Class: dict_dict_array
	Operator: []
	Use: Gets the element that is that number in the list
*/
template <typename data_type>
data_type & dict_dict_array<data_type>::get( char * key )
{
	// Create a pointer to walk the list
	list_el< dict_array <data_type> > * walker = this->get_head();
	// Create a pointer to the data type which we will return
	data_type * found = NULL;
	// Walk until the end or the number is reached
	while ( walker && !found )
	{
		// Look for the key in the array
		if ( walker->get_data()->contains( key ) )
		{
			found = walker->get_data()->get( key );
		}
		// Make the walker the next item in the list
		walker = walker->get_next();
	}
	if ( !found )
	{
		if ( this->should_append )
		{
			found = this->append( key );
		}
		else
		{
			found = this->insert( key );
		}
	}
	return * found;
}



/*
	Class: dict_dict_array
	Method: contains
	Use: Checks if index is in list
*/
template <typename data_type>
bool dict_dict_array<data_type>::contains( unsigned int num )
{
	if ( num < this->list_size )
	{
		return true;
	}
	return false;
}


/*
	Class: dict_dict_array
	Method: contains
	Use: Checks if key is in list
*/
template <typename data_type>
bool dict_dict_array<data_type>::contains( char * key )
{
	// Create a pointer to walk the list
	list_el< dict_array <data_type> > * walker = this->get_head();
	// Create a pointer to the data type which we will return
	bool found = false;
	// Walk until the end or the number is reached
	while ( walker && !found )
	{
		// Look for the tiem in the array
		if ( walker->get_data()->contains( key ) )
		{
			found = true;
		}
		// Make the walker the next item in the list
		walker = walker->get_next();
	}
	return found;
}


/*
	Class: dict_dict_array
	Method: get_head
	Use: Returns the pointer to head
*/
template <typename data_type>
list_el< dict_array <data_type> > * dict_dict_array<data_type>::get_head( void )
{
	return this->head;
}


/*
	Class: dict_dict_array
	Method: get_tail
	Use: Returns the pointer to tail
*/
template <typename data_type>
list_el< dict_array <data_type> > * dict_dict_array<data_type>::get_tail( void )
{
	return this->tail;
}


/*
	Class: dict_dict_array
	Method: size
	Use: Returns the number of elements in the list
*/
template <typename data_type>
unsigned int dict_dict_array<data_type>::size( void )
{
	return this->list_size;
}



/*
	Class: dict_dict_array
	Method: keys
	Use: Returns the number of elements in the list
*/
template <typename data_type>
char ** dict_dict_array<data_type>::keys( void )
{
	// Create the array of strings
	char ** keys = new char*[ this->list_size ];
	// Create a pointer to walk the list
	list_el< dict_array <data_type> > * walker = this->get_head();
	// The key number you are on
	unsigned int key = 0;
	// The keys for each dict_array
	char ** walker_keys;
	// Walk until the end or the number is reached
	while ( walker )
	{
		// Fetch the keys for that dict_array
		walker_keys = walker->get_data()->keys();
		for ( unsigned int i = 0; i < walker->get_data()->size(); ++i )
		{
			// Create a new string
			keys[ key ] = new char[ strlen( walker_keys[ i ] ) + 1 ];
			// Copy over the strings data
			strcpy( keys[ key ], walker_keys[ i ] );
			// Increment the real key we are on
			++key;
			delete [] walker_keys[ i ];
		}
		delete [] walker_keys;
		// Make the walker the next item in the list
		walker = walker->get_next();
	}
	return keys;
}



/*
	Class: dict_dict_array
	Method: print
	Use: Prints all of the keys and values
*/
template <typename data_type>
void dict_dict_array<data_type>::print( void )
{
	char ** keys = this->keys();
	for ( unsigned int i = 0; i < this->size(); ++i )
	{
		std::cout << keys[ i ] << '\t' << this->get( i ) << '\n';
		delete [] keys[ i ];
	}
	delete [] keys;
}



/*
	Class: dict_dict_array
	Method: insert
	Use: Inserts into the list based on the val
		That's only because I want to leave it
		like this for now. The val isn't nesisary
*/
template <typename data_type>
data_type * dict_dict_array<data_type>::insert( char * key ) //, data_type data )
{
	// Allocate memory for a new list_el dict_dict_array
	// list_el< dict_array <data_type> > * newcurr = new list_el< dict_array <data_type> >;
	// Set the key of the new list_el to the key passed in
	// newcurr->set_key( key );
	// Set the data of the new list_el to the data passed in
	// newcurr->set_data( data );

	data_type * value = NULL;

	// If head is NULL we know that this is the first element in the list
	if ( head == NULL )
	{
		// Set the begining of the list to newcurr
		head = new list_el< dict_array <data_type> >;
		// Set the end of the list to newcurr
		tail = head;
		// This is because it is the only element in the list
		// Get the key from the first nodes array
		value = head->get_data()->get( key );
	}
	// If the value of newcurr is somewhere inbetween then we need to
	// find when in the list it belongs
	else
	{
		// Create a walker to go through the list
		list_el< dict_array <data_type> > * walker = head;
		// As long as the value of newcurr is greater than
		// that of the next element we need to keep walking
		while( !value && walker && walker->get_data()->full() )
		{
			// The array is full but the key belongs here
			if ( walker->get_data()->belongs( key ) )
			{
				// We need to take out the last key and find where it
				// belongs then insert there
				// std::cout << "POP from walker\n";
				// std::cout << "\nPrinting " << this->size() << '\n';
				// this->print();
				// std::cout << "Finished printing " << this->size() << "\n";
				// std::cout << key << " belongs in :\n";
				// walker->get_data()->print();
				data_type * pop = walker->get_data()->pop();
				char * pop_key = walker->get_data()->pop_key();
				// Remove the key we've fixed, this does nothing to
				// the data in that space
				walker->get_data()->remove( pop_key );
				// std::cout << "Removed " << pop_key << " :\n";
				// walker->get_data()->print();
				// Insert now that there's space, just sets the key
				value = walker->get_data()->get( key );
				// exit(1);
				// Find the one that we just removeds place
				// std::cout << "RECURSIVE GET " << pop_key << '\n';
				data_type * new_pop = & this->get( pop_key );
				// std::cout << "END OF RECURSIVE GET " << pop_key << '\n';
				// Subtract one because that wasn't really a new insert
				--this->list_size;
				// Make sure they aren't NULL
				if ( value && new_pop )
				{
					*new_pop = *value;
				}
				// Delete the key we've fixed
				delete [] pop_key;
				// std::cout << "Set up " << key << ":\n";
				// walker->get_data()->print();
				// std::cout << "VALUE OF:\t" << key << "\tIS:\t" << value << "\n\n";
			}
			// Make the walker thenext element in the list
			walker = walker->get_next();
		}
		// The loop exits when the value of newcurr is no longer
		// bigger than the value of the element which walker is.
		// This means that it belongs at this spot in the list
		// because it is greater than the previous walkers number
		// and smaller than the current number
		if ( !value && walker )
		{
			// std::cout << "GET " << key << " from walker\n";
			value = walker->get_data()->get( key );
		}
		else if ( !value )
		{
			// std::cout << "INSERT " << key << " at tail\n";
			list_el< dict_array <data_type> > * newcurr = new list_el< dict_array <data_type> >;
			// The tail needs to know that newcurr is larger than it
			tail->set_next(newcurr);
			// newcurr needs to know that tail is smaller than it
			newcurr->set_prev(tail);
			// newcurr needs to know that there is nothing larger than it
			newcurr->set_next(NULL);
			// The newcurr becomes the tail because it is the largest element
			tail = newcurr;
			// Get the key's value
			value = tail->get_data()->get( key );
		}
	}

	// Increment the size of the list because we just added an element
	++this->list_size;

	// Return how many elsements are in the list
	return value;
}



/*
	Class: dict_dict_array
	Method: append
	Use: Appends into the list based on the val
		That's only because I want to leave it
		like this for now. The val isn't nesisary
*/
template <typename data_type>
data_type * dict_dict_array<data_type>::append( char * key ) //, data_type data )
{
	// Allocate memory for a new list_el dict_dict_array
	data_type * value = NULL;
	// Set the data of the new list_el to the data passed in
	// newcurr->set_data( data );

	// If head is NULL we know that this is the first element in the list
	if ( head == NULL )
	{
		// Set the begining of the list to newcurr
		head = new list_el< dict_array <data_type> >;
		// Set the end of the list to newcurr
		tail = head;
		// This is because it is the only element in the list
		value = head->get_data()->get( key );
	}
 	// If the value of newcurr is greater than the tail then it is the tail
	else
	{
		if ( !tail->get_data()->full() )
		{
			value = tail->get_data()->get( key );
		}
		else
		{
			list_el< dict_array <data_type> > * newcurr = new list_el< dict_array <data_type> >;
			// The tail needs to know that newcurr is larger than it
			tail->set_next(newcurr);
			// newcurr needs to know that tail is smaller than it
			newcurr->set_prev(tail);
			// newcurr needs to know that there is nothing larger than it
			newcurr->set_next(NULL);
			// The newcurr becomes the tail because it is the largest element
			tail = newcurr;
			// Get the key's value
			value = tail->get_data()->get( key );
		}
	}

	// Increment the size of the list because we just added an element
	++this->list_size;

	// Return how many elsements are in the list
	return value;
}



/*
	Class: dict_dict_array
	Method: remove
	Use: Removes the given index from the list
*/
template <typename data_type>
bool dict_dict_array<data_type>::remove( char * key )
{
	bool removed = false;
	// If head is not NULL we know that 
	// there is a list to remove from
	if ( head )
	{
		// Create a walker to go through the list
		list_el< dict_array <data_type> > * walker = head;
		// As long as the value of newcurr is greater than
		// that of the next element we need to keep walking
		while( !removed && walker )
		{
			// The array is full but the key belongs here
			if ( walker->get_data()->contains( key ) )
			{
				walker->get_data()->remove( key );
				--this->list_size;
				removed = true;
			}
			// Make the walker thenext element in the list
			walker = walker->get_next();
		}
	}
	// Return the status of removal
	return removed;
}


// template <typename data_type>
// unsigned int dict_dict_array<data_type>::load_file( char * file_name )
// {
// 	// Ment to be 
// }