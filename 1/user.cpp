/*
	Author: John Andersen
	Date: 01/15/2015
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
	this->delim = ';';
	this->set( "hero_file", "heros.csv" );
	this->set( "hero_keys", "description" );
	this->set( "power_file", "powers.csv" );
	this->set( "power_keys", "applicable situation,number of heros with this power" );
	this->load();
}



/*
	Class: user
	Method: save
	Use: Calls the save method of the classes in the backgorund
*/
bool user::save( void )
{	
	// It took to long to save so I made it fork
	if ( gen::thread() )
	{
		// Save the file and kill the thread
		this->heros.save_file( this->strings[ "hero_file" ], this->delim );
		this->powers.save_file( this->strings[ "power_file" ], this->delim );
		exit(0);
	}
	else
	{
		// If the child saved then return true
		return true;
	}
	return false;
}



/*
	Class: user
	Method: load
	Use: Calls the load methods and then
		gets rid of the objects that were
		created that we didn't need
*/
bool user::load( void )
{
	// These return the number of lines loaded
	// therefor true if anything loaded
	int lines_loaded = this->heros.load_file( this->strings[ "hero_file" ], this->delim ) +
		this->powers.load_file( this->strings[ "power_file" ], this->delim );
	char ** hero_names = this->heros.keys();
	for ( unsigned int i = 0; i < this->heros.size(); ++i )
	{
		char ** heros_powers = this->heros[ i ].keys();
		for ( unsigned int j = 0; j < this->heros[ i ].size(); ++j )
		{
			if ( 0 != strcmp( heros_powers[ j ], "description" ) )
			{
				this->link_hero_power( hero_names[ i ], heros_powers[ j ] );
			}
			delete [] heros_powers[ j ];
		}
		delete [] heros_powers;
		delete [] hero_names[ i ];
	}
	delete [] hero_names;
	char ** power_names = this->powers.keys();
	for ( unsigned int i = 0; i < this->powers.size(); ++i )
	{
		char ** heros_powers = this->powers[ i ].keys();
		for ( unsigned int j = 0; j < this->powers[ i ].size(); ++j )
		{
			if ( 0 != strcmp( heros_powers[ j ], "situation" ) &&
				0 != strcmp( heros_powers[ j ], "Heros with this power" ) )
			{
				// std::cout << "Linking hero " << heros_powers[ j ] << " to " << power_names[ i ] << '\n';
				this->link_hero_power( heros_powers[ j ], power_names[ i ] );
			}
			delete [] heros_powers[ j ];
		}
		delete [] heros_powers;
		delete [] power_names[ i ];
	}
	delete [] power_names;
	return lines_loaded;
}



/*
	Class: user
	Method: edit
	Use: Edits the appropriate object
*/
bool user::edit( char * hero_power )
{
	if ( 0 == strcmp( hero_power, "hero" ) )
	{
		this->edit_hero();
	}
	else if ( 0 == strcmp( hero_power, "power" ) )
	{
		this->edit_power();
	}
	else if ( this->heros.contains( hero_power ) )
	{
		this->edit_hero( hero_power );
	}
	else if ( this->powers.contains( hero_power ) )
	{
		this->edit_power( hero_power );
	}
	else
	{
		std::cout << "Do you want to edit a hero or a power?\n";
	}
	return true;
}



/*
	Class: user
	Method: edit_hero
	Use: Asks for a heros name before editing
*/
bool user::edit_hero( void )
{
	char * user_input = new char [ gen::STRING_SIZE ];
	gen::get_line( "What is the hero's name? ", user_input, gen::STRING_SIZE );
	this->edit_hero( user_input );
	delete [] user_input;
	return true;
}



/*
	Class: user
	Method: edit_hero
	Use: Edits a hero given the name
*/
bool user::edit_hero( char * hero )
{
	char * user_input = new char [ gen::STRING_SIZE ];
	char * ask = new char [ gen::STRING_SIZE ];
	this->set( "hero", hero );
	if ( this->heros.contains( this->strings[ "hero" ] ) &&
		this->heros[ this->strings[ "hero" ] ].contains("description") )
	{
		this->heros[ this->strings[ "hero" ] ].print();
		do
		{
			gen::get_line( "Type description to change description or the name of the power you want to edit for this hero\n# ", user_input, gen::STRING_SIZE );
			this->set( "property", user_input );
			if ( 0 == strcmp( this->strings[ "property" ], "description" ) )
			{
				sprintf( ask, "What is %s's %s? ", this->strings[ "hero" ], this->strings[ "property" ] );
				gen::get_line( ask, user_input, gen::STRING_SIZE );
				this->heros[ this->strings[ "hero" ] ].set( this->strings[ "property" ], user_input );
			}
			else
			{
				std::cout << "Does " << this->strings[ "hero" ] << " have " << this->strings[ "property" ] << " as a power? ";
				if ( gen::confirm() )
				{
					this->link_hero_power( this->strings[ "hero" ], this->strings[ "property" ] );
				}
				else
				{
					this->unlink_hero_power( this->strings[ "hero" ], this->strings[ "property" ] );
				}
			}
			std::cout << "Continue editing?\n";
		}
		while( gen::confirm() );
	}
	else
	{
		gen::get_line( "How would you describe this hero? ", user_input, gen::STRING_SIZE );
		this->heros[ this->strings[ "hero" ] ].set( "description", user_input );
	}
	std::cout << this->strings[ "hero" ] << '\n';
	this->heros[ this->strings[ "hero" ] ].print();
	delete [] user_input;
	delete [] ask;
	return true;
}



