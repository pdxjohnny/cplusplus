/*
	Author: John Andersen
	Date: 11/4/2014
	Description: array class, a dynamicly allocated
		size changing array
*/


#include <cstdio>

#ifndef NULL
	#define NULL 0
#endif


/*
	Class: array
	Use: Holds the length of the array as well as
		the pinter to the array which is an array
		of pointer to the data type.
		The way that this deletes means that it is
		not suitable for use with creating an
		array of arrays because when deleteing
		members of the array of pointers it only
		calls the single delete not delete [].
*/
template <typename data_type>
class array
{
public:
	array();
	~array();
	// Allows access to the elements by their position
	data_type &operator[]( unsigned int num );
	bool operator=( data_type ** new_array );
	// Returns the number of elements in the list
	unsigned int size( void );
	// Inserts a data of the list type into the list
	unsigned int insert( data_type * data );
	// Inserts a data of the list type into the list
	bool copy( data_type ** copy_to, data_type ** copy_from );
	// Deletes a data of the list type into the list
	unsigned int remove( unsigned int num );
	// Resets the array to nothing
	void remove_all( void );
private:
	// Length of the array
	unsigned int array_size;
	// The pointer to an array of pointers which
	// point to what ever the data type is
	data_type ** array_pointer;
};

#include "array.cpp"
// Included because of template use.
// data_type will be replaced with
// whatever data type is used at
// compile time