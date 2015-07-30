/*
	Author: John Andersen
	Date: 02/04/2015
	Description: Calculator which creates an equation
		using a stack and a queue for the operations
*/



#include "calc.h"



/*
	Class: calc
	Method: Constructor
	Use: Initializes data members
*/
calc::calc( void )
{
	init();
};



/*
	Class: calc
	Method: Destructor
	Use: Deallocates all memory used
*/
calc::~calc( void )
{
	destroy();
};



/*
	Class: calc
	Method: init
	Use: Allocates stack and queue
*/
void calc::init( void )
{
	// Create an instance of a queue
	// which will contain the strings
	// of exec statements
	perform = new queue<char *>;
	// Create a stack which will contain all
	// of the calculations to be performed
	last = new stack<calculation>( 5 );
}



/*
	Class: calc
	Method: destroy
	Use: Deallocates all of the strings stored in
		the queue and then deallocates the stack
		and the queue
*/
void calc::destroy( void )
{
	// Get the array of all the stings
	char ** actions = perform->all();
	// Loop through all of the strings
	for ( int i = 0; i < perform->size(); ++i )
	{
		// Deallocate the memory given to each
		delete [] actions[ i ];
	}
	// Deallocate the array we used
	delete [] actions;
	// Deallocate the queue
	delete perform;
	// Deallocate the stack
	delete last;
}



/*
	Class: calc
	Method: clear
	Use: Resets the stack and the queue
*/
void calc::clear( void )
{
	// Deallocate the stack	and queue
	destroy();
	// Recreate the stack and queue
	init();
}



/*
	Class: calc
	Method: add_to_queue
	Use: Adds a calculation in action number form
		to the queue
*/
void calc::add_to_queue( calculation & add )
{
	// The string being formated as an exec statement
	char queue_string[ gen::STRING_SIZE ];
	// Create the correct statement based on the operation
	if ( add.operation == '+' )
	{
		sprintf( queue_string, "add %f", add.value );
	}
	else if ( add.operation == '-' )
	{
		sprintf( queue_string, "subtract %f", add.value );
	}
	else if ( add.operation == '*' )
	{
		sprintf( queue_string, "multiply %f", add.value );
	}
	else if ( add.operation == '/' )
	{
		sprintf( queue_string, "divide %f", add.value );
	}
	// Allocate the string to be added to the queue
	char * alloced_queue_string = new char[ strlen( queue_string ) + 1 ];
	// Make the queue sting the formated string
	strcpy( alloced_queue_string, queue_string );
	// Add the action to the queue
	perform->enqueue( alloced_queue_string );
}



/*
	Class: calc
	Method: add
	Use: Creates an add calculation pushes
		it to the stack and enqueues it to
		the queue
*/
double calc::add( double value )
{
	// Create the calculation to add
	// to the stack
	calculation calculation_to_add;
	calculation_to_add.value = value;
	// Set the correct operation
	calculation_to_add.operation = '+';
	// Add the operation to the stack
	last->push( calculation_to_add );
	// Add the action to the queue
	add_to_queue( calculation_to_add );
	return calculate();
}



/*
	Class: calc
	Method: subtract
	Use: Creates an subtract calculation pushes
		it to the stack and enqueues it to
		the queue
*/
double calc::subtract( double value )
{
	// Create the calculation to add
	// to the stack
	calculation calculation_to_add;
	calculation_to_add.value = value;
	// Set the correct operation
	calculation_to_add.operation = '-';
	// Add the operation to the stack
	last->push( calculation_to_add );
	// Add the action to the queue
	add_to_queue( calculation_to_add );
	return calculate();
}



/*
	Class: calc
	Method: multiply
	Use: Creates an multiply calculation pushes
		it to the stack and enqueues it to
		the queue
*/
double calc::multiply( double value )
{
	// Create the calculation to add
	// to the stack
	calculation calculation_to_add;
	calculation_to_add.value = value;
	// Set the correct operation
	calculation_to_add.operation = '*';
	// Add the operation to the stack
	last->push( calculation_to_add );
	// Add the action to the queue
	add_to_queue( calculation_to_add );
	return calculate();
}



