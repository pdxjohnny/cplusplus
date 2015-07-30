/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Test file sorry no comments here
*/



#include <iostream>
#include <cstdlib>


#include "tree.h"


int main(int argc, char *argv[])
{
	tree<int> life;
	for ( int i = 1; i < argc - 1; ++i )
	{
		life.get( argv[i] ) = i;
	}
	// int ** all = life.all();
	// char ** keys = life.keys();
	int size = life.size();
	for ( int i = 0; i < size; ++i )
	{
		// std::cout << keys[i] << '\t' << * all[i] << '\t' << life.key(i) << '\t' << life[i] << '\n';
		std::cout << life.key(i) << '\t' << life[i] << '\n';
	}
	std::cout << "Tree size: " << size << '\n';
	std::cout << "Removing:\t" << argv[ argc - 1 ] << "\t" << life.remove( argv[ argc - 1 ] ) << '\n';
	size = life.size();
	for ( int i = 0; i < size; ++i )
	{
		std::cout << life.key(i) << '\t' << life[i] << '\n';
	}
	std::cout << "Tree size: " << size << '\n';
	// delete [] keys;
	// delete [] all;

	return 0;
}
