/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Hash class uses the data structure provided
		to implement a hash table with chaining
*/



template <typename> class hash;


/*
	Class: hash
	Use: Creates a hash table of specified size
		and uses the data structure to implement chianing
		as the colission resolution tequneqe
*/
template <typename data_structure, typename data_type>
class hash< void( data_structure, data_type ) >
{
	public:
		// Initializes data members
		hash( int size = 100 );   
		// Deallocate all the indexs
		~hash( void );
		// Adds up the ascii values of chars in an string 
		int strval( char * string );
		// Creates an index given a string
		int hash_function( char * key );
		// Shorthand for get method
		data_type & operator[]( char * key );
		// Returns the variable of data_type associated with the key
		data_type & get( char * key );
		// Checks if the key is in the hash table
		bool contains( char * key );
		// Checks if the key is in a data structure
		bool contains( char * key, data_structure ** curr);
		bool remove( char * key );
		bool remove(char * key, data_structure ** curr);
	private:
		// The hash table array
		data_structure ** hash_table;
		// The size of the array
		int hash_table_size;
		// The number of items in the table
		int in_table;
};

#include "hash.cpp"
