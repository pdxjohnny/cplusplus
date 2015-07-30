/*
	Author: John Andersen
	Date: 11/8/2014
	Description: Student class
*/

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cctype>

// For all the general string minipulations and such
#ifndef GENERAL_INCLUDED
	#include "general.h"
#endif
// For when a variably sized array is needed
#include "dlist.h"
// For the course class
#include "course.h"
// For the task class
#include "task.h"

/*
	Class: student
	Use: Stores all of the student data and methods to:
	 add, get, modify, or combine them.
	 Also contains the handle_input method.
*/
class student
{
public:
	// Methods for adding courses and tasks
	unsigned int add_course( void );
	unsigned int add_task( void );
	// Methods for outside to get number of tasks and courses
	unsigned int number_of_courses( void );
	unsigned int number_of_tasks( void );
	// Lists all of the courses or tasks
	void list_courses( void );
	void list_tasks( const char *designator );
	// Cats the ending onto the fullname
	void make_file_name( char *file_name, const char *file_ending );
	// Saves the courses and tasks to csvs
	bool save( void );
	bool load( void );
	// Gets the users first and last name
	void read_name( void );
	// The user control for the student class
	bool handle_input( void );
private:
	// Store the name of the student
	char first_name[gen::STRING_SIZE];
	char last_name[gen::STRING_SIZE];
	// So we know what courses are taken
	dlist<course> courses;
	// So we can keep track of tasks
	dlist<task> tasks;
};
