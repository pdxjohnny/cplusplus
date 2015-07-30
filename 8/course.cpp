/*
	Author: John Andersen
	Date: 11/4/2014
	Description: Course class methods
*/


// For the course class
#include "course.h"


/*
	Class: course
	Method: from_string
	Use: Parses a csv string into data members
*/
void course::from_string( char *course_info )
{
	// Create srings for the numbered data types so we can parse
	// the input into seperate strings then convert to numbers
	char section_string[gen::STRING_SIZE];
	// The string should be in csv format so we just parse it in order
	gen::split_line( course_info, this->CRN, course_info, ',' );
	gen::split_line( course_info, this->designator, section_string, ',' );
	// Convert the section to an int and make sure its positive
	this->section = std::atoi( section_string );
	if ( this->section < 0 )
	{
		this->section *= -1;
	}
}


/*
	Class: course
	Method: prompt
	Use: Propmts user for the values of data members
*/
void course::prompt( void )
{
	// Holds the users input to a question
	char user_input[gen::STRING_SIZE];
	// Ask the user for their course information
	gen::get_line( "What's the course CRN(12345-678), course designator(CS162), and section(number)?\n# ", user_input, gen::STRING_SIZE );
	// Capitalize everything and remove whitespace
	gen::toupper( user_input );
	gen::remove_whitespace( user_input );
	// Parses the string into the members
	this->from_string( user_input );
}


/*
	Class: course
	Method: print
	Use: Creates a string of the class to be displayed as a table
*/
char *course::print( void )
{
	// Make the as_string array only about as long as it needs to be
	unsigned int all_lengths = strlen( this->CRN ) + strlen( this->designator ) + gen::STRING_SIZE;
	// Make a pointer and assign it to an array of proper size so it
	// can be referenced outside this function
	char *as_string = new char[all_lengths];
	// Format the string so it looks like a table
	sprintf( as_string, "%s\t\t|%s\t\t\t|%d\n", this->CRN, this->designator, this->section );
	return as_string;
}


/*
	Class: course
	Method: save
	Use: Creates a string of the class in csv format
*/
char *course::save( void )
{
	// Make the as_string array only about as long as it needs to be
	unsigned int all_lengths = strlen( this->CRN ) + strlen( this->designator ) + gen::STRING_SIZE;
	// Make a pointer and assign it to an array of proper size so it
	// can be referenced outside this function
	char *as_string = new char[all_lengths];
	// Format the string, csv is great for parseing in
	sprintf( as_string, "%s,%s,%d\n", this->CRN, this->designator, this->section );
	return as_string;
}
