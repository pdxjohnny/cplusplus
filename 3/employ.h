/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Employ class uses a csv file and indexs
		all the columns with a hash table for easy retrival by column
*/



#include "gen.h"
#include "dict.h"
#include "hash.h"
#include <fstream>



/*
	Struct: job
	Use: Holds all the fields of a job listing
		plus any keywords specified
*/
struct job
{
	char * employer;
	char * city;
	char * state;
	char * title;
	char * description;
	char * experiance;
	float pay;
	dict<char *> key_words;
};



/*
	Class: employ
	Use: Provides easy retrival of job
		listings stored in a csv file
*/
class employ
{
	public:
		// Sets the delimiter and loads the file
		employ( char * file_name );
		// Dealloates all the jobs
		~employ();
		// Finds all the jobs of a keyword
		job ** find( char * text );
		// Creates a job from a csv string
		job * parse( char * line );
		// Adds a job to all the hash tables by key
		void add_job( job * add );
		// Displays a job
		void print_job( job * print );
		// Deallocate all data members of a job and keywords
		void delete_job( job * del );
		// Loads a csv file into the class instance
		int load( char * file_name );
		// Gives the size of a key dictonary
		int size( char * text );
		// Displays all jobs that are loaded
		int display_all( void );
	private:
		// The character that deliminates the csv file
		char delim;
		// All of the jobs
		dict<job *> all_jobs;
		// The hash table for indexing by keys
		hash< void( dict< dict<job *> >, dict<job *> ) > all;
};


