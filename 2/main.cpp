/*
	Author: John Andersen
	Date: 02/04/2015
	Description: Program to create an equation
	Algoritham: This program will create an equation
		and calculate the result on request.
		It is used to test the stack, queue and
		calc ADT's.
*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

// For the gen class
#include "gen.h"
// For the calc class
#include "calc.h"


const unsigned int STRING_SIZE = 100;

/*
	Function: handle_input
	Use: Prompts the user for what they want to do.
		Calls the appropriate method.
		Returns false if the user wants to exit.
*/
bool handle_input( calc * my_calc )
{
	// Hold the input of the user
	char user_input[ STRING_SIZE ],
		action[ STRING_SIZE ],
		number[ STRING_SIZE ] = "";
	// Get what the user types in, hopefully they do it
	// in the format requested
	gen::get_line( "", user_input, STRING_SIZE );
	gen::split_line( user_input, action, number, ' ' );
	// Return false if they want to exit
	if ( strcmp( action, "exit" ) == 0 )
	{
		return false;
	}
	// If they want to remove then remove a forecast
	else if ( strcmp( action, "undo" ) == 0 )
	{
		if ( atoi( number ) > 0 )
			my_calc->undo( atoi( number ) );
		else
			my_calc->undo( 1 );
	}
	// View the equation and the commands
	else if ( strcmp( action, "view" ) == 0 )
	{
		my_calc->view_history();
	}
	// Clears the equation and history
	else if ( strcmp( action, "clear" ) == 0 )
	{
		my_calc->clear();
	}
	// Calculate the total
	else if ( strcmp( action, "calc" ) == 0 )
	{
		std::cout << "Total: " << my_calc->calculate() << '\n';
	}
	// Atempt to execute their command
	else
	{
		my_calc->exec( user_input );
	}
	// As long as they don't want to exit return true
	return true;
}



int main( int argc, char const *argv[] )
{
	// Create the calculator object
	calc * my_calc = new calc;

	std::cout << "( add, subtract, divide, multiply ) and number... or view, calc, clear, or exit\n";
	// Propmt them for input untill they say exit
	while ( handle_input( my_calc ) )
	{
		// Loop while input is not "exit"
	}

	// Delete the calculator
	delete my_calc;

	return 0;
}


