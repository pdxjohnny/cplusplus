/*
	Author: John Andersen
	Date: 11/8/2014
	Description: Task class definition
*/

#ifndef GENERAL_INCLUDED
	#include "general.h"
#endif
#include <cstdio>


/*
	Struct: date_object
	Use: Holds the day, month, and year
*/
struct date_object
{
	unsigned int day;
	unsigned int month;
	unsigned int year;
};


/*
	Class: task
	Use: Holds a task and the course is it assinged to
*/
class task
{
public:
	// Returns the course designator
	char *course( void );
	// Parses a csv string into data members
	void from_string( char *task_info );
	// Propmts user for the values of data members
	void prompt( void );
	// Creates a string of the class in json format
	char *print( void );
	// Creates a string of the class in csv format
	char *save( void );
private:
	// The name of the task
	char name[gen::STRING_SIZE];
	// The course designator associated with the task
	char designator[gen::STRING_SIZE];
	// What ever is done to prepare for the task
	char prep[gen::STRING_SIZE];
	// Any other information associated with the task
	char info[gen::STRING_SIZE];
	// The date to assotciate with the task
	date_object date;
	// The priority level of the task
	unsigned int priority;
};
