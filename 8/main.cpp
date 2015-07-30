/*
	Author: John Andersen
	Date: 11/8/2014
	Description: Program to manage students courses and tasks
	Algoritham: This program will ask the user their name
		It will then attempt to load any existing courses
			and tasks from csvs into lists in memory
		It will prompt the user on what they would like to do
		It can list all the courses or tasks
		It can add new courses or tasks
		It will save the courses and tasks
		It will ask to save before exit
*/
#include <iostream>


// For all the general string minipulations and such
#ifndef GENERAL_INCLUDED
	#include "general.h"
#endif
// For the student class
#include "student.h"


int main(int argc, char const *argv[])
{
	// Create the student
	student current_student;
	// Read in the students name
	current_student.read_name();
	// Attempt to load any of their previous
	// data
	current_student.load();
	// Propmt them for input untill they say exit
	while ( current_student.handle_input() )
	{
		// Loop while input is not "exit"
	}
	// Ask the user if they want to save
	// This prevents them from forgeting to save
	std::cout << "Do you want to save? ";
	if ( gen::confirm() )
	{
		// Check if we could save or not
		if ( current_student.save() )
		{
			std::cout << "Saved\n";
		}
		else
		{
			std::cout << "Failed to save\n";
		}
	}
	return 0;
}


