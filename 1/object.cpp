/*
	Author: John Andersen
	Date: 01/15/2015
	Description: object class methods
*/

// Include the object class definition
#include "object.h"



/*
	Class: object
	Method: deallocator
	Use: Delete the string pointers it has allocated
*/
object::~object()
{
	for ( unsigned int i = 0; i < this->strings.size(); ++i )
	{
		delete [] this->strings[ i ];
	}
}


/*
	Class: object
	Operator: []
	Use: Allows access to any one of the members
		by typecasting the result of this.
		The return on the char * dict needs work
*/
void * object::operator[]( char * key )
{
	// The void return pointer
	void * return_value = NULL;
	// If the key is an intiger
	if ( this->ints.contains( key ) )
	{
		// Return the address of the int
		return_value = & this->ints[ key ];
	}
	else if ( this->floats.contains( key ) )
	{
		// Return the address of the float
		return_value = & this->floats[ key ];
	}
	else if ( this->strings.contains( key ) )
	{
		// Return the pointer to char
		return_value = this->strings[ key ];
	}
	return return_value;
}


/*
	Class: object
	Method: from_string
	Use: Parses a string into data members
*/
void object::from_string( char * keys,  char * values, const char delim )
{
	// A copy of the keys string
	char local_keys[ strlen( keys ) + 1 ];
	// The key for accessing the value
	char key[ gen::STRING_SIZE ];
	// The value of the key
	char value[ gen::STRING_SIZE ];
	// Make a copy of the keys string
	strcpy( local_keys, keys );
	// While their are delimiters left in both
	// the keys and values strings
	while ( gen::count( local_keys, delim ) && gen::count( values, delim )  )
	{
		// Pop off the first key
		gen::split_line( local_keys, key, local_keys, delim );
		// Pop off the first value
		gen::split_line( values, value, values, delim );
		// Assign the key to the value
		this->set( key, value );
	}
	if ( strlen( local_keys ) && strlen( values ) )
	{
		// Can't pop off any more but there is one more
		// being that the last chacters are not the delim
		this->set( local_keys, values );
	}
}


/*
	Class: object
	Method: set
	Use: Sets a value appropriatly
*/
bool object::set( char * key, char * value )
{
	// If the value is an int and is not in
	// the other dictionarys
	if ( gen::is_int( value ) &&
		!this->floats.contains( key ) &&
		!this->strings.contains( key ) )
	{
		// Add to the int dictionary
		this->ints[ key ] = atoi( value );
		return true;
	}
	// If the value is a float and is not in
	// the other dictionarys
	else if ( gen::is_float( value ) &&
		!this->ints.contains( key ) &&
		!this->strings.contains( key ) )
	{
		// Add to the float dictionary
		this->floats[ key ] = atof( value );
		return true;
	}
	// If the value is a string and is not in
	// the other dictionarys
	else if ( !this->ints.contains( key ) &&
		!this->floats.contains( key ) )
	{
		// If the dictionary contains the key
		// then we have used it and it has been
		// allocaed, therefor delete before reallocating
		if ( this->strings.contains( key ) )
		{
			delete [] this->strings[ key ];
		}
		// Make the key only as big as needed
		this->strings[ key ] = new char[ strlen( value ) + 1 ];
		// Copy over the string
		strcpy( this->strings[ key ], value );
		return true;
	}
	return false;
}


/*
	Class: object
	Method: contains
	Use: Tests if value is present
*/
bool object::contains( char * key )
{
	return this->ints.contains( key ) ||
		this->floats.contains( key ) ||
		this->strings.contains( key );
}


/*
	Class: object
	Method: set
	Use: Sets a value appropriatly
*/
bool object::set( char * key, int value )
{
	// We know the client wants an int so
	// make sure it wont be present else where
	this->floats.remove( key );
	this->strings.remove( key );
	// Add to the int dictionary
	this->ints[ key ] = value;
	return true;
}


/*
	Class: object
	Method: set
	Use: Sets a value appropriatly
*/
bool object::set( char * key, float value )
{
	// We know the client wants a float so
	// make sure it wont be present else where
	this->ints.remove( key );
	this->strings.remove( key );
	// Add to the int dictionary
	this->floats[ key ] = value;
	return true;
}


