/*
	Author: John Andersen
	Date: 03/19/2015
	Class: CS 163, Portland State University
	Assignment: Homework 5
	Description: Program to find a path between rides
	Algorithm:
			Load rides
			List all rides
			List all adjacent for every ride
			Find a path if asked
	Make or: g++ main.cpp gen.cpp park.cpp
*/



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

