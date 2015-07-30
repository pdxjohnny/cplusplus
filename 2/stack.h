/*
	Author: John Andersen
	Date: 02/04/2015
	Description: Stack implemented using a
		linear linked list of arrays where
		last is the index of the last item
		inserted into head's values array
*/



#ifndef STACK
	#define STACK 5



/*
	Struct: stack_node
	Use: Holds an array of the data_type
		and the next node in the stack
*/
template <typename data_type>
struct stack_node
{
	data_type * values;
	stack_node * next;
};



/*
	Class: stack
	Use: First in first out data structure
		where what ever you push in can be
		imediatly poped back out
*/
template <typename data_type>
class stack
{
	public:
		// Initializes data members with defualt array size
		stack( void );
		// Initializes data members with provided array size
		stack( int num );
		// Deallocates all nodes and arrays
		~stack( void );
		// Initializes data members with defualt array size
		void init( void );
		// Deallocates all nodes and arrays
		void clear( void );
		// The number of items in the stack
		int size( void );
		// Adds the data given to the top index of the stack
		int push( const data_type & );
		// Removes the last added item
		int pop ( void ); 
		// Creates an array from the queue
		data_type * all( void );
		// Get last item put on the stack
		data_type * peek( void );
	private:
		// The front of the stack
		stack_node<data_type> * head;
		// The number of items in the stack
		int in_stack;
		// The size of each stack_nodes values array
		int array_size;
		// The index in head's values array
		// of the last added value
		int last;
};

#include "stack.cpp"
// Because of templates

#endif
