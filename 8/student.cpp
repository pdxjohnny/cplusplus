/*
	Author: John Andersen
	Date: 11/8/2014
	Description: Student class methods
*/


// For the student class
#include "student.h"


/*
	Class: student
	Method: add_course
	Use: Prompts the user for a course.
		Returns the index of the added course.
*/
unsigned int student::add_course( void )
{
	// Allocate memory for and create a pointer to the new course
	course *course_to_add=(course *) malloc(sizeof(course));
	// Populate the course values fromt the string
	course_to_add->prompt();
	// Insert the course into the list of courses
	this->courses.insert( course_to_add );
	// Reteurn the index of the last element in the courses list
	return this->courses.size()-1;
}


/*
	Class: student
	Method: add_task
	Use: Prompts the user for a task.
		Returns the index of the added task.
*/
unsigned int student::add_task( void )
{
	// Allocate memory for and create a pointer to the new task
	task *task_to_add=(task *) malloc(sizeof(task));
	// Populate the task values fromt the string
	task_to_add->prompt();
	// Insert the task into the list of tasks
	this->tasks.insert( task_to_add );
	// Reteurn the index of the last element in the tasks list
	return this->tasks.size()-1;
}


/*
	Class: student
	Method: number_of_courses
	Use: Returns the number of elements in the courses list
*/
unsigned int student::number_of_courses( void )
{
	return this->courses.size();
}


/*
	Class: student
	Method: number_of_tasks
	Use: Returns the number of elements in the tasks list
*/
unsigned int student::number_of_tasks( void )
{
	return this->tasks.size();
}


/*
	Class: student
	Method: list
	Use: Lists all the courses for the student
*/
void student::list_courses( void )
{
	std::cout << "You have " << this->courses.size() << " total.\n";
	std::cout << "CRN\t\t|Course Designator\t|Section\n";
	for ( unsigned int i = 0; i < this->courses.size(); ++i )
	{
		// This returns a new char array
		char *line = this->courses[i]->print();
		std::cout << line;
		// We created a new char arry so we have to delete it
		delete line;
	}
	return;
}


/*
	Class: student
	Method: list
	Use: Lists all the tasks for the student
		Can also list by course
*/
void student::list_tasks( const char *designator )
{
	std::cout << "You have " << this->tasks.size() << " total.\n";
	for ( unsigned int i = 0; i < this->tasks.size(); ++i )
	{
		// This returns a new char array
		char *line = this->tasks[i]->print();
		// Only print if there is no designator or
		// the designator matches
		if ( strcmp( designator, "" ) == 0 || strcmp( designator, this->tasks[i]->course() ) == 0 )
		{
			std::cout << line;
		}
		// We created a new char arry so we have to delete it
		delete line;
	}
	return;
}


/*
	Class: student
	Method: read_name
	Use: Gets the students first and last name
*/
void student::read_name( void )
{
	// String to hold the full name
	char fullname[gen::STRING_SIZE];
	gen::get_line( "What's your first and last name?\n# ", fullname, gen::STRING_SIZE );
	gen::remove_multi_whitespace(fullname);
	gen::capitalize( fullname );
	// Parse into the first and last names
	gen::split_line( fullname, this->first_name, this->last_name, ' ' );
	return;
}


/*
	Class: student
	Method: make_file_name
	Use: Cats the ending onto the fullname
*/
void student::make_file_name( char *file_name, const char *file_ending )
{
	// Clear the string
	gen::strclr( file_name );
	// Make the file_name the first name
	strcpy( file_name, this->first_name );
	// Add the last name
	strcat( file_name, this->last_name );
	// Remove whitespace just in case
	gen::remove_whitespace( file_name );
	// Add the file ending
	strcat( file_name, file_ending );
	return;
}


/*
	Class: student
	Method: save
	Use: Saves the courses and tasks in seperate csv files
		It uses the name of the student to name the files
*/
bool student::save( void )
{
	// The output file object
	std::ofstream save_file;
	// The file endings
	const char *file_ending[] = { "Courses.csv", "Tasks.csv" };
	// The array for the file name
	char file_name[ strlen(this->first_name) + strlen(this->last_name)
		+ strlen("Courses.csv") + 1 ];
	// The return code, false if it can't open a file
	bool return_code = false;
	// Loop twice to use both the file endings
	for ( unsigned int i = 0; i < 2; ++i )
	{
		// Make the file name
		this->make_file_name( file_name, file_ending[i] );
		// Open the file
		save_file.open( file_name );
		// If the file is open then write
		if ( save_file.is_open() )
		{
			// If this is the course file
			if ( strcmp( file_ending[i], "Courses.csv" ) == 0 )
			{
				// Then loop through the courses list
				save_file << "CRN,Course Designator,Section\n";
				for ( unsigned int j = 0; j < this->courses.size(); ++j )
				{
					// Save returns a new char array
					char *line = this->courses[j]->save();
					save_file << line;
					// Delete the new array that was malloc'd
					delete line;
				}
			}
			// Else this must be the tasks file
			else
			{
				// Then loop through the tasks list
				save_file << "Course,Name,Preperation,Info,Date,Priority\n";
				for ( unsigned int j = 0; j < this->tasks.size(); ++j )
				{
					// Save returns a new char array
					char *line = this->tasks[j]->save();
					save_file << line;
					// Delete the new array that was malloc'd
					delete line;
				}
			}
			// Echo where we saved to
			std::cout << "Saved to " << file_name << '\n';
			// A file was opened set the return code to true
			return_code = true;
		}
		// Close the currently open file
		save_file.close();
	}
	// Return whether a file was opened or not
	return return_code;
}


