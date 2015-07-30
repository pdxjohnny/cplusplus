/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Voting for oscars class
*/



#include "gen.h"
#include "tree.h"
#include "hash.h"
#include <fstream>


/*
	Struct: nomination
	Use: Holds the actors name the awrad they are in the running for
		as well as what movie they were in and the award category
		also the number of votes they have
*/
struct nomination
{
	char * name;
	char * movie;
	char * category;
	int votes;
};


/*
	Class: vot
	Use: Facilitates voting for the oscars with indexing nominations
*/
class vote
{
	public:
		// Initialises data members and loads from file
		vote( char * file_name );
		// Deallocates all of the nominations
		~vote();
		// Displays a nomination
		void print_nomination( nomination * print );
		// Makes a csv string from the nomination
		void string_nomination( char * string, nomination * print );
		// Deallocates the members of a nomination
		void delete_nomination( nomination * del );
		// Adds a nomination to the hash table
		void add_nomination( nomination * add );
		// Removes a nomination from the hash table and the tree of all nominations
		void remove_nomination( nomination * add );
		// Creates a nomination from a csv string
		nomination * parse( char * line );
		// Gives the number of nominations for a given key
		int size( char * text );
		// Finds nominations associated with a key
		nomination ** find( char * text );
		// Loads the contents of a file into nomination strutures
		int load( char * file_name );
		// Writes nominations back to file
		int save( char * file_name );
		// Displays all loaded nominations
		int display_all( void );
	private:
		// Character that deliminate the save file
		char delim;
		// All the nominations
		tree<nomination *> all_nominations;
		// Indexed nominations
		hash< void( tree< tree<nomination *> >, tree<nomination *> ) > all;
};