/*
	Class: calc
	Method: divide
	Use: Creates an divide calculation pushes
		it to the stack and enqueues it to
		the queue
*/
double calc::divide( double value )
{
	// Create the calculation to add
	// to the stack
	calculation calculation_to_add;
	calculation_to_add.value = value;
	// Set the correct operation
	calculation_to_add.operation = '/';
	// Add the operation to the stack
	last->push( calculation_to_add );
	// Add the action to the queue
	add_to_queue( calculation_to_add );
	return calculate();
}



/*
	Class: calc
	Method: calculate
	Use: Performs all of the calculations
		on the stack
*/
double calc::calculate( void )
{
	// Result is the return value
	// it is the result of the equation
	double result = 0;
	// Special is the result of a sequence
	// of operation preformed one after another
	// in acordinace with mathmatical order of operations
	double special = 0;
	// All is all the calculations on the stack as an array
	calculation * all = last->all();
	// Loop through all of the calculations
	for ( int i = 0; i < last->size(); ++i )
	{
		// special should be zero unless it is
		// set in the while loop
		special = 0;
		// This loop will ensure that order of operations
		// is followed by performing calculations on special
		// and exiting when multiplication and dividsion are
		// no longer imideately used
		while (
			( i < last->size() &&
				( all[ i ].operation == '*' ||
					all[ i ].operation == '/' ) ||
			( i + 1 < last->size() &&
				( all[ i + 1 ].operation == '*' ||
					all[ i + 1 ].operation == '/' ) ) )
			)
		{
			// If the current operation is * or / then we have to
			// multiply or divide special because multiplication
			// and dividsion need to be preformed first in an equation
			// also if the next operation is going to be multiplication
			// or dividsion then we should add or subtract from special
			// because the operation was intended to be preformed on the
			// value preceding it
			if ( all[ i ].operation == '+' )
			{
				special += all[ i ].value;
			}
			else if ( all[ i ].operation == '-' )
			{
				special -= all[ i ].value;
			}
			else if ( all[ i ].operation == '*' )
			{
				special *= all[ i ].value;
			}
			else if ( all[ i ].operation == '/' )
			{
				special /= all[ i ].value;
			}
			// Move to the next operation to see if we still
			// need to operate on special
			++i;
		}
		// Add special to result, if no multiplication of dividsion
		// occored then 0 / nothing is added
		result += special;
		// If the while loop has not put us over the end
		if ( i < last->size() )
		{
			// Perform the requested operation on result
			if ( all[ i ].operation == '+' )
			{
				result += all[ i ].value;
			}
			else if ( all[ i ].operation == '-' )
			{
				result -= all[ i ].value;
			}
		}
	}
	// Deallocate the array that is the stack
	delete [] all;
	// Return the calculated result
	return result;
}



/*
	Class: calc
	Method: flip
	Use: Makes the calculation have the
		oppisite operation
*/
void calc::flip( calculation & flip )
{
	// This is pretty self explanitory ^
	if ( flip.operation == '+' )
	{
		flip.operation = '-';
	}
	else if ( flip.operation == '-' )
	{
		flip.operation = '+';
	}
	else if ( flip.operation == '*' )
	{
		flip.operation = '/';
	}
	else if ( flip.operation == '/' )
	{
		flip.operation = '*';
	}
}



/*
	Class: calc
	Method: last_operation
	Use: Populates last with the last calculation
		to be put on the stack, false if stack is
		empty
*/
bool calc::last_operation( calculation & last )
{
	// Ask for the last operation
	calculation * last_calc = this->last->peek();
	// If there is a stack there will be an operation
	if ( last_calc )
	{
		// Set the provided calculation
		// to be the last calculation
		last = * last_calc;
		// Return true because last was set
		return true;
	}
	// Return false because last wasn't set
	return false;
}