/*
	Class: student
	Method: load
	Use: Loads the courses and tasks from seperate csv files
		It uses the name of the student to know which files
*/
bool student::load( void )
{
	// A file input object
	std::ifstream load_file;
	// The file endings
	const char *file_ending[] = { "Courses.csv", "Tasks.csv" };
	// The array for the file name
	char file_name[ strlen(this->first_name) + strlen(this->last_name)
		+ strlen("Courses.csv") + 1 ];
	// The size of the current_line array which is read in
	int current_line_size = gen::STRING_SIZE * 2;
	// The current_line array for reading in the file
	char current_line[current_line_size];
	// The return code, false if it can't open a file
	bool return_code = false;
	// Loop twice to use both the file endings
	for ( unsigned int i = 0; i < 2; ++i )
	{
		// Make the file name
		this->make_file_name( file_name, file_ending[i] );
		// Open the file
		load_file.open( file_name );
		// If the file is open then read
		if ( load_file.is_open() )
		{
			// Get the first line, it contains the column headers
			// Get a line and store it in the current_line array
			load_file.get( current_line, current_line_size, '\n' );
			// Read in and ignore the newline
			load_file.ignore( current_line_size, '\n' );
			// Then loop until the end of file
			while ( !load_file.eof() )
			{
				// Get a line and store it in the current_line array
				load_file.get( current_line, current_line_size, '\n' );
				// Read in and ignore the newline
				load_file.ignore( current_line_size, '\n' );
				// If the string length of the line is less than 1
				// then it is the last line so break. We don't want
				// to make an empty course or task
				if ( strlen( current_line ) < 1 )
				{
					break;
				}
				// If this is the course file
				else if ( strcmp( file_ending[i], "Courses.csv" ) == 0 )
				{
					// Create a new course
					course *new_course = new course;
					// Populate the members from the line
					new_course->from_string( current_line );
					// Insert the course in the list
					this->courses.insert( new_course );
				}
				// Else this must be the tasks file
				else
				{
					// Create a new task
					task *new_task = new task;
					// Populate the members from the line
					new_task->from_string( current_line );
					// Insert the task in the list
					this->tasks.insert( new_task );
				}
			}
			// A file was opened to return true
			return_code = true;
		}
		// Close the currently open file
		load_file.close();
	}
	// Return whether a file was opened
	return return_code;
}


/*
	Class: student
	Method: handle_input
	Use: Prompts the user for what they want to do.
		Calls the appropriate method.
		Returns false if the user wants to exit.
*/
bool student::handle_input( void )
{
	// Hold the input of the user, and if it is for coursees or tasks
	char user_input[gen::STRING_SIZE],
		arg_one[gen::STRING_SIZE],
		arg_two[gen::STRING_SIZE],
		designator[gen::STRING_SIZE];
	// Ask the user what they would like to do
	gen::get_line("What would you like to do to your courses and tasks?\nadd course/task, list courses/tasks (class designator), save, exit\n# ", user_input, gen::STRING_SIZE);
	// Return false if they want to exit
	if ( strcmp( user_input, "exit" ) == 0 )
	{
		return false;
	}
	// If they want to save attempt to save
	else if ( strcmp( user_input, "save" ) == 0 )
	{
		if (  this->save() )
		{
			std::cout << "Saved\n";
		}
		else
		{
			std::cout << "Failed to save\n";
		}
		// Return because we already know they
		// didn't want to list or add
		return true;
	}
	// If it wan't exit or save then its list or add
	// Split the string into three arguments
	// The first is the action add / list
	// The second is the type course / task
	// The third is a filter my the course designator
	gen::split_line( user_input, arg_one, user_input, ' ' );
	gen::split_line( user_input, arg_two, designator, ' ' );
	gen::toupper( designator );
	// If they want to list check what they want to list
	if ( strcmp( arg_one, "list" ) == 0 )
	{
		if ( strcmp( arg_two, "courses" ) == 0 )
		{
			this->list_courses();
		}
		else if ( strcmp( arg_two, "tasks" ) == 0 )
		{
			this->list_tasks( designator );
		}
	}
	// If they want to add check what they want to add
	else if ( strcmp( arg_one, "add" ) == 0 )
	{
		if ( strcmp( arg_two, "course" ) == 0 )
		{
			this->add_course();
		}
		else if ( strcmp( arg_two, "task" ) == 0 )
		{
			this->add_task();
		}
	}
	// As long as they don't want to exit return true
	return true;
}
