/*
	Author: John Andersen
	Date: 02/04/2015
	Description: Calculator which creates an equation
		using a stack and a queue for the operations
*/



#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>

#include "gen.h"
#include "stack.h"
#include "queue.h"


#ifndef CALCULATOR
	#define CALCULATOR



/*
	Struct: calculation
	Use: Stores the value and operation
		which will be exicuted on the next
		value
*/
struct calculation
{
	double value;
	char operation;
};



/*
	Class: calc
	Use: Proforms operations using the calculation
		struct as well as a stack and queue
*/
class calc
{
	public:
		// Initializes data members
		calc();
		// Deallocates all memory used
		~calc();
		// Allocates stack and queue
		void init( void );
		// Deallocates stack and queue
		void destroy( void );
		// Resets the stack and the queue
		void clear( void );
		// Adds a calculation in action number form
		void add_to_queue( calculation & );
		// Creates an add calculation
		double add( double value );
		// Creates an subtract calculation
		double subtract( double value );
		// Creates an multiply calculation
		double multiply( double value );
		// Creates an divide calculation
		double divide( double value );
		// Performs all of the calculations
		double calculate();
		// Makes the calculation have the oppisite operation
		void flip( calculation & ); 
		// Populates last with the last calculation
		bool last_operation( calculation & );
		// Pops the last request off the stack
		double undo( int number );
		// Undos until a particular calculation
		double undo( calculation & );
		// Displays the actions in the queue as well as the equation
		int view_history();
		// Calls the proper method given a sting
		double exec( const char * );
	private:
		// Holds all the commands recived
		queue<char *> * perform;
		// Holds all the calculations
		stack<calculation> * last;
};



#endif
