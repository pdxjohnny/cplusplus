/*
	Author: John Andersen
	Date: 02/19/2015
	Description: This program uses the employ class
		to find jobs matching certain keywords
	Algoritham: Load the jobs into memory
		Index the jobs with the hash table
		Look for a key
		Display the array of jobs for that key
*/



#include "employ.h"
#include <iostream>



int main( int argc, char ** argv )
{
	// Check for the name of the file containing the jobs
	if ( argc > 1 )
	{
		// Initialize with the name of the jobs file
		employ finder( argv[ 1 ] );
		// If there is a search peramiter then search
		// for it and display the results
		if ( argc > 2 )
		{
			// Get the size of the array
			int count = finder.size( argv[ 2 ] );
			// Get the array of jobs found with the given key
			job ** jobs = finder.find( argv[ 2 ] );
			// Loop through the array
			for ( int i = 0; i < count; ++i )
			{
				gen::line('#');
				// Print out the job
				finder.print_job( jobs[ i ] );
			}
			if ( count )
			{
				gen::line('#');
			}
			// Delete the array of pointers to jobs
			delete [] jobs;
		}
		else
		{
			// No search peramiter was given so display all jobs
			std::cout << "All Jobs\n";
			std::cout << finder.display_all() << " jobs\n";
		}
	}
	else
	{
		// Failed to provide jobs file name
		std::cout << "Usage: " << argv[0] << " jobs.csv \"String to search for\"\n";
	}
	return 0;
}
