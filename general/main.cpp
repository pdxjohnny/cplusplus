/*
	Author: John Andersen
	Date: 11/8/2014
	Description: Program to manage forecasts
	Algoritham: This program will attempt to load any 
			existing forecasts from the weather.csv file
		It will prompt the user on what they would like to do
		It can list the forecasts
		It can add new forecasts
		It can remove forecasts
		It can save the forecasts
		It will ask to save before exit
*/
#include <iostream>


// For all the general string minipulations and such
#ifndef GENERAL_INCLUDED
	#include "general.h"
#endif
// For the user class
#include "user.h"


int main(int argc, char const *argv[])
{
	// Create the user
	user current_user;
	// Attempt to load any of the previous
	// data
	current_user.load();
	// Propmt them for input untill they say exit
	while ( current_user.handle_input() )
	{
		// Loop while input is not "exit"
	}
	// Ask the user if they want to save
	// This prevents them from forgeting to save
	std::cout << "Do you want to save? ";
	if ( gen::confirm() )
	{
		// Check if we could save or not
		if ( !current_user.save() )
		{
			std::cout << "Failed to save\n";
		}
	}
	return 0;
}


