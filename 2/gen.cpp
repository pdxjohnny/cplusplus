/*
	Author: John Andersen
	Date: 11/5/2014
	Description: General functions I always use
*/

// For class definition
#include "gen.h"


/*
	Namespace: gen
	Method: capitalize
	Use: Capitalises the first letter of every word
*/
void gen::capitalize( char *cap_me )
{
	// Remove any leading whitespace to
	// ensure the first char is not whitespace
	gen::remove_leading( cap_me, ' ' );
	gen::remove_leading( cap_me, '\t' );
	gen::toupper( cap_me[0] );
	// Loop through the whole array
	for (unsigned int i = 1; i < strlen( cap_me ); ++i)
	{
		// Every time there is a space before a letter
		// capitalize the letter
		if ( cap_me[i-1] == ' ' && cap_me[i] != ' ' )
		{
			gen::toupper( cap_me[i] );
		}
	}
	return;
}


/*
	Namespace: gen
	Method: toupper
	Use: Capitalises every letter in a string
*/
void gen::toupper( char *cap_me )
{
	// Loop through and capitalize every letter
	for ( unsigned int i = 0; i < strlen(cap_me); ++i)
	{
		gen::toupper(cap_me[i]);
	}
	return;
	// No time to try this, havent compiled it yet
	// while ( ( cap_me++ ) != 0 )
	// {
	// 	*cap_me = std::toupper(*cap_me);
	// }
	// return;
}


/*
	Namespace: gen
	Method: toupper
	Use: Capitalises a char by reference
*/
void gen::toupper( char &cap_me )
{
	cap_me = std::toupper(cap_me);
	return;
}


/*
	Namespace: gen
	Method: strclr
	Use: Clears a string
*/
void gen::strclr( char *clear )
{
	// Walks the lenght of the string and sets all
	// characters until the terminator to 0
	for ( unsigned int i = 0; i < strlen(clear); ++i )
	{
		clear[i] = 0;
	}
	return;
}


/*
	Namespace: gen
	Method: remove_char
	Use: Removes all instances of a character in a string
*/
void gen::remove_char( char *input, char remove_char )
{
	// Walks the lenght of the string
	for (unsigned int i = 0; i < strlen(input); ++i)
	{
		// While the current character is the character
		// that needs to be removed
		while ( input[i] == remove_char )
		{
			// Move all the characters one to the front
			for (unsigned int j = i; j < strlen(input); ++j)
			{
				input[j] = input[j+1];
			}
		}
	}
	return;
}


/*
	Namespace: gen
	Method: remove_leading
	Use: Removes all of a leading charater
		this is especially usefull to remove padding
*/
void gen::remove_leading( char *input, char remove_char )
{
	// While the first character is whitespace
	while ( input[0] == remove_char )
	{
		// Move each of the characters one to the front
		for (unsigned int j = 0; j < strlen(input); ++j)
		{
			input[j] = input[j+1];
		}
	}
}

/*
	Namespace: gen
	Method: remove_whitespace
	Use: Removes all whitespace in a string
*/
void gen::remove_whitespace( char *input )
{
	gen::remove_char( input, ' ' );
	gen::remove_char( input, '\t' );
	return;
}


/*
	Namespace: gen
	Method: remove_multi_whitespace
	Use: Removes all double, triple, etc spaces
*/
void gen::remove_multi_whitespace( char *input )
{
	// Removes any leading whitespace
	remove_leading( input, ' ' );
	remove_leading( input, '\t' );
	// Loop through the whole array
	for (unsigned int i = 1; i < strlen(input); ++i)
	{
		// If there are double spaces
		if ( input[i-1] == ' ' && input[i] == ' ' )
		{
			// Move the characters one to the front
			// until there is just a single space at
			// i-1 and i is not a space
			while ( input[i] == ' ' )
			{
				for (unsigned int j = i-1; j < strlen(input); ++j)
				{
					input[j] = input[j+1];
				}
			}
			// Subtract one from i to make sure we got all of them
			--i;
		}
	}
	return;
}