/*
	Class: user
	Method: edit_power
	Use: Asks for a powers name before editing
*/
bool user::edit_power( void )
{
	char * user_input = new char [ gen::STRING_SIZE ];
	gen::get_line( "What is the power's name / type? ", user_input, gen::STRING_SIZE );
	this->edit_power( user_input );
	delete [] user_input;
	return true;
}



/*
	Class: user
	Method: edit_power
	Use: Edits a power given the name
*/
bool user::edit_power( char * power )
{
	char * user_input = new char [ gen::STRING_SIZE ];
	char * ask = new char [ gen::STRING_SIZE ];
	this->set( "power", power );
	if ( this->powers.contains( this->strings[ "power" ] ) &&
		this->powers[ this->strings[ "power" ] ].contains("situation") )
	{
		this->powers[ this->strings[ "power" ] ].print();
		do
		{
			gen::get_line( "Type situation to change situation or the name of the hero you want to edit for this power\n# ", user_input, gen::STRING_SIZE );
			this->set( "property", user_input );
			if ( 0 == strcmp( this->strings[ "property" ], "situation" ) )
			{
				sprintf( ask, "What is the best %s for %s? ", this->strings[ "property" ], this->strings[ "power" ] );
				gen::get_line( ask, user_input, gen::STRING_SIZE );
				this->powers[ this->strings[ "power" ] ].set( this->strings[ "property" ], user_input );
			}
			else
			{
				std::cout << "Does " << this->strings[ "property" ] << " have " << this->strings[ "power" ] << " as a power? ";
				if ( gen::confirm() )
				{
					this->link_hero_power( this->strings[ "property" ], this->strings[ "power" ] );
				}
				else
				{
					this->unlink_hero_power( this->strings[ "property" ], this->strings[ "power" ] );
				}
			}
			std::cout << "Continue editing?\n";
		}
		while( gen::confirm() );
	}
	else
	{
		gen::get_line( "In what situation is this power useful? ", user_input, gen::STRING_SIZE );
		this->powers[ this->strings[ "power" ] ].set( "situation", user_input );
	}
	std::cout << this->strings[ "power" ] << '\n';
	this->powers[ this->strings[ "power" ] ].print();
	delete [] user_input;
	delete [] ask;
	return true;
}




/*
	Class: user
	Method: heros_with_power
	Use: Finds number of heros with a power
*/
int user::heros_with_power( char * power_name )
{
	object * power = & this->powers[ power_name ];
	if ( power->contains( "Heros with this power" ) &&
		power->contains( "situation" ) )
	{
		return power->size() - 2;
	}
	else if ( power->contains( "Heros with this power" ) ||
		power->contains( "situation" ) )
	{
		return power->size() - 1;
	}
	else
	{
		return power->size();
	}
}


/*
	Class: user
	Method: link_hero_power
	Use: Creates the keys for each object
*/
bool user::link_hero_power( char * hero, char * power_name )
{
	object * power = & this->powers[ power_name ];
	this->heros[ hero ].set( power_name, "Active" );
	power->set( hero, "Has power" );
	power->set( "Heros with this power", this->heros_with_power( power_name ) );
	return true;
}



/*
	Class: user
	Method: unlink_hero_power
	Use: Remvoes the keys from each object
*/
bool user::unlink_hero_power( char * hero_name, char * power_name )
{
	object * power = & this->powers[ power_name ];
	object * hero = & this->heros[ hero_name ];
	hero->remove( power_name );
	power->remove( hero_name );
	power->set( "Heros with this power", this->heros_with_power( power_name ) );
	return true;
}



/*
	Class: user
	Method: list
	Use: Lists all of the heros or powers
*/
bool user::list( char * hero_power )
{
	char ** keys;
	gen::line('-');
	if ( 0 == strcmp( hero_power, "heros" ) )
	{
		keys = this->heros.keys();
		for ( unsigned int i = 0; i < this->heros.size(); ++i )
		{
			std::cout << '\n';
			std::cout << "\t" << color::lightblue << keys[ i ] << color::normal << "\n";
			delete [] keys[ i ];
			this->heros[ i ].print();
		}
		delete [] keys;
	}
	else if ( 0 == strcmp( hero_power, "powers" ) )
	{
		keys = this->powers.keys();
		for ( unsigned int i = 0; i < this->powers.size(); ++i )
		{
			std::cout << '\n';
			std::cout << "\t" << color::lightblue << keys[ i ] << color::normal << "\n";
			delete [] keys[ i ];
			this->powers[ i ].print();
		}
		delete [] keys;
	}
	std::cout << '\n';
	gen::line('-');
	return true;
}



