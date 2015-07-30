/*
	Author: John Andersen
	Date: 11/8/2014
	Description: user class methods
*/


// For the user class
#include "user.h"



/*
	Class: user
	Method: constructor
	Use: Sets the name of the save file so the user
		doesn't have to.
*/
user::user()
{
	strcpy( this->file_name, "weather.csv" );
}


/*
	Class: user
	Method: save
	Use: Calls the save method of the weather class
		telling it to save to file_name.
*/
bool user::save( void )
{
	return this->weather_data.save( this->file_name );
}


/*
	Class: user
	Method: load
	Use: Calls the load method of the weather class
		telling it to load from file_name.
*/
bool user::load( void )
{
	return this->weather_data.load( this->file_name );
}


/*
	Class: user
	Method: handle_input
	Use: Prompts the user for what they want to do.
		Calls the appropriate method.
		Returns false if the user wants to exit.
*/
bool user::handle_input( void )
{
	// Hold the input of the user
	char user_input[gen::STRING_SIZE],
		action[gen::STRING_SIZE],
		source[gen::STRING_SIZE] = "";
	// Ask the user what they would like to do
	gen::get_line("Would you like to add, list (source), or save your forecasts? (\"exit\" to exit)# ", user_input, gen::STRING_SIZE);
	gen::split_line( user_input, action, source, ' ' );
	// Return false if they want to exit
	if ( strcmp( action, "exit" ) == 0 )
	{
		return false;
	}
	// If they want to save attempt to save
	else if ( strcmp( action, "save" ) == 0 )
	{
		if ( !this->save() )
		{
			std::cout << "Failed to save\n";
		}
	}
	// If they want to list then list
	else if ( strcmp( action, "list" ) == 0 )
	{
		this->weather_data.list( source );
	}
	// If they want to add then add a forecast
	else if ( strcmp( action, "add" ) == 0 )
	{
		this->weather_data.add();
	}
	// If they want to remove then remove a forecast
	else if ( strcmp( action, "remove" ) == 0 )
	{
		this->weather_data.remove();
	}
	// As long as they don't want to exit return true
	return true;
}
