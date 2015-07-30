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



class park
{
	public:
		park( char * file_name );
		~park( void );
		void connect();
		void delete_ride( ride * curr_ride );
		void display_ride( ride * curr_ride );
		ride * parse( char * line );
		int load( char * file_name );
		void init( char * file_name );
		void display_all(  );
		void adjacent( );
		void display_path( char * from, char * to );
		void destroy(  );
	private:
		tree< ride * > all;
		graph< void( ride *, char * ) > connector;
};


