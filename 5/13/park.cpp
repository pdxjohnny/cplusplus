/*
	Author: John Andersen
	Date: 03/19/2015
	Class: CS 163, Portland State University
	Assignment: Homework 5
	Description: Class to find a paths between rides
		in a theme park methods
*/



#include "park.h"



/*
	Class: park
	Method: park
	Use: Loads the file
	Input: File name
	Output: None
*/
park::park( char * file_name )
{
	init( file_name );
}



/*
	Class: park
	Method: park
	Use: Deallocates all the rides
	Input: None
	Output: None
*/
park::~park( void )
{
	destroy();
}



/*
	Class: park
	Method: connect
	Use: Inserts edges in the graph
	Input: Uses the all tree of rides
	Output: None
*/
void park::connect()
{
	for ( int i = 0; i < all.size(); ++i )
	{
		for ( int j = 0; j < all[ i ]->num_connections; ++j )
		{
			connector.insert_edge( all[ i ]->name, all[ i ]->connections[ j ]->to, all[ i ]->connections[ j ]->name );
		}
	}
}



/*
	Class: park
	Method: delete_ride
	Use: Deallocates a ride and its data
	Input: The pointer to the ride
	Output: None
*/
void park::delete_ride( ride * curr_ride )
{
	delete [] curr_ride->name;
	for ( int i = 0; i < curr_ride->num_connections; ++i )
	{
		delete [] curr_ride->connections[ i ]->to;
		delete [] curr_ride->connections[ i ]->name;
		delete curr_ride->connections[ i ];
	}
	delete [] curr_ride->connections;
	delete curr_ride;
}



/*
	Class: park
	Method: display_ride
	Use: Prints a ride to the screen
	Input: Pointer to the ride
	Output: Ride data to screen
*/
void park::display_ride( ride * curr_ride )
{
	std::cout << curr_ride->name << ":\tWait: " << curr_ride->wait << " minutes";
	for ( int i = 0; i < curr_ride->num_connections; ++i )
	{
		std::cout << "\n" << curr_ride->connections[ i ]->name << "\t->\t" << curr_ride->connections[ i ]->to;
	}
	std::cout << '\n';
}



/*
	Class: park
	Method: parse
	Use: Loads a ride form the csv line
	Input: Line in csv format
	Output: Populated ride
*/
ride * park::parse( char * line )
{
	ride * ride_loaded = new ride;
	int value_size = gen::STRING_SIZE * 2;
	char value [ value_size ];
	char temp [ value_size ];
	connection * conn;
	char * ride_value = NULL;
	int values = gen::count( line, delim ) + 1;
	ride_loaded->num_connections = values - 2;
	ride_loaded->connections = new connection * [ ride_loaded->num_connections ];
	for ( int i = 0; i < values; ++i )
	{
		gen::split_line( line, value, line, delim );
		ride_value = new char [ strlen( value ) + 1 ];
		strcpy( ride_value, value );
		if ( i == values - 1 )
		{
			ride_value[ strlen( ride_value ) - 1 ] = '\0';
		}
		switch ( i )
		{
			case 0:
				ride_loaded->name = ride_value;
				break;
			case 1:
				ride_loaded->wait = atoi( ride_value );
				delete [] ride_value;
				break;
			default:
				conn = new connection;
				gen::split_line( ride_value, temp, ride_value, '-' );
				conn->to = new char [ strlen( temp ) + 1 ];
				conn->name = new char [ strlen( ride_value ) + 1 ];
				strcpy( conn->to, temp );
				strcpy( conn->name, ride_value );
				ride_loaded->connections[ i - 2 ] = conn;
				delete [] ride_value;
				break;
		}
		gen::strclr( value );
	}
	return ride_loaded;
}



/*
	Class: park
	Method: load
	Use: Loads and parses all rides into the all tree of rides
	Input: File name to load
	Output: Number of rides loaded
*/
int park::load( char * file_name )
{
	int num_loaded = 0;
	std::ifstream file;
	file.open( file_name );
	if ( file.is_open() )
	{
		bool headers = true;
		int curr_size = gen::STRING_SIZE * 2;
		char curr_line [ curr_size ];
		ride * curr_ride;
		while ( !file.eof() )
		{
			// Get a line and store it in the curr_line array
			file.get( curr_line, curr_size, '\n' );
			// If there is data on the line
			if ( !headers && strlen( curr_line ) > 2 )
			{
				curr_ride = parse( curr_line );
				++num_loaded;
				all[ curr_ride->name ] = curr_ride;
				// display_ride( curr_ride );
				connector.insert_vertex( curr_ride->name, curr_ride );
			}
			headers = false;
			// Read in and ignore the newline
			file.ignore( curr_size, '\n' );
		}
		file.close();
	}
	return num_loaded;
}



/*
	Class: park
	Method: init
	Use: Loads and connects rides
	Input: File name to load
	Output: None
*/
void park::init( char * file_name )
{
	load( file_name );
	connect(  );
}



/*
	Class: park
	Method: display_all
	Use: Displays all the loaded rides
	Input: None
	Output: To screen all the ride names
*/
void park::display_all(  )
{
	std::cout << "All rides loaded:\n";
	gen::line('-');
	connector.display_all();
	gen::line('-');
}



/*
	Class: park
	Method: adjacent
	Use: Displays all the rides and their adjacent rides
	Input: None
	Output: None
*/
void park::adjacent( )
{
	for (int i = 0; i < all.size(); ++i)
	{
		gen::line('-');
		std::cout << "Adjacent for ";
		display_ride( all[ i ] );
		gen::line('-');
		std::cout << '\n';
	}
}



/*
	Class: park
	Method: display_path
	Use: Finds a path from one ride to another and displays it
	Input: Start and end ride names
	Output: To screen the path
*/
void park::display_path( char * from, char * to )
{
	std::cout << "From " << from << " to " << to << '\n';
	int length = connector.path_length( from, to );
	if ( !length )
		std::cout << "Can't find path\n";
	else
	{
		ride ** path = connector.path( from, to );
		std::cout << path[ 0 ]->name;
		for ( int i = 1; i < length; ++i )
		{
			std::cout << " -> " << path[ i ]->name;
		}
		std::cout << "\n";
		delete [] path;
	}
}



/*
	Class: park
	Method: destroy
	Use: Deallocates all rides and data
	Input: None
	Output: None
*/
void park::destroy(  )
{
	for (int i = 0; i < all.size(); ++i)
	{
		delete_ride( all[ i ] );
	}
}


