/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Employ class uses a csv file and indexs
		all the columns with a hash table for easy retrival by column
*/



#include "employ.h"



/*
	Class: employ
	Method: Constructor
	Use: Sets the delimiter and loads the file
	Input: The filename to be loaded
	Output: None
*/
employ::employ( char * file_name )
{
	// The deliminating character for the file
	delim = ',';
	// The first thing that needs to be done is
	// load all the jobs from a file
	load( file_name );
};



/*
	Class: employ
	Method: Destructor
	Use: Dealloates all the jobs
	Input: None
	Output: None
*/
employ::~employ()
{
	// Loop through all the jobs and deallocate them
	for ( unsigned int i = 0; i < all_jobs.size(); ++i )
	{
		delete_job( all_jobs[ i ] );
	}
};



/*
	Class: employ
	Method: find
	Use: Finds all the jobs of a keyword
	Input: The keyword to find
	Output: An arry of jobs with that keyword
*/
job ** employ::find( char * text )
{
	// Lowercase the text
	gen::tolower( text );
	// The size of the dictionary
	int num = size( text );
	// The pointer to the array of jobs
	job ** jobs = NULL;
	// Make sure there are jobs found
	if ( num )
	{
		// Create an array the size of the jobs found
		jobs = new job * [ num ];
		// Loop through all the jobs
		for ( int i = 0; i < num; ++i )
		{
			// Put the job in the array
			jobs[ i ] = all[ text ][ i ];
		}
	}
	// Return the jobs found array
	return jobs;
}



/*
	Class: employ
	Method: parse
	Use: Creates a job from a csv string
	Input: The line to be parsed into a jobs data members
	Output: The job created and filled
*/
job * employ::parse( char * line )
{
	// Create a new job
	job * job_loaded = new job;
	// The length of the string value
	int value_size = gen::STRING_SIZE;
	// The value wtring which is used to split
	// up the line into members
	char value [ value_size ];
	// This is a pionter to a character array that
	// gets allocated to the right sie then set to
	// the correct data member
	char * job_value = NULL;
	// The number of key words a job has
	int key_words = 0;
	// The number of values to be parsed in
	int values = gen::count( line, delim ) + 1;
	// Loop trough all the values to be read
	for ( int i = 0; i < values; ++i )
	{
		// Pop off the first value from the line
		gen::split_line( line, value, line, delim );
		// Make the job_value the right length
		job_value = new char [ strlen( value ) + 1 ];
		// Copy the string over
		strcpy( job_value, value );
		// If it is the last value the fix the string
		if ( i == values - 1 )
		{
			// For some reason it gets messed up so the null
			// terminating character has to be set
			job_value[ strlen( job_value ) - 1 ] = '\0';
		}
		// Based on the number set the member
		switch ( i )
		{
			case 0:
				job_loaded->employer = job_value;
				break;
			case 1:
				job_loaded->city = job_value;
				break;
			case 2:
				job_loaded->state = job_value;
				break;
			case 3:
				job_loaded->title = job_value;
				break;
			case 4:
				job_loaded->description = job_value;
				break;
			case 5:
				job_loaded->experiance = job_value;
				break;
			case 6:
				job_loaded->pay = atof( job_value );
				delete [] job_value;
				break;
			default:
				job_loaded->key_words[ key_words ] = job_value;
				++key_words;
				break;
		}
		// Make sure the string gets emptied
		gen::strclr( value );
	}
	// The job that was just filled
	return job_loaded;
}



/*
	Class: employ
	Method: add_job
	Use: Adds a job to all the hash tables by key
	Input: Pointer to a job to add
	Output: None
*/
void employ::add_job( job * add )
{
	// For the key word we are on
	int key_words = 0;
	// The key to hash on
	char add_key [ gen::STRING_SIZE ];
	for ( unsigned int i = 0; i < 7 + add->key_words.size(); ++i )
	{
		// Copy the contents of whatever member we are on into
		// the add_key array of characters
		switch ( i )
		{
			case 0:
				strcpy( add_key, add->employer );
				break;
			case 1:
				strcpy( add_key, add->city );
				break;
			case 2:
				strcpy( add_key, add->state );
				break;
			case 3:
				strcpy( add_key, add->title );
				break;
			case 4:
				strcpy( add_key, add->description );
				break;
			case 5:
				strcpy( add_key, add->experiance );
				break;
			case 6:
				sprintf( add_key, "%.2f", add->pay );
				break;
			default:
				strcpy( add_key, add->key_words[ key_words ] );
				++key_words;
				break;
		}
		// Makes the key lower case so its easier to find
		gen::tolower( add_key );
		// The hash table all gives a dict that
		// given the title returns a poiner to job
		// which is set to the job to add
		all[ add_key ][ add->title ] = add;
	}
}



