/*
	Author: John Andersen
	Date: 11/4/2014
	Description: dict_array class methods.
*/

// #include "dict_array.h"
// This is intentionally commented out, explination in is dlist.h



/*
	Class: dict_array
	Method: Constructor
	Use: Initialises data members
*/
template <typename data_type>
dict_array<data_type>::dict_array()
{
	this->init( DICT_ARRAY_SIZE );
};



/*
	Class: dict_array
	Method: Constructor
	Use: Initialises data members with an array of size max
*/
template <typename data_type>
dict_array<data_type>::dict_array( unsigned int max )
{
	this->init( max );
};



/*
	Class: dict_array
	Method: deconstructor
	Use: deletes whatever data is pointing to
*/
template <typename data_type>
dict_array<data_type>::~dict_array()
{
	this->reset();
};



/*
	Class: dict_array
	Method: init
	Use: Initialises data members with an array of size max
*/
template <typename data_type>
void dict_array<data_type>::init( unsigned int max )
{
	this->array_size = 0;
	this->first_open = 0;
	this->max_size = max;
	// Allocate the arrays
	this->array = new data_type[ this->max_size ];
	this->item_keys = new char*[ this->max_size ];
	this->open = new bool[ this->max_size ];
	// Set them all to open
	for ( unsigned int i = 0; i < this->max_size; ++i )
	{
		this->open[ i ] = true;
		this->item_keys[ i ] = NULL;
	}
}



/*
	Class: dict_array
	Method: reset
	Use: resets data members
*/
template <typename data_type>
void dict_array<data_type>::reset( void )
{
	// Remove the keys used
	for ( unsigned int i = 0; i < this->max_size; ++i )
	{
		if ( !this->open[ i ] )
		{
			delete [] this->item_keys[ i ];
		}
	}
	// Deallocated the arrays
	delete [] array;
	delete [] item_keys;
	delete [] open;
}


/*
	Class: dict_array
	Method: size
	Use: sizes the value of the private val to val
*/
template <typename data_type>
int dict_array<data_type>::size( void )
{
	return this->array_size;
}


/*
	Class: dict_array
	Method: full
	Use: Check if array is full
*/
template <typename data_type>
bool dict_array<data_type>::full( void )
{
	return ( this->array_size == this->max_size );
}


/*
	Class: dict_array
	Method: contains
	Use: containss the value of the private val to val
*/
template <typename data_type>
bool dict_array<data_type>::contains( char * key )
{
	// Loop through and look for the key
	for ( unsigned int i = 0; i < this->max_size; ++i )
	{
		// Only look if the string is allocated
		if ( !this->open[ i ] &&
			0 == strcmp( this->item_keys[ i ], key ) )
		{
			return true;
		}
	}
	return false;
}


/*
	Class: dict_array
	Method: keys
	Use: Returns the array of keys
*/
template <typename data_type>
char ** dict_array<data_type>::keys( void )
{
	// Allocate the array of characters
	char ** keys = new char*[ this->array_size ];
	// The key of the array we are one, only copy
	// keys that are in use
	unsigned int key = 0;
	// Loop through all of the keys
	for ( unsigned int i = 0; i < this->max_size; ++i )
	{
		// Only copy the key over if its there to copy
		if ( !this->open[ i ] )
		{
			// Create a new string
			keys[ key ] = new char[ strlen( this->item_keys[ i ] ) + 1 ];
			// Copy over the strings data
			strcpy( keys[ key ], this->item_keys[ i ] );
			// Increment the real key we are on
			++key;
		}
	}
	return keys;
}


/*
	Class: dict_array
	Method: remove
	Use: removes the value of the private val to val
*/
template <typename data_type>
bool dict_array<data_type>::remove( char * key )
{
	// Loop through all of the keys
	for ( unsigned int i = 0; i < this->max_size; ++i )
	{
		// Only comapre the key over if its there
		if ( !this->open[ i ] &&
			0 == strcmp( this->item_keys[ i ], key ) )
		{
			#ifdef DEBUG
				std::cout << color::red;
				std::cout << "Found and deleting: " << key << '\n';
				std::cout << color::normal;
			#endif
			// Deallocate the key string
			delete [] this->item_keys[ i ];
			// This is now an available spot
			this->open[ i ] = true;
			// If this one is closer to 0 than the current
			// first open then make it that
			if ( i < this->first_open )
			{
				this->first_open = i;
			}
			// We removed one so decement the array size
			--this->array_size;
			// Sort the array by key
			this->sort();
			// Return true because we remvoed
			return true;
		}
	}
	// No removal took place
	return false;
}


