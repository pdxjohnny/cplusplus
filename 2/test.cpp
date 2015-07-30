/*
	Author: John Andersen
	Date: 02/04/2015
	Description: Program to test stack and queue
	Algoritham: Used to test the stack and queue ADT's,
		primarily for memory usage and speed.
*/
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>

// For the stack class
#include "stack.h"
// For the queue class
#include "queue.h"


void stack_test( int loop )
{
	// Create the stack
	stack<int> test_stack( 5 );

	for (int i = 0; i < loop; ++i)
	{
		// int add = rand() % loop;
		// std::cout << i << " -> ";
		test_stack.push( i );
	}
	// std::cout << '\n';
	// std::cout << '\n';

	// int * all = test_stack.all();
	// for ( int i = test_stack.size() - 1; i >= 0 ; --i )
	// {
	// 	std::cout << all[ i ] << " -> ";
	// }
	// std::cout << '\n';
	// delete [] all;

	// for ( int i = 0; i < loop / 2; ++i )
	// {
	// 	// std::cout << "pop: " << * test_stack.peek() << '\n';
	// 	test_stack.pop();
	// }

	// all = test_stack.all();
	// for ( int i = 0; i < test_stack.size(); ++i )
	// {
	// 	std::cout << all[ i ] << " -> ";
	// }
	// std::cout << '\n';
	// delete [] all;
}



void queue_test( int loop )
{
	// Create the queue
	queue<int> test_queue;

	for (int i = 0; i < loop; ++i)
	{
		// int add = rand() % loop;
		test_queue.enqueue( i );
	}

// 	int * all = test_queue.all();
// 	for ( int i = 0; i < test_queue.size(); ++i )
// 	{
// 		std::cout << all[ i ] << " -> ";
// 	}
// 	std::cout << '\n';
// 	std::cout << '\n';
// 	delete [] all;

// 	for ( int i = 0; i < loop / 2; ++i )
// 	{
// 		// std::cout << "dequeue: " << * test_queue.peek() << '\n';
// 		test_queue.dequeue();
// 	}

// 	all = test_queue.all();
// 	for ( int i = 0; i < test_queue.size(); ++i )
// 	{
// 		std::cout << all[ i ] << " -> ";
// 	}
// 	std::cout << '\n';
// 	delete [] all;
}


int main(int argc, char const *argv[])
{
	if ( argc > 1 )
	{
		if ( 0 == strcmp( "stack", argv[1] ) )
		{
			stack_test( atoi( argv[2] ) );
		}
		else
		{
			queue_test( atoi( argv[2] ) );
		}
	}
	return 0;
}


