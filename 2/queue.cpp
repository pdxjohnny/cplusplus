/*
	Author: John Andersen
	Date: 02/04/2015
	Description: Queue implemented using a
		circular linked list where the rear
		pointer is the most recently
		added item and rear->next is
		the first item added
*/



/*
	Class: queue
	Method: Constructor
	Use: Sets rear and in_queue to NULL and 0
*/
template <typename data_type>
queue<data_type>::queue( void )
{
	// NULL because there is no list
	rear = NULL;
	// There are 0 items
	in_queue = 0;
}



/*
	Class: queue
	Method: Deconstuctor
	Use: Deletes all the queue_nodes in the queue
*/
template <typename data_type>
queue<data_type>::~queue( void )
{
	// If there is a queue
	if ( rear )
	{
		// For walking the list
		queue_node<data_type> * curr = rear;
		// For deleting after walking to next
		queue_node<data_type> * del = NULL;
		// Loop through the list
		do
		{
			// Set delete to the current node
			del = curr;
			// Walk to the next node
			curr = curr->next;
			// Deallocate the node
			delete del;
		}
		// Stop when the walker is the first queue_node
		while ( curr && curr != rear );
		// Reset the values of the members
		rear = NULL;
		in_queue = 0;
	}
}



/*
	Class: queue
	Method: enqueue
	Use: Adds data to the end of the queue
*/
template <typename data_type>
int queue<data_type>::enqueue(const data_type & to_add)
{
	// Allocate memory for a new queue_node
	queue_node<data_type> * add = new queue_node<data_type>;
	// Set eh next pointer to NULL
	add->next = NULL;
	// Set the value to the value provided
	add->value = to_add;
	// If there is no list
	if ( !rear )
	{
		// The rear becomes the new addition
		rear = add;
		// The rear points to itself
		rear->next = rear;
	}
	// There is a list
	else
	{
		// Add next becomes the first item
		add->next = rear->next;
		// The rear next points to the new item
		rear->next = add;
		// The rear becomes the new item
		rear = add;
	}
	// Increment the number of nodes in the queue
	++this->in_queue;
	// Return the number of nodes in the queue
	return this->in_queue;
}



/*
	Class: queue
	Method: dequeue
	Use: Removes the item at the front of the queue
*/
template <typename data_type>
int queue<data_type>::dequeue()
{
	// If there is a queue
	if ( rear )
	{
		// If there is more than one node
		if ( rear != rear->next )
		{
			// Rear next is the oldest item so delete it
			queue_node<data_type> * del = rear->next;
			// Set the oldest item to be the next oldest item
			rear->next = rear->next->next;
			// Delete the oldest item
			delete del;
		}
		// If there is only one node
		else
		{
			// Reset rear
			delete rear;
			rear = NULL;
		}
		// Decrement the number of nodes in the queue
		--this->in_queue;
		// Return true because something was removed
		return true;
	}
	// Return false because nothing was removed
	return false;
}



/*
	Class: queue
	Method: size
	Use: The number of items in the queue
*/
template <typename data_type>
int queue<data_type>::size( void )
{
	// Return the number of nodes in the queue
	return this->in_queue;
}



/*
	Class: queue
	Method: all
	Use: The queue as an array
*/
template <typename data_type>
data_type * queue<data_type>::all( void )
{
	// A pointer to an array of the data_type
	data_type * all = NULL;
	// If there is a queue
	if ( rear && this->in_queue )
	{
		// Allocate memory for the array
		all = new data_type[ this->in_queue ];
		// Start the wakler at the oldest item
		queue_node<data_type> * curr = rear->next;
		int i = 0;
		do
		{
			// The index gets the current value
			all[ i ] = curr->value;
			// Traverse to the next queue_node
			curr = curr->next;
			// Increment the index
			++i;
		}
		// While we haven't reached the oldest item
		while ( curr && curr != rear->next );
	}
	// Return the array or lack therof
	return all;
}



/*
	Class: queue
	Method: peek
	Use: Pointer to the item at the front of the queue
*/
template <typename data_type>
data_type * queue<data_type>::peek(void)
{
	// If there is a queue
	if ( rear )
	{
		// Return a pointer to the oldest nodes value
		return & rear->next->value;
	}
	// No list so can't return a pointer to anywhere
	return NULL;
}


