/*
	Author: John Andersen
	Date: 01/15/2015
	Description: Program to manage heros and powers
	Algoritham: This program will attempt to load any 
			existing heros and powers from files
		It will prompt the user on what they would like to do
		It can list the heros or powers
		It can add new heros or powers
		It can edit existing heros or powers
		It can remove heros or powers
		It will save the heros or powers
*/
#include <iostream>

// For the user class
#include "user.h"


int main(int argc, char const *argv[])
{
	// Create the user
	user current_user;

	// Not enough arguments so display help
	if ( argc == 2 )
	{
		current_user.help();
	}
	else if ( argc > 2 )
	{
		// Pass the methods and 
		current_user.handle_input( argv[1], argv[2] );
	}
	// No arguments so ask for input
	else
	{
		// Propmt them for input untill they say exit
		while ( current_user.handle_input() )
		{
			// Loop while input is not "exit"
		}
	}

	return 0;
}