/*
	Namespace: gen
	Method: error_check
	Use: Calls remove_multi_whitespace and capitalize
*/
void gen::error_check( char *input )
{
	remove_multi_whitespace( input );
	capitalize( input );
	return;
}


/*
	Namespace: gen
	Method: split_line
	Use: Splits a line into two baised on the delim
*/
void gen::split_line( const char *line, char *first, char *second, const char delim )
{
	// This worked and now it doesn't so not for not
	// // Copy the characters while the character
	// // line points to is not the same as delim
	// while ( *line != delim && (*first++ = *line++) != 0 );
	// // Skip over the delim
	// line++;
	// // Copy the rest into second
	// while ( (*second++ = *line++) != 0 );
	// return;
	unsigned int i, j;
	for ( i = 0; i < strlen(line) && line[i] != delim; ++i)
	{
		// Copy the line into the first string
		first[i] = line[i];
	}
	// Set the character right after the last character
	// in first to the null terminator
	first[i] = '\0';
	// Skip over the deliminating character
	++i;
	for ( j = 0 ; i < strlen(line); ++i)
	{
		// Copy the line into the second string
		second[j] = line[i];
		++j;
	}
	// Set the character right after the last character
	// in second to the null terminator
	second[j] = '\0';
	return;
}


/*
	Namespace: gen
	Method: confirm
	Use: Askes yes or no, true if yes / y
*/

bool gen::confirm()
{
	// Array for the users input
	char selection[STRING_SIZE];
	// Ask the user yes or no
	std::cout << "(yes/no)\n# ";
	std::cin >> selection;
	// Remove any leading spaces
	gen::remove_whitespace(selection);
	// Capitalise the first letter
	gen::toupper(selection[0]);
	// If the first letter is a upercase Y
	// Then the answer is yes
	if ( selection[0] == 'Y' )
	{
		// Return true because user
		// said yes
		return true;
	}
	// Return false if it was anything but yes
	return false;
}


/*
	Namespace: gen
	Method: get_line
	Use: Prints "ask" then gets a response and stores it in "response"
*/
void gen::get_line( const char *ask, char* response, unsigned int response_size )
{
	// Set redo for checking if the size was acceptable
	bool redo = false;
	do
	{
		// If we need to redo let the user know they were
		// over the character limit
		if ( redo )
		{
			std::cout << "Sorry that was more than " << response_size-1 << " characters.\n";
			// Set redo to false so we don't
			// loop again if their answer was ok
			redo = false;
		}
		// Ask the question
		std::cout << ask;
		// Keep getting rid of the first character
		// so long as its a new line
		while ( (char)std::cin.peek() == '\n' )
		{
			// Get rid of it
			std::cin.ignore(1);
		}
		// Now that the first character is not a new line
		// we can get all the characters until a new line
		std::cin.get( response, response_size-1, '\n' );
		// If we got all the characters and there is something
		// other than the newline in the buffer then the
		// user must have input too many characters
		if ( (char)std::cin.peek() != '\n' )
		{
			// Clear the users response
			gen::strclr( response );
			// Throw out anything thats still in the buffer
			std::cin.ignore(1000,'\n');
			// Make sure we ask them again
			redo = true;
		}
	}
	while ( redo );
	// When the loop exits there should be a single newline
	// still in the stream we should ignore
	std::cin.ignore(1000,'\n');
	return;
}


/*
	Namespace: gen
	Method: number
	Use: Checks to see if the string contains all
		numbers
*/
bool gen::number( char * string )
{
	// Walk the string
	if ( gen::is_int( string ) || gen::is_float( string ) )
	{
		return true;
	}
	// If we didn't find a non digit
	return false;
}



/*
	Namespace: gen
	Method: is_int
	Use: Checks to see if the string contains all
		is_ints
*/
bool gen::is_int( char * string )
{
	// Walk the string
	while( *string )
	{
		// Allow negative numbers
		if ( !std::isdigit( *string ) )
		{
			// If its not a negative sign and not a digit
			return false;
		}
		// Go to the next charater
		string++;
	}
	// If we didn't find a non digit
	return true;
}