/*
	Class: dict_array
	Method: sort
	Use: sorts the value of the private val to val
*/
template <typename data_type>
int dict_array<data_type>::sort( void )
{
	// temps are used to swap values in the sort
	bool temp_open;
	char * temp_key;
	data_type temp_value;
	bool sorted = false;
	// sorted is used to let the caller know if the sort
	// changed anything in the array
	bool changed = true;
	// changed is used to see if any elements wher out of order
	// if they are out of order it attempts to sort them
	// once a loop completes without being out of order
	// we know that there is no more to sort
	while ( changed )
	{
		// To start nothing has changed
		changed = false;
		// Loop through all the elements of the array
		for ( unsigned int j = 0; j < this->max_size - 1; ++j )
		{
			// Check if the keys are in the right order
			if ( !this->open[ j ] && !this->open[ j + 1 ] &&
				0 < strcmp( this->item_keys[ j ], this->item_keys[ j + 1 ] ) )
			{
				// Create our temp variables to swap
				temp_open = this->open[ j ];
				temp_key = new char[ strlen( this->item_keys[ j ] ) + 1 ];
				strcpy( temp_key, this->item_keys[ j ] );
				temp_value = this->array[ j ];
				// Set the current to the next
				this->open[ j ] = this->open[ j + 1 ];
				delete [] this->item_keys[ j ];
				this->item_keys[ j ] = new char[ strlen( this->item_keys[ j + 1 ] ) + 1 ];
				strcpy( this->item_keys[ j ], this->item_keys[ j + 1 ] );
				this->array[ j ] = this->array[ j + 1 ];
				// Set the next to the temp
				this->open[ j + 1 ] = temp_open;
				delete [] this->item_keys[ j + 1 ];
				this->item_keys[ j + 1 ] = temp_key;
				this->array[ j + 1 ] = temp_value;
				// We changed the order of the array so we need to make
				// sure its correct again
				changed = true;
				// The list was sorted so return true
				sorted = true;
			}
		}
	}
	return sorted;
}



/*
	Class: dict_array
	Method: belongs
	Use: belongss the value of the private val to val
*/
template <typename data_type>
bool dict_array<data_type>::belongs( char * key )
{
	bool belongs = false;
	// If there is an array
	if ( this->array_size )
	{
		// Make sure the last has a key, if key is ascii
		// less than the last item then it belong here and
		// the last item doesn't
		if ( !this->open[ this->first_open - 1 ] &&
			0 < strcmp( this->item_keys[ this->first_open - 1 ], key ) )
		{
			belongs = true;
		}
	}
	return belongs;
}


/*
	Class: dict_array
	Method:get_data
	Use: get_data the value of the private val to val
*/
template <typename data_type>
char * dict_array<data_type>::pop_key( void )
{
	// If the first open is not 0
	if ( this->first_open - 1 > 0 )
	{
		// Create a copy of the key
		char * key = this->item_keys[ this->first_open - 1 ];
		char * pop_key = new char[ strlen( key ) + 1 ];
		strcpy( pop_key, key );
		return pop_key;
	}
	return NULL;
}


/*
	Class: dict_array
	Method:get_data
	Use: get_data the value of the private val to val
*/
template <typename data_type>
data_type * dict_array<data_type>::pop( void )
{
	// Return the address of the last entry
	if ( this->first_open - 1 > 0 )
	{
		return &this->array[ this->first_open - 1 ];
	}
	return NULL;
}


/*
	Class: dict_array
	Method:get_data
	Use: get_data the value of the private val to val
*/
template <typename data_type>
data_type * dict_array<data_type>::get( unsigned int index )
{
	// How many we have been though
	unsigned int position = 0;
	if ( index < this->max_size )
	{
		for ( unsigned int i = 0; i < this->max_size; ++i )
		{
			if ( !this->open[ i ] )
			{
				// Return if the position is the index requested
				// the client doesn't need to know which ones are
				// empty
				if ( position == index )
				{
					return &this->array[ i ];
				}
				++position;
			}
		}
		char key[11];
		sprintf( key, "%d", index );
		return this->insert( key );
	}
	return NULL;
}


/*
	Class: dict_array
	Method:get_data
	Use: get_data the value of the private val to val
*/
template <typename data_type>
data_type * dict_array<data_type>::get( char * key )
{
	for ( unsigned int i = 0; i < this->max_size; ++i )
	{
		// Look fo rthe key and return the address of it
		if ( !this->open[ i ] &&
			0 == strcmp( this->item_keys[ i ], key ) )
		{
			return &this->array[ i ];
		}
	}
	// If we don't find it create it
	return this->insert( key );
}


/*
	Class: dict_array
	Method:insert
	Use: insert the value of the private val to val
*/
template <typename data_type>
data_type * dict_array<data_type>::insert( char * key )
{
	// Make sure there is room
	if ( this->first_open < this->max_size )
	{
		// Mark it as in use
		this->open[ this->first_open ] = false;
		// Copy over the key
		this->item_keys[ this->first_open ] = new char[ strlen( key ) + 1 ];
		strcpy( this->item_keys[ this->first_open ], key );
		// Find the next open spot int he array
		while ( this->first_open < this->max_size &&
				!this->open[ this->first_open ] )
		{
			++this->first_open;
		}
		// Increment the array size
		++this->array_size;
		this->sort();
		// Sorting may change position
		return this->get( key );
	}
	return NULL;
}



/*
	Class: dict_array
	Method: print
	Use: prints the value of the private val to val
*/
template <typename data_type>
void dict_array<data_type>::print( void )
{
	for ( unsigned int i = 0; i < this->max_size; ++i )
	{
		if ( !this->open[ i ] )
		{
			std::cout << i << "\t:\t" << this->item_keys[ i ] << "\t:\t" << this->array[ i ] << '\n';
		}
	}
}



/*
	Class: dict_array
	Operator: []
	Use: Retrives and item in the array by its key
*/
template <typename data_type>
data_type * dict_array<data_type>::operator[]( char * key )
{
	return this->get( key );
}



/*
	Class: dict_array
	Operator: []
	Use: Retrives and item in the array by its index
*/
template <typename data_type>
data_type * dict_array<data_type>::operator[]( unsigned int index )
{
	return this->get( index );
}
