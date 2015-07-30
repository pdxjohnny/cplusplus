#include "gen.h"
#include "list_el.h"
#include "dict_array.h"
#include "dict_dict_array.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char * argv[])
{
	// dict_dict_array<int> array;
	// dict_dict_array<char *> array;
	// for ( unsigned int i = 1; i < argc; ++i )
	// {
	// 	// array[ argv[i] ] = i;
	// 	array[ argv[i] ] = new char [ strlen( argv[i] ) + 2 ];
	// 	sprintf( array[ argv[i] ], "%s%c", argv[i], argv[i][0] + 1 );
	// 	// strcpy( array[ argv[i] ], argv[i] );
	// }
	// std::cout << "\nPrinting " << array.size() << '\n';
	// std::cout << color::blue;// << highlight::green;
	// array.print();
	// std::cout << highlight::normal;
	// std::cout << "Finished printing " << array.size() << '\n';
	// // array.print();
	// // std::cout << array.full() << '\n';
	// // delete [] array[ argv[5] ];
	// // array.remove( argv[5] );
	// std::cout << array.size() << '\n';
	// // std::cout << array.full() << '\n';
	// for ( unsigned int i = 0; i < array.size(); ++i )
	// {
	// 	delete [] array[ i ];
	// }

	if ( gen::thread() )
	{
		while( true )
		{
			std::cout << "Client\n";
			usleep( 2000 * 1000 );
		}
	}
	else
	{
		while( true )
		{
			std::cout << "Parent\n";
			usleep( 5000 * 1000 );
		}
	}

	// list_el< dict_array<char *> > * element = new list_el< dict_array<char *> >;
	// std::cout << argc - 1 << '\n';
	// dict_array<char *> * array = element->get_data();
	// for ( unsigned int i = 1; i < argc; ++i )
	// {

	// 	*(*array)[ argv[i] ] = new char [ strlen( argv[i] ) + 1 ];
	// 	strcpy( *(*array)[ argv[i] ], argv[i] );
	// }
	// array->print();
	// std::cout << array->size() << '\n';
	// std::cout << array->full() << '\n';
	// delete [] *(*array)[ argv[5] ];
	// array->remove( argv[5] );
	// std::cout << array->size() << '\n';
	// std::cout << array->full() << '\n';
	// for ( unsigned int i = 1; i < argc; ++i )
	// {
	// 	if ( i != 5 )
	// 		delete []  *(*array)[ argv[i] ];
	// }
	// std::cout << array->size() << '\n';
	// std::cout << array->full() << '\n';


	// array[ "test_2" ] = new char [20];
	// strcpy( array[ "test_2" ], "Hello world!!!" );
	// std::cout <<  array[ "test_2" ] << '\n';
	// delete []  array[ "test_2" ];

	// array->remove( "test_1" );

	// array[ "test_1" ] = new char [20];
	// strcpy( array[ "test_1" ], "Hello world!!!" );
	// std::cout <<  array[ "test_1" ] << '\n';
	// delete []  array[ "test_1" ];

	// array[ "test_1" ] = new char [20];
	// strcpy( array[ "test_1" ], "Hello world!!!" );
	// std::cout <<  array[ "test_1" ] << '\n';
	// delete []  array[ "test_1" ];

	// array[ "test_1" ] = new char [20];
	// strcpy( array[ "test_1" ], "Hello world!!!" );
	// std::cout <<  array[ "test_1" ] << '\n';
	// delete []  array[ "test_1" ];
	// std::cout <<  array[ "test_1" ] << '\n';
	// delete element;
	return 0;
}