/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Voting for oscars class
*/



#include "vote.h"



/*
	Class: vote
	Method: Constructor
	Use: Initialises data members and loads from file
	Input: Filename of the file that contains the nominations
	Output: None
*/
vote::vote( char * file_name )
{
	// Set the character that the deliminates the csv file
	// obviously its not a comma
	delim = '\t';
	// Load nominations from the specified file
	load( file_name );
};



/*
	Class: vote
	Method: Destructor
	Use: Deallocates all of the nominations
	Input: None
	Output: None
*/
vote::~vote()
{
	// Get the number of nominations in the tree
	unsigned int count = all_nominations.size();
	// Create an array for faster access of nominations stored in the tree
	nomination *** all = all_nominations.all();
	// Loop through all of the nominations
	for ( unsigned int i = 0; i < count; ++i )
	{
		// Deallocate the nomination
		delete_nomination( * all[ i ] );
	}
	delete [] all;
};



/*
	Class: vote
	Method: print_nomination
	Use: Displays a nomination
	Input: A pointer to the nomination to be displayed
	Output: Prints nomination to screen
*/
void vote::print_nomination( nomination * print )
{
	// Check if there is a nomination to print
	if ( print )
	{
		// Loop through because I haven't changed this
		for ( unsigned int i = 0; i < 4; ++i )
		{
			// Print the appropriate nomination data member
			switch ( i )
			{
				case 0:
					std::cout << color::blue;
					std::cout << '\t' << print->name << '\n';
					std::cout << color::normal;
					break;
				case 1:
					std::cout << "Movie:\t\t" << print->movie << '\n';
					break;
				case 2:
					std::cout << "Nominated For:\t" << print->category << '\n';
					break;
				case 3:
					std::cout << "Votes:\t\t" << print->votes << '\n';
					break;
				default:
					break;
			}
		}
	}
}



/*
	Class: vote
	Method: string_nomination
	Use: Makes a csv string from the nomination
	Input: String to format and the nomination to format with
	Output: None
*/
void vote::string_nomination( char * string, nomination * print )
{
	// Check if there is a nomination to create a string from
	if ( print )
	{
		// Loop through because I haven't changed this
		for ( unsigned int i = 0; i < 4; ++i )
		{
			// Copy the members into the string
			switch ( i )
			{
				case 0:
					sprintf( string, "%s%c", print->name, delim );
					break;
				case 1:
					sprintf( string, "%s%s%c", string, print->movie, delim );
					break;
				case 2:
					sprintf( string, "%s%s%c", string, print->category, delim );
					break;
				case 3:
					sprintf( string, "%s%d", string, print->votes );
					break;
				default:
					break;
			}
		}
	}
}



/*
	Class: vote
	Method: delete_nomination
	Use: Deallocates the members of a nomination
	Input: Pointer to the nomination
	Output: None
*/
void vote::delete_nomination( nomination * del )
{
	// Check if there is a nomination to delete
	if ( del )
	{
		// Loop through because I haven't changed this
		for ( unsigned int i = 0; i < 4; ++i )
		{
			switch ( i )
			{
				// Delete all of the members
				case 0:
					delete [] del->name;
					break;
				case 1:
					delete [] del->movie;
					break;
				case 2:
					delete [] del->category;
					break;
				default:
					break;
			}
		}
	}
	delete del;
}



/*
	Class: vote
	Method: add_nomination
	Use: Adds a nomination to the hash table
	Input: Pointer to nomination to add
	Output: None
*/
void vote::add_nomination( nomination * add )
{
	// Check if there is a nomination to add
	if ( add )
	{
		char add_key [ gen::STRING_SIZE ];
		// Loop through because I haven't changed this
		for ( unsigned int i = 0; i < 4; ++i )
		{
			// Get each key and add cpy it over to add it to the hash table
			switch ( i )
			{
				case 0:
					strcpy( add_key, add->name );
					break;
				case 1:
					strcpy( add_key, add->movie );
					break;
				case 2:
					strcpy( add_key, add->category );
					break;
				default:
					break;
			}
			gen::tolower( add_key );
			all[ add_key ].get( add->name ) = add;
		}
	}
}



/*
	Class: vote
	Method: remove_nomination
	Use: Removes a nomination from the hash table and the tree of all nominations
	Input: Pointer to the nomination to be removed
	Output: None
*/
void vote::remove_nomination( nomination * rm )
{
	// Check if there is a nomination to remove
	if ( rm )
	{
		char rm_key [ gen::STRING_SIZE ];
		// Loop through because I haven't changed this
		for ( unsigned int i = 0; i < 4; ++i )
		{
			// Remove the name from the hash table under whichever keys it is seen
			switch ( i )
			{
				case 0:
					strcpy( rm_key, rm->name );
					break;
				case 1:
					strcpy( rm_key, rm->movie );
					break;
				case 2:
					strcpy( rm_key, rm->category );
					break;
				default:
					break;
			}
			gen::tolower( rm_key );
			all[ rm_key ].remove( rm->name );
		}
		all_nominations.remove( rm->name );
		delete_nomination( rm );
	}
}