/*
	Class: object
	Method: prompt
	Use: Propmts user for the values of data members
*/
void object::prompt( char * keys, char delim )
{
	// The amount of deliminating chacters in the string
	unsigned int delim_count = gen::count( keys, delim );
	// used as a copy of the keys string
	char local_keys[ strlen( keys ) + 1 ];
	// For the current key
	char key[ gen::STRING_SIZE ];
	// For the current value
	char value[ gen::STRING_SIZE ];
	// For the current question
	char ask[ gen::STRING_SIZE ];
	// Making a copy of the keys so as to preserve them
	strcpy( local_keys, keys );
	// Loop through all keys including the last
	for ( unsigned int i = 0; i <= delim_count; ++i  )
	{
		// Pop off the first key into the key array
		gen::split_line( local_keys, key, local_keys, delim );
		// Format the question
		sprintf( ask, "What is the %s: ", key );
		// Ask the user for the value
		gen::get_line( ask, value, gen::STRING_SIZE );
		// Set the key to be the input
		this->set( key, value );
		// Clear the strings so as to avoid them
		// getting longer than they should be
		gen::strclr( value );
		gen::strclr( ask );
	}
	return;
}


/*
	Class: object
	Method: print
	Use: Creates a string of the class in json format
		because its easily readable this way
*/
void object::print( void )
{
	// Get the array of key strings
	char ** keys = this->ints.keys();
	// Loop through all the ints
	for ( unsigned int i = 0; i < this->ints.size(); ++i )
	{
		std::cout << keys[ i ] << "\t:\t" << this->ints[ i ] << '\n';
		// Delete the string that is the key
		delete [] keys[ i ];
	}
	// Delete the array of pointers to the key stings
	delete [] keys;
	// Get the new array of key strings
	keys = this->floats.keys();
	// Loop through all the floats
	for ( unsigned int i = 0; i < this->floats.size(); ++i )
	{
		std::cout << keys[ i ] << "\t:\t" << this->floats[ i ] << '\n';
		// Delete the string that is the key
		delete [] keys[ i ];
	}
	// Delete the array of pointers to the key stings
	delete [] keys;
	// Get the new array of key strings
	keys = this->strings.keys();
	// Loop through all the strings
	for ( unsigned int i = 0; i < this->strings.size(); ++i )
	{
		std::cout << keys[ i ] << "\t:\t" << this->strings[ i ] << '\n';
		// Delete the string that is the key
		delete [] keys[ i ];
	}
	// Delete the array of pointers to the key stings
	delete [] keys;
}


/*
	Class: object
	Method: value_length
	Use: Length of value as a string
*/
unsigned int object::value_length( char * key )
{
	// The string for ints and floats
	char value[ gen::STRING_SIZE ];
	// If the key is an int
	if ( this->ints.contains( key ) )
	{
		// The value's length if it were a string
		sprintf( value, "%d", this->ints[ key ] );
		return strlen( value );
	}
	// If the key is a float
	else if ( this->floats.contains( key ) )
	{
		// The value's length if it were a string
		sprintf( value, "%f", this->floats[ key ] );
		return strlen( value );
	}
	// If the key is a string
	else if ( this->strings.contains( key ) )
	{
		// Just the string length
		return strlen( this->strings[ key ] );
	}
	return 0;
}


/*
	Class: object
	Method: length_of_values
	Use: Length of value all values as strings
*/
unsigned int object::length_of_values( char * keys, char delim )
{
	// The amount of deliminating chacters in the string
	unsigned int delim_count = gen::count( keys, delim );
	// The length of all the values
	unsigned int all_lengths = 0;
	// A copy of the keys string
	char local_keys[ strlen( keys ) + 1 ];
	// The key for accessing the value
	char key[ gen::STRING_SIZE ];
	// Make a copy of the keys string
	strcpy( local_keys, keys );
	// Lopp through all of the keys
	for ( unsigned int i = 0; i <= delim_count; ++i  )
	{
		// If we are not of the last key
		if ( i < delim_count )
		{
			// Pop off the first key into the key string
			gen::split_line( local_keys, key, local_keys, delim );
			// Add the length to all_lengths
			all_lengths += this->value_length( key );
		}
		// On the last key we can't pop it off because
		// it is the only string left in local_keys
		else
		{
			// Add the length to all_lengths
			all_lengths += this->value_length( local_keys );
		}
	}
	return all_lengths;
}


