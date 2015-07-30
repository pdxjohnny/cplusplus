#include "park.h"
#include <iostream>


int main(int argc, char *argv[])
{
	if ( argc < 2 )
	{
		std::cout << "Usage " << argv[ 0 ] << " rides.csv\n";
		return 0;
	}
	park disney( argv[ 1 ] );
	disney.display_all();
	disney.adjacent();
	if ( argc == 4 )
	{
		disney.display_path( argv[ 2 ], argv[ 3 ] );
	}
	return 0;
}

