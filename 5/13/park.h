/*
	Author: John Andersen
	Date: 03/19/2015
	Class: CS 163, Portland State University
	Assignment: Homework 5
	Description: Class to find a paths between rides
		in a theme park
*/



#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>



#include "gen.h"
#include "graph.h"



const char delim = ',';



struct connection
{
	char * to;
	char * name;
};



/*
	Struct: ride
	Use: Ride in a theme park
*/
struct ride
{
	char * name;
	int wait;
	connection ** connections;
	int num_connections;
};



/*
	Class: park
	Use: Class to find a paths between rides
		in a theme park
*/
class park
{
	public:
		// Loads the file
		park( char * file_name );
		// Deallocates all the rides
		~park( void );
		// Inserts edges in the graph
		void connect( void );
		// Deallocates a ride and its data
		void delete_ride( ride * curr_ride );
		// Prints a ride to the screen
		void display_ride( ride * curr_ride );
		// Loads a ride form the csv line
		ride * parse( char * line );
		// Loads and parses all rides into the all tree of rides
		int load( char * file_name );
		// Loads and connects rides
		void init( char * file_name );
		// Displays all the loaded rides
		void display_all( void );
		// Displays all the rides and their adjacent rides
		void adjacent( void );
		// Finds a path from one ride to another and displays it
		void display_path( char * from, char * to );
		// Deallocates all rides and data
		void destroy( void );
	private:
		// All the rides loaded
		tree< ride * > all;
		// The graph of the rides to connect them
		graph< void( ride *, char * ) > connector;
};