/*
	Class: calc
	Method: undo
	Use: Pops the last request off the stack and
		add the the oppisite of the last request
		to the queue to simulate a cancelation
		do to the undo
*/
double calc::undo( int number )
{
	// Loop for the number of times given
	for ( int i = 0; i < number; ++i )
	{
		// Check if there is a calculation on
		// the stack
		calculation * undo = last->peek();
		// If there is
		if ( undo )
		{
			// Flip the sing so as to reverse its
			// affects on the equation
			flip( * undo );
			// Add the fliped calculation the the
			// queue so the user can see it cancels
			// which is an undo
			add_to_queue( * undo );
		}
		// Remove the last item if its there
		last->pop();
	}
	// Return the recalculated total
	return calculate();
}



/*
	Class: calc
	Method: undo
	Use: Undos until a particular calculation
*/
double calc::undo( calculation & until )
{
	// Grab the last calculation
	calculation * undo = last->peek();
	// While the operation and value of the last
	// calculation on the stack do not match
	// the calculation passed in pop one off
	// the stack
	while ( undo &&
		undo->operation != until.operation && 
		undo->value != until.value
		)
	{
		// Remove the last calculation
		last->pop();
		// Grab the last calculation
		undo = last->peek();
	}
	// Return the recalculated total
	return calculate();
}



/*
	Class: calc
	Method: view_history
	Use: Displays the actions in the queue as well
		as the current equation created by the stack
*/
int calc::view_history( void )
{
	// Get the array of strings that are commands
	char ** actions = perform->all();
	// Loop thorugh all the comands used to make the equation
	for ( int i = 0; i < perform->size(); ++i )
	{
		// Print out the command
		std::cout << actions[ i ] << '\n';
	}
	// Delete the array of commands
	delete [] actions;
	// If there is anything on the stack
	if ( last->size() )
	{
		// Get all of the calculations on the stack
		calculation * all = last->all();
		// State that the equation starts with doing something to 0
		// which makes sense because if the user was to exec a string
		// with just a number it would add that number thus starting the
		// equation with that number
		std::cout << 0 << ' ';
		// Loop through all the operations
		for ( int i = 0; i < last->size(); ++i )
		{
			// Print the operation and the value associated with is=t
			std::cout << all[ i ].operation << ' ' << all[ i ].value << ' ';
		}
		// Print a newline at the end of the equation
		std::cout << '\n';
		// Deallocate the array of calculations
		delete [] all;
	}
	// Return how many calculations are in the equation
	return last->size();
}



/*
	Class: calc
	Method: exec
	Use: Calls the proper method given a sting
		in the format of action number
*/
double calc::exec( const char * initial )
{
	// Holds the action, such as add
	// subtract, multiply, or divide
	char action[ strlen( initial ) + 1 ];
	// Holds the number as a string associated
	// with the action
	char number[ strlen( initial ) + 1 ];
	// Split the action and the number on the space
	gen::split_line( initial, action, number, ' ' );
	// The return value will be the result of
	// the equation calculated after the action
	// is performed
	double result = 0;
	// If all we have is number then add it
	if ( gen::number( action ) )
	{
		result = add( atof( action ) );
	}
	// Call the method with the same name as action
	// pass it the foalt / double version of number
	else if ( strcmp( action, "add" ) == 0 )
	{
		result = add( atof( number ) );
	}
	else if ( strcmp( action, "subtract" ) == 0 )
	{
		result = subtract( atof( number ) );
	}
	else if ( strcmp( action, "multiply" ) == 0 )
	{
		result = multiply( atof( number ) );
	}
	else if ( strcmp( action, "divide" ) == 0 )
	{
		result = divide( atof( number ) );
	}
	// Return the current result of the equation
	return result;
}