/*
	Class: vote
	Method: parse
	Use: Creates a nomination from a csv string
	Input: CSV string
	Output: New nomination
*/
nomination * vote::parse( char * line )
{
	// Create the nomination
	nomination * nomination_loaded = new nomination;
	// The size of the string
	int value_size = gen::STRING_SIZE * 2;
	// The string to hold the value being parsed in
	char value [ value_size ];
	// The value that will be allocated
	char * nomination_value = NULL;
	// The number of values to parse in
	int values = gen::count( line, delim ) + 1;
	for ( int i = 0; i < values; ++i )
	{
		// Pop off the value
		gen::split_line( line, value, line, delim );
		// Create a string of the correct length
		nomination_value = new char [ strlen( value ) + 1 ];
		// Copy the string
		strcpy( nomination_value, value );
		// For some reason I used to need this
		// if ( i == values - 1 )
		// {
		// 	nomination_value[ strlen( nomination_value ) - 1 ] = '\0';
		// }
		// Set the appropriate member
		switch ( i )
		{
			case 0:
				nomination_loaded->name = nomination_value;
				break;
			case 1:
				nomination_loaded->movie = nomination_value;
				break;
			case 2:
				nomination_loaded->category = nomination_value;
				break;
			case 3:
				nomination_loaded->votes = atoi( nomination_value );
				delete [] nomination_value;
				break;
			default:
				delete [] nomination_value;
				break;
		}
		gen::strclr( value );
	}
	return nomination_loaded;
}




/*
	Class: vote
	Method: size
	Use: Gives the number of nominations for a given key
	Input: Key to search for
	Output: The number of nominations found
*/
int vote::size( char * text )
{
	gen::tolower( text );
	return all[ text ].size();
}




/*
	Class: vote
	Method: find
	Use: Finds nominations associated with a key
	Input: Key to search for
	Output: Array of nominations associated with the key
*/
nomination ** vote::find( char * text )
{
	gen::tolower( text );
	int num = size( text );
	nomination ** nominations = NULL;
	if ( num )
	{
		// Avoid using the subsript operator on the hash table
		tree< nomination * > * look = & all[ text ];
		nominations = new nomination * [ num ];
		for ( int i = 0; i < num; ++i )
		{
			// Grab all the nominations for the key and store them in an array
			nominations[ i ] = look->get( i );
		}
	}
	return nominations;
}



/*
	Class: vote
	Method: load
	Use: Loads the contents of a file into nomination strutures
	Input: Filename to be loaded
	Output: Number of nominations loaded
*/
int vote::load( char * file_name )
{
	int num_loaded = 0;
	bool headers = true;
	std::ifstream file;
	file.open( file_name );
	if ( file.is_open() )
	{
		int curr_size = gen::STRING_SIZE * 2;
		char curr_line [ curr_size ];
		while ( !file.eof() )
		{
			// Get a line and store it in the curr_line array
			file.get( curr_line, curr_size, '\n' );
			// Read in and ignore the newline
			file.ignore( curr_size, '\n' );
			// If there is data on the line
			if ( !headers && strlen( curr_line ) > 2 )
			{
				// Load the nomination from the line
				nomination * current = parse( curr_line );
				if ( !all_nominations.contains( current->name ) )
				{
					// Add the nomination to the tree of all of them
					all_nominations[ current->name ] = current;
					// Add the nomination to the hash it needs to be in
					add_nomination( current );
					// A nomination was loaded
					++num_loaded;
				}
				else
				{
					delete_nomination( current );
				}
			}
			headers = false;
		}
		file.close();
	}
	return num_loaded;
}



/*
	Class: vote
	Method: save
	Use: Writes nominations back to file
	Input: Filename to save to
	Output: Number of nominations saved
*/
int vote::save( char * file_name )
{
	int num_saved = 0;
	bool headers = true;
	std::ifstream old_file;
	std::ofstream save_file;
	old_file.open( file_name );
	char temp_file_name [] = ".temp.csv";
	save_file.open( temp_file_name );
	if ( old_file.is_open() && save_file.is_open() )
	{
		// Output the headers
		save_file << "name\tmovie\tcategory\tvotes\n";
		int string_size = gen::STRING_SIZE * 2;
		char old_line [ string_size ];
		char curr_line [ string_size ];
		while ( !old_file.eof() )
		{
			if ( headers )
			{
				// Get a line and store it in the old_line array
				old_file.get( old_line, string_size, '\n' );
				// Read in and ignore the newline
				old_file.ignore( string_size, '\n' );
				headers = false;
			}
			// Get a line and store it in the old_line array
			old_file.get( old_line, string_size, delim );
			// Read in and ignore the newline
			old_file.ignore( string_size, '\n' );
			if ( strlen( old_line ) > 2 )
			{
				// Load the nomination from the line
				if ( all_nominations.contains( old_line ) )
				{
					string_nomination( curr_line, all_nominations[ old_line ] );
					save_file << curr_line << '\n';
					++num_saved;
				}
			}
			gen::strclr( old_line );
			gen::strclr( curr_line );
		}
		old_file.close();
		save_file.close();
		if ( remove( file_name ) == 0 )
		{
			rename( temp_file_name, file_name );
		}
	}
	return num_saved;
}



/*
	Class: vote
	Method: display_all
	Use: Displays all loaded nominations
	Input: None
	Output: Number of nominations loaded
*/
int vote::display_all( void )
{
	// Get an array of all the nominationm
	int count = all_nominations.size();
	nomination *** all = all_nominations.all();
	// Loop through and print them all
	for ( int i = 0; i < count; ++i )
	{
		gen::line('-');
		print_nomination( * all[ i ] );
	}
	if ( count )
	{
		gen::line('-');
	}
	delete [] all;
	return count;
}


