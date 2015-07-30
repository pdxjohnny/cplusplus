/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Hash class uses the data structure provided
		to implement a hash table with chaining
*/



/*
	Class: Hash
	Method: Constructor
	Use: Initializes data members
	Input: The size of the hash table
	Output: None
*/
template <typename data_structure, typename data_type>
hash< void( data_structure, data_type ) >::hash( int size )
{
	// The number of items in the table
	in_table = 0;
	// The size of the array
	hash_table_size = size;
	// The array of size hash_table_size
	hash_table = new data_structure * [ hash_table_size ];
	// Set all indexs to NULL
	for ( int i = 0; i < hash_table_size; ++i )
	{
		hash_table[ i ] = NULL;
	}
}



/*
	Class: Hash
	Method: Deconstructor
	Use: Deallocate all the indexs
	Input: None
	Output: None
*/
template <typename data_structure, typename data_type>
hash< void( data_structure, data_type ) >::~hash( void )
{
	// The pointer to the pointer to the index
	data_structure ** del = NULL;
	// Loop through the table
	for ( int i = 0; i < hash_table_size; ++i )
	{
		// Minimize operations an fetches
		del = & hash_table[ i ];
		// If its pointing to anything
		if ( * del )
		{
			// Delete it
			delete * del;
		}
	}
	// Delete the table
	delete [] hash_table;
}



/*
	Class: hash
	Method: strval
	Use: Adds up the ascii values of chars in an string 
	Input: The string to asess
	Output: The sum of all chars in the string
*/
template <typename data_structure, typename data_type>
int hash< void( data_structure, data_type ) >::strval( char * string )
{
	// The length of the string
	int len = strlen( string );
	// The sum of the characters
	int chars = 0;
	// Walk the string
	for ( int i = 0; i < len; ++i )
	{
		// Add to the sum of characters
		chars += string[ i ];
	}
	// Return the sum of characters
	return chars;
}



/*
	Class: Hash
	Method: hash_function
	Use: Creates an index given a string
	Input: A string
	Output: An index
*/
template <typename data_structure, typename data_type>
int hash< void( data_structure, data_type ) >::hash_function( char * key )
{
	// Find the sum of characters and mod by the table size
	return strval( key ) % hash_table_size;
}



/*
	Class: Hash
	Method: operator []
	Use: Shorthand for get method
	Input: Key string
	Output: The variable associated with the key
*/
template <typename data_structure, typename data_type>
data_type & hash< void( data_structure, data_type ) >::operator[]( char * key )
{
	// Calls the get method
	return this->get( key );
}



/*
	Class: Hash
	Method: get
	Use: Returns the variable of data_type associated with the key
	Input: Key string
	Output: The variable associated with the key
*/
template <typename data_structure, typename data_type>
data_type & hash< void( data_structure, data_type ) >::get( char * key )
{
	// Finds the index from the hash function
	int index = hash_function( key );
	// Creates a pointer for less operations and fetches
	data_structure ** curr = & hash_table[ index ];
	// Increments if we are about to add the key
	if ( !contains( key, curr ) )
	{
		++in_table;
	}
	// If the element hasen't been allocated then alloacte it
	if ( !(*curr) )
	{
		* curr = new data_structure;
	}
	// Ask the data structure for the key
	return (*curr)->get( key );
}



/*
	Class: Hash
	Method: contains
	Use: Checks if the key is in the hash table
	Input: The key
	Output: True for in table false for not
*/
template <typename data_structure, typename data_type>
bool hash< void( data_structure, data_type ) >::contains( char * key )
{
	// Calls the contains method with the appropriate index
	return contains( key, & hash_table[ hash_function( key ) ] );
}



/*
	Class: Hash
	Method: contains
	Use: Checks if the key is in a data structure
	Input: The key and data structure
	Output: True for in data structure false for not
*/
template <typename data_structure, typename data_type>
bool hash< void( data_structure, data_type ) >::contains( char * key, data_structure ** curr)
{
	// If the index has be allocated
	if ( * curr )
	{
		// Check if it has the key
		return ( * curr )->contains( key );
	}
	// If it hasn't been allocated then theres no way it has the key
	return false;
}


