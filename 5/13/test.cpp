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



struct ride
{
	char * name;
	int wait;
	connection ** connections;
	int num_connections;
};



void connect( tree < ride * > & all, graph< void( ride *, char * ) > & connector )
{
	for ( int i = 0; i < all.size(); ++i )
	{
		for ( int j = 0; j < all[ i ]->num_connections; ++j )
		{
			connector.insert_edge( all[ i ]->name, all[ i ]->connections[ j ]->to, all[ i ]->connections[ j ]->name );
		}
	}
}



void delete_ride( ride * curr_ride )
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



void display_ride( ride * curr_ride )
{
	std::cout << curr_ride->name << ":\tWait: " << curr_ride->wait << " minutes";
	for ( int i = 0; i < curr_ride->num_connections; ++i )
	{
		std::cout << "\n" << curr_ride->connections[ i ]->name << "\t->\t" << curr_ride->connections[ i ]->to;
	}
	std::cout << '\n';
}



ride * parse( char * line )
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



int load( char * file_name, graph< void( ride *, char * ) > & connector, tree< ride * > & all )
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



void init( char * file_name, graph< void( ride *, char * ) > & connector, tree< ride * > & all )
{
	load( file_name, connector, all );
	connect( all, connector );
}


void display_all( graph< void( ride *, char * ) > & connector )
{
	std::cout << "All rides loaded:\n";
	gen::line('-');
	connector.display_all();
	gen::line('-');
}



void adjacent( graph< void( ride *, char * ) > & connector, tree< ride * > & all )
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



void display_path( char * from, char * to, graph< void( ride *, char * ) > & connector )
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



void destroy( tree< ride * > & all )
{
	for (int i = 0; i < all.size(); ++i)
	{
		delete_ride( all[ i ] );
	}
}



int main(int argc, char *argv[])
{
	if ( argc < 2 )
	{
		std::cout << "Usage " << argv[ 0 ] << " rides.csv\n";
		return 0;
	}
	tree< ride * > all;
	graph< void( ride *, char * ) > connector;
	init( argv[ 1 ], connector, all );
	display_all( connector );
	adjacent( connector, all );
	if ( argc == 4 )
	{
		display_path( argv[ 2 ], argv[ 3 ], connector );
	}
	destroy( all );
	return 0;
}


