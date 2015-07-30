/*
	Author: John Andersen
	Date: 11/4/2014
	Description: Course class
*/

#include <cstdio>
#ifndef GENERAL_INCLUDED
	#include "general.h"
#endif

/*
	Class: course
	Use: Stores the information associated with a course
		Such as: CRN, designator, and section
*/
class course
{
public:
	// Parses a csv string into data members
	void from_string( char *course_info );
	// Propmts user for the values of data members
	void prompt( void );
	// Creates a string of the class in json format
	char *print( void );
	// Creates a string of the class in csv format
	char *save( void );
private:
	// Its a string because I've seen them with hyphens
	char CRN[gen::STRING_SIZE];
	// String for the designator ( CS162 )
	char designator[gen::STRING_SIZE];
	// Section should never be negative
	unsigned int section;
};