/*
	Class: object
	Method: value_string
	Use: Sets the string to the value
*/
void object::value_string( char * value, char * key )
{
	if ( this->ints.contains( key ) )
	{
		// Format the sting as an intiger
		sprintf( value, "%d", this->ints[ key ] );
	}
	else if ( this->floats.contains( key ) )
	{
		// Format the sting as a float
		sprintf( value, "%f", this->floats[ key ] );
	}
	else if ( this->strings.contains( key ) )
	{
		// Copy the string
		strcpy( value, this->strings[ key ] );
	}
}


/*
	Class: object
	Method: save
	Use: Creates a string of the class in csv format
*/
char * object::to_string( char * keys, char delim )
{
	// The amount of deliminating chacters in the string
	int delim_count = this->size() - 1;
	// This will be the size of the string it is determined by the
	// number of delimiters to be used added with the length of the
	// values and 1 for the \0 terminating character
	unsigned int all_lengths = delim_count + this->length_of_values( keys, delim ) + 1;
	// used as a copy of the keys string
	char local_keys[ strlen( keys ) + 1 ];
	// For the current key
	char key[ gen::STRING_SIZE ];
	// For the current value
	char value[ gen::STRING_SIZE ];
	// Making a copy of the keys so as to preserve them
	strcpy( local_keys, keys );
	// Make the as_string array only about as long as it needs to be
	char * as_string = new char[ all_lengths ];
	// Loop through all keys including the last
	for ( unsigned int i = 0; i <= delim_count; ++i  )
	{
		// Pop off the first key into the key array
		gen::split_line( local_keys, key, local_keys, delim );
		// Put the value as a sting into the value array
		this->value_string( value, key );
		// Add the values as columns
		gen::add_to_csv( i, delim_count, as_string, value, delim ); 
		// Clear the value string so as to avoid keys longer
		// than they should be
		gen::strclr( value );
	}
	return as_string;
}


/*
	Class: object
	Method: remove
	Use: Removes a value
*/
void object::remove( char * key )
{
	if ( this->ints.contains( key ) )
	{
		this->ints.remove( key );
	}
	else if ( this->floats.contains( key ) )
	{
		this->floats.remove( key );
	}
	else if ( this->strings.contains( key ) )
	{
		// If the dictionary contains the key
		// then we have used it and it has been
		// allocaed, therefor delete before reallocating
		delete [] this->strings[ key ];
		this->strings.remove( key );
	}
}



/*
	Class: object
	Method: size
	Use: Adds up all sizes
*/
int object::size( void )
{
	return this->ints.size() + this->floats.size() + this->strings.size();
}



/*
	Class: object
	Method: keys_length
	Use: Finds the length of all the keys with a delim
*/
unsigned int object::keys_length( void )
{
	// The length of the new string
	unsigned int length = 0;
	// Get all of the keys
	char ** int_keys = this->ints.keys();
	char ** float_keys = this->floats.keys();
	char ** string_keys = this->strings.keys();
	// Loop through all the ints
	for ( unsigned int i = 0; i < this->ints.size(); ++i )
	{
		// The length of the key plus one for a delim
		length += strlen( int_keys[ i ] ) + 1;
		// Delete the string that is the key
		delete [] int_keys[ i ];
	}
	// Loop through all the floats
	for ( unsigned int i = 0; i < this->floats.size(); ++i )
	{
		// The length of the key plus one for a delim
		length += strlen( float_keys[ i ] ) + 1;
		// Delete the string that is the key
		delete [] float_keys[ i ];
	}
	// Loop through all the strings
	for ( unsigned int i = 0; i < this->strings.size(); ++i )
	{
		// The length of the key plus one for a delim
		length += strlen( string_keys[ i ] ) + 1;
		// Delete the string that is the key
		delete [] string_keys[ i ];
	}
	// Delete the array of pointers to the key stings
	delete [] int_keys;
	delete [] float_keys;
	delete [] string_keys;
	// Sum of them all with their delims
	return length;
}




