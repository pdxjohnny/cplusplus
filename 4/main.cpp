/*
	Author: John Andersen
	Date: 02/19/2015
	Description: See README
	Algorithm:
		Load data
		Search For data
		Possiblly change or remove data
		Save data
*/



#include "vote.h"
#include <iostream>



/*
	Function: print
	Use: Prints a nomination
	Input: Vote instance and the key to find and display
	Output: Prints all the nominations found to the screen
*/
void print( vote & finder, char * find )
{
	// Number of nominations in the array of nominations found
	int count = finder.size( find );
	// Array of nominations found matching the key
	nomination ** nominations = finder.find( find );
	for ( int i = 0; i < count; ++i )
	{
		// For style to ease the eye
		gen::line('-');
		// Print the nomination
		finder.print_nomination( nominations[ i ] );
	}
	if ( count )
	{
		// For style to ease the eye
		gen::line('-');
	}
	// Delete the array of pointers we were given
	delete [] nominations;
}



/*
	Function: set
	Use: Sets the votes of all nominations found
	Input: Finder instance, nominations file name, key to search for and number to set
	Output: Number of nominations found for key
*/
int set( vote & finder, char * file_name, char * find, int num )
{
	print( finder, find );
	// Grab the array of elements matching the string
	nomination ** nominations = finder.find( find );
	// Finde the number of elemenets in the array 
	int count = finder.size( find );
	// Loop through all the nominations found
	for ( int i = 0; i < count; ++i )
	{
		// For style to ease the eye
		gen::line('-');
		// Set the votes to the given value
		nominations[ i ]->votes = num;
		// Print the nomination
		finder.print_nomination( nominations[ i ] );
	}
	if ( count )
	{
		// For style to ease the eye
		gen::line('-');
	}
	// Delete the array of pointers we were given
	delete [] nominations;
	// Save them because we set new votes
	finder.save( file_name );
	return count;
}



/*
	Function: add
	Use: Increments the votes of all nominations found
	Input: Finder instance, nominations file name, key to search for and number to add
	Output: Number of nominations found for key
*/
int add( vote & finder, char * file_name, char * find, int num )
{
	print( finder, find );
	// Grab the array of elements matching the string
	nomination ** nominations = finder.find( find );
	// Finde the number of elemenets in the array 
	int count = finder.size( find );
	// Loop through all the nominations found
	for ( int i = 0; i < count; ++i )
	{
		// For style to ease the eye
		gen::line('-');
		// Add the votes to the given value
		nominations[ i ]->votes += num;
		// Print the nomination
		finder.print_nomination( nominations[ i ] );
	}
	if ( count )
	{
		// For style to ease the eye
		gen::line('-');
	}
	// Delete the array of pointers we were given
	delete [] nominations;
	// Save them because we added to the votes
	finder.save( file_name );
	return count;
}



/*
	Function: remove
	Use: Removes all nominations found
	Input: Finder instance, nominations file name, key to search for
	Output: Number of nominations found for key
*/
int remove( vote & finder, char * file_name, char * find )
{
	// Grab the array of elements matching the string
	nomination ** nominations = finder.find( find );
	// Finde the number of elemenets in the array 
	int count = finder.size( find );
	// Loop through all the nominations found
	for ( int i = 0; i < count; ++i )
	{
		// For style to ease the eye
		gen::line('-');
		// Print the nomination
		finder.print_nomination( nominations[ i ] );
		// Delete the nomination
		finder.remove_nomination( nominations[ i ] );
	}
	if ( count )
	{
		// For style to ease the eye
		gen::line('-');
	}
	// Delete the array of pointers we were given
	delete [] nominations;
	// Save the ones that weren't removed
	finder.save( file_name );
	return count;
}



int main( int argc, char ** argv )
{
	// Check if the file name is given
	if ( argc > 1 )
	{
		// Load from the file
		vote finder( argv[ 1 ] );
		if ( argc > 4 && 0 == strcmp( argv[ 3 ], "set" ) )
		{
			// set the votes of the items that match the search criteria
			set( finder, argv[ 1 ], argv[ 2 ], atoi( argv[ 4 ] ) );
		}
		else if ( argc > 4 && 0 == strcmp( argv[ 3 ], "add" ) )
		{
			// add to the votes of the items that match the search criteria
			add( finder, argv[ 1 ], argv[ 2 ], atoi( argv[ 4 ] ) );
		}
		else if ( argc > 3 && 0 == strcmp( argv[ 3 ], "remove" ) )
		{
			// remove the items that match the search criteria
			remove( finder, argv[ 1 ], argv[ 2 ] );
		}
		else if ( argc > 2 )
		{
			// Print the findings
			print( finder, argv[ 2 ] );
		}
		else
		{
			// No nomination to search for so display them all
			std::cout << "All nominations\n";
			finder.display_all();
		}
	}
	else
	{
		// Display usage message
		std::cout << "Usage: " << argv[0] << " nominations.csv ";
		std::cout << "\"Name, Movie, or Award to search for\" ";
		std::cout << "( add, set, remove ) ( number of votes )\n";
	}
	return 0;
}