/*
	Namespace: gen
	Method: is_float
	Use: Checks to see if the string contains all
		is_floats
*/
bool gen::is_float( char * string )
{
	// Walk the string
	while( *string )
	{
		// Allow negative numbers
		if ( *string != '-' && !std::isdigit( *string ) )
		{
			// If its not a negative sign and not a digit
			return false;
		}
		// Go to the next charater
		string++;
	}
	// If we didn't find a non digit
	return true;
}



/*
	Namespace: gen
	Method: count
	Use: Counts the occurences of a char in a string
*/
int gen::count( char * string, const char delim )
{
	unsigned int num = 0;
	// Walk the string
	while( *string )
	{
		// Check for delim
		if ( *string == delim )
		{
			++num;
		}
		// Go to the next charater
		string++;
	}
	// Return the number of occurences
	return num;
}



/*
	Namespace: gen
	Method: add_to_csv
	Use: Creates a csv string given the current string
		and the string to add to it
*/
void gen::add_to_csv( int column_position, int column_count, char * string, char * add, const char delim )
{
	// std::cout << column_position << " out of " << column_count << " adding " << add << '\n';
	// std::cout << "column_position == column_count: " << (column_position == column_count) << '\n';
	if ( strlen( add ) < 1 )
	{
		return;
	}
	if ( column_position == 0 && column_position == column_count )
	{
		// First time, don't copy over existing because
		// there is no data in sting yet
		sprintf( string, "%s", add );
	}
	else if ( column_position == 0 )
	{
		// First time, don't copy over existing because
		// there is no data in sting yet
		sprintf( string, "%s%c", add, delim );
	}
	else if ( column_position >= column_count )
	{
		// If this is the last then we know not to add
		// the delim at the end
		sprintf( string, "%s%s", string, add );
	}
	else
	{
		// Otherwise copy over the previous key and then
		// the current column followed by the delim
		sprintf( string, "%s%s%c", string, add, delim );
	}
}



/*
	Namespace: gen
	Method: line
	Use: Creates a horizontal line across the screen
*/
void gen::line( const char character )
{
	// Get the size of the terminal
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	// Print the character the number of columns
	// that the window is across
	for ( unsigned int i = 0; i < w.ws_col; ++i )
	{
		std::cout << character;
	}
	std::cout << '\n';
}



/*
	Namespace: gen
	Method: thread
	Use: Forks off and returns true if it is the client
*/
int gen::thread( void )
{
	return !(fork());
}




/*
	Namespace: gen
	Method: handle_input
	Use: Prompts the user for what they want to do.
		Calls the appropriate method.
		Returns false if the user wants to exit.
*/
/*
bool gen::handle_input( gen::functions )
{
	// Hold the input of the user
	char user_input[gen::STRING_SIZE],
		action[gen::STRING_SIZE],
		source[gen::STRING_SIZE] = "";
	// Ask the user what they would like to do
	gen::get_line("Would you like to add, list (source), or save your forecasts? (\"exit\" to exit)# ", user_input, gen::STRING_SIZE);
	gen::split_line( user_input, action, source, ' ' );
	// Return false if they want to exit
	if ( strcmp( action, "exit" ) == 0 )
	{
		return false;
	}
	// If they want to save attempt to save
	else if ( strcmp( action, "save" ) == 0 )
	{
		if ( !this->save() )
		{
			std::cout << "Failed to save\n";
		}
	}
	// If they want to list then list
	else if ( strcmp( action, "list" ) == 0 )
	{
		this->weather_data.list( source );
	}
	// If they want to add then add a forecast
	else if ( strcmp( action, "add" ) == 0 )
	{
		this->weather_data.add();
	}
	// If they want to remove then remove a forecast
	else if ( strcmp( action, "remove" ) == 0 )
	{
		this->weather_data.remove();
	}
	// As long as they don't want to exit return true
	return true;
}
*/