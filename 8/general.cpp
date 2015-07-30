/*
	Author: John Andersen
	Date: 11/5/2014
	Description: General functions I always use
*/

// For class definition
#include "general.h"


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
		first[i] = line[i];
	}
	// Set the character right after the last character
	// in first to the null terminator
	first[i] = '\0';
	// Skip over the deliminating character
	++i;
	for ( j = 0 ; i < strlen(line); ++i)
	{
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
