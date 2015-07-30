#include "dict.h"
#include "hash.h"
#include "gen.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>


// The maximum size of a string
const int STRING_SIZE = 30;



/*
	Function: random word
	Use: Creates a random word of random size
*/
int random_word( char * string )
{
	// The size f the word
	int count = rand() % STRING_SIZE;
	for (int i = 0; i < count; ++i)
	{
		// Random lowercase asciii char
		string[ i ] = rand() % 26 + 97;
	}
	// Remember to null terminate the string
	string[ count ] = '\0';
	return count;
}



int main( int argc, char *argv[] )
{
	if ( argc > 2 )
	{
		// Make sure everything is really random
		srand(time(NULL));
		// Create the table of specified size
		int table_size = atoi( argv[1] );
		// Number of random words to be tested
		int num = atoi( argv[2] );
		// The hash table created with the table size
		hash< void ( dict<int>, int ) > table( table_size );
		// The hits array for recording how many times an
		// index in the hash table is hit
		int hits [ table_size ];
		// For the output
		std::ofstream results_file;
		// The char array to hold the random words
		char word [ STRING_SIZE ];
		// Fill the hits array with zeros
		for ( int i = 0; i < table_size; ++i )
		{
			hits[ i ] = 0;
		}
		// Create num many random words
		for ( int i = 0; i < num; ++i )
		{
			// If a word was created
			if ( random_word( word ) )
			{
				// Inrement the times the index was hit
				++hits[ table.hash_function( word ) ];
			}
			// Empty the char array
			gen::strclr( word );
		}
		// Open the results file
		results_file.open("test.txt");
		// If its open
		if ( results_file.is_open() )
		{
			// Output each index with the times it was hit
			for ( int i = 0; i < table_size; ++i )
			{
				results_file << i << '\t' << hits[ i ] << '\n';
			}
		}
		// Close the results file
		results_file.close();
	}
	return 0;
}