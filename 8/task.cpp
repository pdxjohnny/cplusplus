/*
	Author: John Andersen
	Date: 11/8/2014
	Description: Task class methods
*/

// Include the task class and date_object struct definitions
#include "task.h"


/*
	Class: task
	Method: course
	Use: Returns the course designator to see if it should be
		printed
*/
char *task::course( void )
{
	return this->designator;
}

/*
	Class: task
	Method: from_string
	Use: Parses a csv string into data members
*/
void task::from_string( char *task_info )
{
	// Create srings for the numbered data types so we can parse
	// the input into seperate strings then convert to numbers
	char priority_string[gen::STRING_SIZE], date[gen::STRING_SIZE],
		month[3], day[3], year[5];
	// The string should be in csv format so we just parse it in order
	gen::split_line( task_info, this->designator, task_info, ',' );
	gen::toupper( this->designator );
	gen::split_line( task_info, this->name, task_info, ',' );
	gen::split_line( task_info, this->prep, task_info, ',' );
	gen::split_line( task_info, this->info, task_info, ',' );
	gen::split_line( task_info, date, priority_string, ',' );
	// We need to seperate the date into seperate day, month, year values
	gen::split_line( date, month, date, '/' );
	gen::split_line( date, day, year, '/' );
	// Convert the strings for day, month, year to int values
	this->date.day = std::atoi( day );
	this->date.month = std::atoi( month );
	this->date.year = std::atoi( year );
	// Convert the piority to an int and make sure its positive
	this->priority = std::atoi( priority_string );
	if ( this->priority < 0 )
	{
		this->priority *= -1;
	}
}


/*
	Class: task
	Method: prompt
	Use: Propmts user for the values of data members
*/
void task::prompt( void )
{
	// Four strings are needed to parse the date into
	// the day, month, and year. Also one to take the
	// whole line in
	char date[gen::STRING_SIZE], month[3], day[3], year[5];
	// Ask the user for their task information
	// Remove any commas so it doesn't mess up csv's
	gen::get_line( "What's the course designator(CS162)?\n# ", this->designator, gen::STRING_SIZE );
	gen::remove_char( this->designator, ',' );
	gen::toupper( this->designator );
	gen::get_line( "What's the tasks name?\n# ", this->name, gen::STRING_SIZE );
	gen::remove_char( this->name, ',' );
	gen::get_line( "What do you do to prepare for this?\n# ", this->prep, gen::STRING_SIZE );
	gen::remove_char( this->prep, ',' );
	gen::get_line( "What other information is associated with this task?\n# ", this->info, gen::STRING_SIZE );
	gen::remove_char( this->info, ',' );
	// Parse the date
	gen::get_line( "What date should this task be completed on? (mm/dd/yyyy) \n# ", date, gen::STRING_SIZE );
	gen::remove_char( date, ',' );
	gen::split_line( date, month, date, '/' );
	gen::split_line( date, day, year, '/' );
	// Convert the strings for day, month, year to int values
	this->date.day = std::atoi( day );
	this->date.month = std::atoi( month );
	this->date.year = std::atoi( year );
	// Get the priority and make sure its positive
	std::cout << "What is the priority of this task on a scale of 1-10?\n# ";
	std::cin >> this->priority;
	if ( this->priority < 0 )
	{
		this->priority *= -1;
	}
}


/*
	Class: task
	Method: print
	Use: Creates a string of the class in json format
		because its easily readable this way
*/
char *task::print( void )
{
	// Make the as_string array only about as long as it needs to be
	unsigned int all_lengths = strlen( this->designator ) + strlen( this->name ) + strlen( this->prep ) + strlen( this->info ) + gen::STRING_SIZE;
	// Make a pointer and assign it to an array of proper size so it
	// can be referenced outside this function
	char *as_string = new char[all_lengths];
	// Format the string, jsons are very readable
	sprintf( as_string, "{\n\t\"Course\": \"%s\",\n\t\"Name\": \"%s\",\n\t\"Preperation\": \"%s\",\n\t\"Info\": \"%s\",\n\t\"Date\": \"%d/%d/%d\",\n\t\"Priority\": %d\n}\n", this->designator, this->name, this->prep, this->info, this->date.month, this->date.day, this->date.year, this->priority );
	return as_string;
}


/*
	Class: task
	Method: save
	Use: Creates a string of the class in csv format
*/
char *task::save( void )
{
	// Make the as_string array only about as long as it needs to be
	unsigned int all_lengths = strlen( this->designator ) + strlen( this->name ) + strlen( this->prep ) + strlen( this->info ) + gen::STRING_SIZE;
	// Make a pointer and assign it to an array of proper size so it
	// can be referenced outside this function
	char *as_string = new char[all_lengths];
	// Format the string, csv is great for parseing in
	sprintf( as_string, "%s,%s,%s,%s,%d/%d/%d,%d\n", this->designator, this->name, this->prep, this->info, this->date.month, this->date.day, this->date.year, this->priority );
	return as_string;
}