/*
	Class: user
	Method: find
	Use: finds all powers and heros for a situation
*/
bool user::find( char * situation )
{
	gen::line('-');
	char ** power_name = this->powers.keys();
	for ( unsigned int i = 0; i < this->powers.size(); ++i )
	{
		if ( this->powers[ i ].contains( "situation" ) )
		{
			char * curr_situation = new char [ this->powers[ i ].value_length( "situation" ) +1 ];
			this->powers[ i ].value_string( curr_situation, "situation" );
			if ( 0 == strcmp( situation, curr_situation ) )
			{
				std::cout << '\n';
				std::cout << "\t" << color::lightblue << power_name[ i ] << color::normal << "\n";
				this->powers[ i ].print();
			}
		}
		delete [] power_name[ i ];
	}
	delete [] power_name;
	std::cout << '\n';
	gen::line('-');
	return true;
}



/*
	Class: user
	Method: remove
	Use: Removes a hero or power
*/
bool user::remove( char * hero_power )
{
	if ( this->heros.contains( hero_power ) )
	{
		object * hero = & this->heros[ hero_power ];
		char ** power = hero->keys();
		for ( unsigned int i = 0; i < hero->size(); ++i )
		{
			if ( 0 != strcmp( "description", power[ i ] ) )
			{
				this->unlink_hero_power( hero_power, power[ i ] );
			}
			delete [] power[ i ];
		}
		delete [] power;
		hero->print();
	}
	else if ( this->powers.contains( hero_power ) )
	{
		object * power = & this->powers[ hero_power ];
		char ** hero = power->keys();
		for ( unsigned int i = 0; i < power->size(); ++i )
		{
			if ( 0 != strcmp( "situation", hero[ i ] ) &&
				0 != strcmp( "Heros with this power", hero[ i ] ) )
			{
				this->unlink_hero_power( hero[ i ], hero_power );
			}
			delete [] hero[ i ];
		}
		delete [] hero;
		power->print();
	}
	this->heros.remove( hero_power );
	this->powers.remove( hero_power );
	return true;
}



/*
	Class: user
	Method: help
	Use: Displays some help information
*/
void user::help( void )
{
	std::cout << "Usage:\n";
	std::cout << "\thelp: displays this message\n";
	std::cout << "\tlist: lists the heros or the powers\n";
	std::cout << "\tedit: lets you add a new hero or power or edit an existing one\n";
	std::cout << "\tremove: removes a hero or power\n";
	std::cout << "\tfind: look up powers that are good for what ever situation you supply\n";
}



/*
	Class: user
	Method: handle_input
	Use: Prompts the user for what they want to do.
		Returns false if the user wants to exit.
*/
bool user::handle_input( void )
{
	bool return_value = true;
	// Hold the input of the user
	char * user_input = new char [ gen::STRING_SIZE ],
		* action = new char [ gen::STRING_SIZE ],
		* args = new char [ gen::STRING_SIZE ];
	// Ask the user what they would like to do
	gen::get_line("Would you like to edit (hero or power), list (heros or powers), find powers and heros for a (situation),\n, or a remove (hero or power)? (\"exit\" to exit)# ", user_input, gen::STRING_SIZE);
	// Action is the first part of the string
	gen::split_line( user_input, action, args, ' ' );
	// Returns continue or exit calls the appropriate methods
	return_value = this->handle_input( action, args );
	// Delete the allocated strings
	delete [] user_input;
	delete [] action;
	delete [] args;
	// As long as they don't want to exit return true
	return return_value;
}



/*
	Class: user
	Method: handle_input
	Use: Given action and extra args.
		Calls the appropriate method.
		Returns false if action is "exit".
*/
bool user::handle_input( const char * action, const char * args )
{
	char * local_action = new char [ strlen( action ) + 1 ];
	char * local_args = new char [ strlen( args ) + 1 ];
	strcpy( local_action, action );
	strcpy( local_args, args );
	// False if exit
	bool return_value = true;
	// Return false if they want to exit
	if ( strcmp( local_action, "exit" ) == 0 )
	{
		return_value = false;
	}
	// If they want to list then list
	else if ( strcmp( local_action, "list" ) == 0 )
	{
		this->list( local_args );
	}
	// If they want to edit then edit
	else if ( strcmp( local_action, "edit" ) == 0 )
	{
		this->edit( local_args );
	}
	// If they want to remove then remove
	else if ( strcmp( local_action, "remove" ) == 0 )
	{
		this->remove( local_args );
	}
	// If they want to find then find
	else if ( strcmp( local_action, "find" ) == 0 )
	{
		this->find( local_args );
	}
	// In case I make no sense
	else if ( strcmp( local_action, "help" ) == 0 )
	{
		this->help();
	}
	else
	{
		std::cout << local_action << '\t' << local_args << '\n';
	}
	this->save();
	delete [] local_action;
	delete [] local_args;
	// As long as they don't want to exit return true
	return return_value;
}