/*
	Class: object
	Method: keys
	Use: Concatonates all the keys
*/
char * object::keys( const char delim )
{
	// The amount of deliminating chacters in the string
	int delim_count = this->size() - 1;
	// The length of the new string
	char * key_string = new char [ this->keys_length() + 1 ];
	// All of the keys
	char ** keys = this->keys();
	// How many keys we have already added to the string
	for ( unsigned int i = 0; i < this->size(); ++i )
	{
		gen::add_to_csv( i, delim_count, key_string, keys[ i ], delim );
		// Delete the string that is the key
		delete [] keys[ i ];
	}
	delete [] keys;
	return key_string;
}





/*
	Class: object
	Method: keys
	Use: Keys as an array
*/
char ** object::keys( void )
{
	// The length of the new string
	char ** keys = new char * [ this->size() ];
	// Get all of the keys
	char ** int_keys = this->ints.keys();
	char ** float_keys = this->floats.keys();
	char ** string_keys = this->strings.keys();
	// How many keys we have already added
	unsigned int key = 0;
	for ( unsigned int i = 0; i < this->ints.size(); ++i )
	{
		keys[ key ] = int_keys[ i ];
		++key;
	}
	// Loop through all the floats
	for ( unsigned int i = 0; i < this->floats.size(); ++i )
	{
		keys[ key ] = float_keys[ i ];
		++key;
	}
	// Loop through all the strings
	for ( unsigned int i = 0; i < this->strings.size(); ++i )
	{
		keys[ key ] = string_keys[ i ];
		++key;
	}
	// Delete the array of pointers to the key stings
	delete [] int_keys;
	delete [] float_keys;
	delete [] string_keys;
	return keys;
}




/*
	Class: dict<object>
	Method: save_file
	Use: Overloads the dict save_file method for use with
		this object class
*/
template <>
unsigned int dict<object>::save_file( char * file_name, const char delim )
{
	// The output file object
	std::ofstream save_file;
	// The return code, false if it can't open a file
	bool return_code = false;
	save_file.open( file_name );
	// If the file is open then write
	if ( save_file.is_open() )
	{
		char ** object_name = this->keys();
		// Loop through all the items
		for ( unsigned int i = 0; i < this->size(); ++i )
		{
			if ( this->get( i ).size() )
			{
				// Get the keys and values in csv format
				char * keys = this->get( i ).keys( delim );
				char * values = this->get( i ).to_string( keys, delim );
				// Put the keys and values in the file for retreval
				save_file << object_name[ i ] << '\n';
				save_file << keys << '\n';
				save_file << values << '\n';
				// Delete the strings that were malloc'd
				delete [] object_name[ i ];
				delete [] keys;
				delete [] values;
			}
		}
		delete [] object_name;
		// A file was opened set the return code to true
		return_code = true;
	}
	// Close the currently open file
	save_file.close();
	// Return whether a file was opened or not
	return return_code;
	return true;
}




/*
	Class: dict<object>
	Method: load_file
	Use: Overloads the dict load_file method for use with
		this object class
*/
template <>
unsigned int dict<object>::load_file( char * file_name, const char delim )
{
	// A file input object
	std::ifstream load_file;
	// The size of the current_line array which is read in
	int current_line_size = gen::STRING_SIZE * 2;
	// The current_line array for reading in the file
	char current_line[current_line_size];
	// The object name that is being read in
	char * object_name = new char [current_line_size];
	// The object keys that are being read in
	char * object_keys = new char [current_line_size];
	// The return code, false if it can't open a file
	bool return_code = false;
	// The part of the object we are reading
	// 0 - name, 1 - keys, 2 - values
	int object_part = 0;
	// Open the file for reading
	load_file.open( file_name );
	// If the file is open then read
	if ( load_file.is_open() )
	{
		while ( !load_file.eof() )
		{
			// Get a line and store it in the current_line array
			load_file.get( current_line, current_line_size, '\n' );
			// Read in and ignore the newline
			load_file.ignore( current_line_size, '\n' );
			// If the string length of the line is less than 1
			// then it is the last line so theres nothing there
			// std::cout << object_part << '\n';
			if ( strlen( current_line ) < 1 )
			{
				break;
			}
			else if ( object_part == 0 )
			{
				strcpy( object_name, current_line );
			}
			else if ( object_part == 1 )
			{
				strcpy( object_keys, current_line );
			}
			else
			{
				// std::cout << "Creating object " << object_name << " keys: " << object_keys << " values: " << current_line << '\n';
				// Set the object name to have the vlaues corresponding to the keys
				this->get( object_name ).from_string( object_keys, current_line, delim );
				gen::strclr( object_name );
				gen::strclr( object_keys );
				gen::strclr( current_line );
			}
			++object_part;
			if ( object_part >= 3 )
			{
				object_part = 0;
			}
		}
		// A file was opened to return true
		return_code = true;
	}
	// Close the currently open file
	load_file.close();
	// Deallocate memoy
	delete [] object_name;
	delete [] object_keys;
	// Return whether a file was opened
	return return_code;
}




