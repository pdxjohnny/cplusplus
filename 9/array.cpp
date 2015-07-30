/*
	Author: John Andersen
	Date: 11/4/2014
	Description: array class, a dynamicly allocated
		size changing array methods
*/


/*
	Class: array
	Method: Constructor
	Use: Initializes the members
*/
template <class data_type>
array<data_type>::array()
{
	// Set the list size to 0 because there is
	// no list yet
	this->array_size = 0;
	// Make our array nothing
	this->array_pointer = NULL;
}


/*
	Class: array
	Method: deconstructor
	Use: Deletes the array
*/
template <class data_type>
array<data_type>::~array()
{
	this->remove_all();
}


/*
	Class: array
	Operator: []
	Use: Gets the element that is that number in the list
*/
template <class data_type>
data_type &array<data_type>::operator[]( unsigned int num )
{
	return *this->array_pointer[ num ];
}

/*
	Class: array
	Operator: =
	Use: Sets array_pointer to the new array
*/
template <class data_type>
bool array<data_type>::operator=( data_type ** new_array )
{
	// If there is an array
	if ( this->array_pointer )
	{
		// Delete the whole array
		this->remove_all();
	}
	// Make a walker so we can walk
	// the length of the array
	data_type ** walker = new_array;
	// Set the size to 0
	this->array_size = 0;
	// Walk through the new array
	while ( walker++ )
	{
		// Increment for every iteration
		++this->array_size;
	}
	// Asign our array_pointer to the new_array
	this->array_pointer = new_array;
	return true;
}


/*
	Class: array
	Method: size
	Use: Returns the size of the array
*/
template <typename data_type>
unsigned int array<data_type>::size( void )
{
	return this->array_size;
}


/*
	Class: array
	Method: deconstructor
	Use: Deletes the array
*/
template <typename data_type>
unsigned int array<data_type>::insert( data_type * data )
{
	// Allocate memory for the new array that is one larger than
	// it used to be
	data_type ** new_array = new data_type*[ this->array_size + 1 ];
	// If there is an existing array
	if ( this->array_pointer )
	{
		// Copy the old array into the new array
		this->copy( new_array, this->array_pointer );
		// Delete the old array
		delete [] this->array_pointer;
	}
	// Asign the array_pointer to the new arrary
	this->array_pointer = new_array;
	// Make the last element the new element
	this->array_pointer[ this->array_size ] = data;
	// Increase the array_size intiger
	++this->array_size;
	return this->array_size;
}


/*
	Class: array
	Method: copy
	Use: Copys the contents of one array
		to the other
*/
template <typename data_type>
bool array<data_type>::copy( data_type ** copy_to, data_type ** copy_from )
{
	// These don't work-
	// while ( (*copy_to++ = *copy_from++) != 0 );
	// while ( *copy_from )
	// {
	// 	*copy_to++ = *copy_from++;
	// }
	// Loop though the array and copy one to the other
	for (int i = 0; i < this->array_size; ++i)
	{
		copy_to[i] = copy_from[i];
	}
	return true;
}


/*
	Class: array
	Method: remove
	Use: Copys over all but the element
		we want to remove to a new array
		and deletes the element we are
		no longer using
*/
template <typename data_type>
unsigned int array<data_type>::remove( unsigned int num )
{
	// Check id there is an array
	if ( this->array_pointer && this->array_size > 1 && num < this->array_size )
	{
		// Create a new array one less than the 
		data_type ** new_array = new data_type*[ this->array_size - 1 ];
		for ( unsigned int i = 0, j = 0; i < this->array_size; ++i )
		{
			// if this is not the element we want to delete then copy
			if ( i != num )
			{
				new_array[j] = this->array_pointer[i];
				// J will not always be i beacuse if i is num 
				// then we wont't copy and we'd end up with a
				// element that is not anything
				++j;
			}
			else
			{
				// Delete the one we aren't copying over
				delete this->array_pointer[i];
			}
		}
		// Delete the array of pointers
		delete [] this->array_pointer;
		// Make the array the new array
		this->array_pointer = new_array;
		// Decrement the size of the array
		--this->array_size;
	}
	return this->array_size;
}


/*
	Class: array
	Method: remove_all
	Use: Deletes all members of the array
		and the array of pointers
*/
template <class data_type>
void array<data_type>::remove_all( void )
{
	// Loop through the array and delete what every member
	// points to
	for ( unsigned int i = 0; i < this->array_size; ++i )
	{
		delete this->array_pointer[i];
	}
	// Delete the array of pointers
	delete [] this->array_pointer;
	// Set the array pointer to nothing
	this->array_pointer = NULL;
};
