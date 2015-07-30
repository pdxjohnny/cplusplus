/*
	Author: John Andersen
	Date: 11/8/2014
	Description: user class
*/

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cctype>

// For all the general string minipulations and such
#ifndef GENERAL_INCLUDED
	#include "general.h"
#endif
// For the weather class
#include "weather.h"

/*
	Class: user
	Use: Stores all of the user data and methods to:
	 add, get, modify, or combine them.
	 Also contains the handle_input method.
*/
class user
{
public:
	user();
	// Saves the weathers and forecasts to csvs
	bool save( void );
	bool load( void );
	// The user control for the user class
	bool handle_input( void );
private:
	// Store the file_name of the weather data
	char file_name[gen::STRING_SIZE];
	// Store the weather class which holds forecasts
	weather weather_data;
};