/*
	Class: dict_dict_array<object>
	Method: save_file
	Use: Overloads the dict_dict_array save_file method for use with
		this object class
*/
template <>
unsigned int dict_dict_array<object>::save_file( char * file_name, const char delim )
{
	// The output file object
	std::ofstream save_file;
	// The return code, false if it can't open a file
	bool return_code = false;
	save_file.open( file_name );
	// If the file is open then write
	if ( save_file.is_open() )
	{
		char ** object_name = this->keys();
		// Loop through all the items
		for ( unsigned int i = 0; i < this->size(); ++i )
		{
			if ( this->get( i ).size() )
			{
				#ifdef DEBUG
					std::cout << "To file " << object_name[ i ] << "\n";
				#endif
				// Get the keys and values in csv format
				char * keys = this->get( i ).keys( delim );
				char * values = this->get( i ).to_string( keys, delim );
				#ifdef DEBUG
					std::cout << color::green;
					std::cout << object_name[ i ] << '\n';
					std::cout << keys << '\n';
					std::cout << values << '\n';
					std::cout << color::normal;
					std::cout << '\n';
				#endif
				// Put the keys and values in the file for retreval
				save_file << object_name[ i ] << '\n';
				save_file << keys << '\n';
				save_file << values << '\n';
				// Delete the strings that were malloc'd
				delete [] object_name[ i ];
				delete [] keys;
				delete [] values;
			}
		}
		delete [] object_name;
		// A file was opened set the return code to true
		return_code = true;
	}
	// Close the currently open file
	save_file.close();
	// Return whether a file was opened or not
	return return_code;
	return true;
}




/*
	Class: dict_dict_array<object>
	Method: load_file
	Use: Overloads the dict_dict_array load_file method for use with
		this object class
*/
template <>
unsigned int dict_dict_array<object>::load_file( char * file_name, const char delim )
{
	// A file input object
	std::ifstream load_file;
	// The size of the current_line array which is read in
	int current_line_size = gen::STRING_SIZE * 2;
	// The current_line array for reading in the file
	char current_line[current_line_size];
	// The object name that is being read in
	char * object_name = new char [current_line_size];
	// The object keys that are being read in
	char * object_keys = new char [current_line_size];
	// The return code, false if it can't open a file
	bool return_code = false;
	// The part of the object we are reading
	// 0 - name, 1 - keys, 2 - values
	int object_part = 0;
	// Open the file for reading
	load_file.open( file_name );
	// If the file is open then read
	if ( load_file.is_open() )
	{
		while ( !load_file.eof() )
		{
			// Get a line and store it in the current_line array
			load_file.get( current_line, current_line_size, '\n' );
			// Read in and ignore the newline
			load_file.ignore( current_line_size, '\n' );
			// If the string length of the line is less than 1
			// then it is the last line so theres nothing there
			// std::cout << object_part << '\n';
			if ( strlen( current_line ) < 1 )
			{
				break;
			}
			else if ( object_part == 0 )
			{
				strcpy( object_name, current_line );
			}
			else if ( object_part == 1 )
			{
				strcpy( object_keys, current_line );
			}
			else
			{
				// std::cout << "Creating object " << object_name << " keys: " << object_keys << " values: " << current_line << '\n';
				// Set the object name to have the vlaues corresponding to the keys
				this->get( object_name ).from_string( object_keys, current_line, delim );
				gen::strclr( object_name );
				gen::strclr( object_keys );
				gen::strclr( current_line );
			}
			++object_part;
			if ( object_part >= 3 )
			{
				object_part = 0;
			}
		}
		// A file was opened to return true
		return_code = true;
	}
	// Close the currently open file
	load_file.close();
	// Deallocate memoy
	delete [] object_name;
	delete [] object_keys;
	// Return whether a file was opened
	return return_code;
}