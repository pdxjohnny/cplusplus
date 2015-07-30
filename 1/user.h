/*
	Author: John Andersen
	Date: 01/16/2014
	Description: user class
*/

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <cctype>
#include <cstdio>


// For all the general string minipulations and such
#include "gen.h"
// For dictionaries
#include "dict.h"
#include "dict_dict_array.h"
// For objects
#include "object.h"


/*
	Class: user
	Use: Stores all of the user data and methods to:
	 edit, get, modify, or combine them.
	 Also contains the handle_input method.
*/
class user : public object
{
public:
	user();
	// Saves the heros and powers to csvs
	bool save( void );
	// Loads the hweros and powers
	bool load( void );
	// Edits the hero power or creates a new one
	bool edit( char * );
	// Asks for what hero to edit
	bool edit_hero( void );
	// Edits the hero provided
	bool edit_hero( char * hero );
	// Asks for what power to edit
	bool edit_power( void );
	// Edits the pwoer provided
	bool edit_power( char * power );
	// The numer of heros with a power
	int heros_with_power( char * power_name );
	// Make suer powers are active and heros have powers
	bool link_hero_power( char * hero, char * power_name );
	// Remvoes powers and heros form each other
	bool unlink_hero_power( char * hero_name, char * power_name );
	// Prints all the powers of heros
	bool list( char * );
	// Finds all the powers given the situation
	bool find( char * );
	// Removes the power or hero passed in
	bool remove( char * );
	// Displays the help text
	void help( void );
	// The user control for the user class
	bool handle_input( void );
	// Calls the appropriate method
	bool handle_input( const char * action, const char * args );
private:
	// Store all the heros in a dict_dict_arrayionary
	dict_dict_array<object> heros;
	// Store all the powers in a dict_dict_arrayionary
	dict_dict_array<object> powers;
	// Deliminate with this character
	char delim;
};
