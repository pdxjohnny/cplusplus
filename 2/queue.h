/*
	Author: John Andersen
	Date: 02/04/2015
	Description: Queue implemented using a
		circular linked list where the rear
		pointer is the most recently
		added item and rear->next is
		the first item added
*/



#ifndef NULL
	#define NULL 0
#endif



#ifndef QUEUE
	#define QUEUE 1



/*
	Struct: queue_node
	Use: Stores a value and a pointer
		to the next queue_node in a list
*/
template <typename data_type>
struct queue_node
{
	data_type value;
	queue_node * next;
};



/*
	Class: queue
	Use: Works like a line where data
		is added at the end and removed at
		the front
*/
template <typename data_type>
class queue
{
	public:
		// Sets rear and in_queue to NULL and 0
		queue( void );
		// Deletes all the queue_nodes in the queue
		~queue( void );
		// Adds data to the end of the queue
		int enqueue( const data_type & );
		// Removes the item at the front of the queue
		int dequeue ( void ); 
		// The number of items in the queue
		int size( void );
		// The queue as an array
		data_type * all( void );
		// Pointer to the item at the front of the queue
		data_type * peek( void );
	private:
		// The number of queue_nodes in the queue
		int in_queue;
		// The most recently added item
		queue_node<data_type> * rear;
};



#include "queue.cpp"
// Because of templates

#endif