/*
	Class: employ
	Method: print_job
	Use: Displays a job
	Input: Pointer to a job to print
	Output: None
*/
void employ::print_job( job * print )
{
	// For the key word we are on
	int key_words = 0;
	// Loop through all 7 members and all keywords
	for ( unsigned int i = 0; i < 7 + print->key_words.size(); ++i )
	{
		// Based on the number display the member
		switch ( i )
		{
			case 0:
				// Color makes is easier to read
				std::cout << color::blue;
				std::cout << '\t' << print->title << '\n';
				std::cout << color::normal;
				break;
			case 1:
				std::cout << print->employer << '\n';
				break;
			case 2:
				std::cout << print->city << '\n';
				break;
			case 3:
				std::cout << print->state << '\n';
				break;
			case 4:
				std::cout << print->description << '\n';
				break;
			case 5:
				std::cout << print->experiance << '\n';
				break;
			case 6:
				std::cout << '$' << print->pay << "/hr" << '\n';
				break;
			default:
				std::cout << print->key_words[ key_words ] << '\n';
				++key_words;
				break;
		}
	}
}



/*
	Class: employ
	Method: delete_job
	Use: Deallocate all data members of a job and keywords
	Input: Pointer to job to delete
	Output: None
*/
void employ::delete_job( job * del )
{
	// For the key word we are on
	int key_words = 0;
	// Loop through all 6 char arrays and all keywords
	for ( unsigned int i = 0; i < 6 + del->key_words.size(); ++i )
	{
		// Based on the number delete the member
		switch ( i )
		{
			case 0:
				delete [] del->employer;
				break;
			case 1:
				delete [] del->city;
				break;
			case 2:
				delete [] del->state;
				break;
			case 3:
				delete [] del->title;
				break;
			case 4:
				delete [] del->description;
				break;
			case 5:
				delete [] del->experiance;
				break;
			default:
				delete [] del->key_words[ key_words ];
				++key_words;
				break;
		}
	}
	// Delete the jobs struct
	delete del;
}



/*
	Class: employ
	Method: load
	Use: Loads a csv file into the class instance
	Input: The name of the csv file
	Output: The number of jobs loaded
*/
int employ::load( char * file_name )
{
	// The number of jobs loaded
	int num_loaded = 0;
	// If the current line is the headers
	bool headers = true;
	// The file object
	std::ifstream file;
	// Open the file
	file.open( file_name );
	// If the file is open then read int he data
	if ( file.is_open() )
	{
		// This the the size of the line to be read in
		int curr_size = gen::STRING_SIZE * 10;
		// Create an array of that size
		char curr_line [ curr_size ];
		// While its not the end of the file
		while ( !file.eof() )
		{
			// Get a line and store it in the curr_line array
			file.get( curr_line, curr_size, '\n' );
			// Read in and ignore the newline
			file.ignore( curr_size, '\n' );
			// If there is data on the line and it is not the header
			if ( !headers && strlen( curr_line ) > 2 )
			{
				// Load the job from the line
				all_jobs[ num_loaded ] = parse( curr_line );
				// Add the job to the hash it needs to be in
				add_job( all_jobs[ num_loaded ] );
				// A job was loaded
				++num_loaded;
			}
			// False if the line is not the headers
			headers = false;
		}
	}
	// Return the number of jobs loaded
	return num_loaded;
}



/*
	Class: employ
	Method: size
	Use: Gives the size of a key dictonary
	Input: The key to find
	Output: The number of jobs accosiated with that key
*/
int employ::size( char * text )
{
	// Lowercase the text
	gen::tolower( text );
	// Return the size of the dictionary
	return all[ text ].size();
}



/*
	Class: employ
	Method: display_all
	Use: Displays all jobs that are loaded
	Input: None
	Output: The number of jobs in the class instance
*/
int employ::display_all( void )
{
	// Get the number of jobs in the list of all of them
	int count = all_jobs.size();
	// Loop through all the jobs
	for ( int i = 0; i < count; ++i )
	{
		gen::line('#');
		// Print the job
		print_job( all_jobs[ i ] );
	}
	if ( count )
	{
		// Just a end delimiter for style
		gen::line('#');
	}
	// Return the number of jobs
	return count;
}
