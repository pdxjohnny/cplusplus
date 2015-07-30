/*
	Author: John Andersen
	Date: 02/04/2015
	Description: Stack implemented using a
		linear linked list of arrays where
		last is the index of the last item
		inserted into head's values array
*/



/*
	Class: stack
	Method: Constructor
	Use: Initializes data members with defualt array size
*/
template <typename data_type>
stack<data_type>::stack( void )
{
	init();
};



/*
	Class: stack
	Method: Constructor
	Use: Initializes data members with provided array size
*/
template <typename data_type>
stack<data_type>::stack( int num )
{
	init();
	// Change from the defualt
	array_size = num;
};



/*
	Class: stack
	Method: Deconstructor
	Use: Deallocates all nodes and arrays
*/
template <typename data_type>
stack<data_type>::~stack( void )
{
	clear();
};



/*
	Class: stack
	Method: init
	Use: Initializes data members with defualt array size
*/
template <typename data_type>
void stack<data_type>::init( void )
{
	// No list head is NULL
	this->head = NULL;
	// Nothing in the stack
	this->in_stack = 0;
	// Array size is the defined size
	this->array_size = STACK;
}



/*
	Class: stack
	Method: clear
	Use: Deallocates all nodes and arrays
*/
template <typename data_type>
void stack<data_type>::clear( void )
{
	// Create a node to walk
	stack_node<data_type> * curr = head;
	// Create a node to delete
	stack_node<data_type> * del = NULL;
	// Loop through the list
	while ( curr )
	{
		// Delete the current node
		del = curr;
		// Move to the next node
		curr = curr->next;
		// Deallocate the array of values
		delete [] del->values;
		// Delete the node
		delete del;
	}
	// No list head is NULL
	this->head = NULL;
	// Nothing in the stack
	this->in_stack = 0;
}



/*
	Class: stack
	Method: size
	Use: The number of items in the stack
*/
template <typename data_type>
int stack<data_type>::size( void )
{
	// The number of items in the stack
	return this->in_stack;
}



/*
	Class: stack
	Method: push
	Use: Adds the data given to the top index of the stack
*/
template <typename data_type>
int stack<data_type>::push( const data_type & to_add )
{
	// If there is no list
	if ( !head )
	{
		// Allocate memory for the new node
		head = new stack_node<data_type>;
		// Create the array of values
		head->values = new data_type[ this->array_size ];
		// Set the first value of the area to to_add
		head->values[ 0 ] = to_add;
		// Make sure last is starting at the beginning
		this->last = 0;
		// Next is nowhere, only node in list
		head->next = NULL;
	}
	// If the top array is full
	else if ( this->last >= this->array_size - 1  )
	{
		// Allocate memory for the new node
		stack_node<data_type> * add = new stack_node<data_type>;
		// Create the array of values
		add->values = new data_type[ this->array_size ];
		// Set the first value of the area to to_add
		add->values[ 0 ] = to_add;
		// Make sure last is starting at the beginning
		this->last = 0;
		// Next is the front, add at the front
		add->next = head;
		// Set head to the new stack_node
		head = add;
	}
	// The top array has free space
	else
	{
		// Increment the lastest index
		++this->last;
		// Set the index of the head node values
		// to the value provided
		head->values[ this->last ] = to_add;
	}
	// Increment the numebr of elements in the stack
	++this->in_stack;
	// Return the numebr of elements in the stack
	return this->in_stack;
}



/*
	Class: stack
	Method: pop
	Use: Removes the last added item
*/
template <typename data_type>
int stack<data_type>::pop( void )
{
	// If there is a list
	if ( head )
	{
		// Go back one on the index
		--this->last;
		// Decrement the number of items on the stack
		--this->in_stack;
		// If last less than a possible array index
		if ( this->last < 0 )
		{
			// Delete the head node
			stack_node<data_type> * del = head;
			// Make head the next node
			head = head->next;
			// Deallocate the array of values int he node
			delete [] del->values;
			// Deallocate the empty item at the front
			delete del;
			// Reset the array_size to be the top of the
			// next array
			this->last = this->array_size - 1;
		}
		// A data_type was poped off
		return true;
	}
	// No list can't remove
	return false;
}



/*
	Class: stack
	Method: all
	Use: Creates an array from the queue
*/
template <typename data_type>
data_type * stack<data_type>::all( void )
{
	// The pointer to the array in reverse form
	data_type * reverse = NULL;
	// The pointer to the array in normal form
	data_type * all = NULL;
	// If there is a list / stack
	if ( this->in_stack )
	{
		// Make reverse and all arrays have the same
		// number of elements the stack does
		reverse = new data_type[ this->in_stack ];
		all = new data_type[ this->in_stack ];
		// Create a walker starting at head
		stack_node<data_type> * curr = head;
		// Added is used as an index because in every
		// node the values are stored with the last
		// added at the end so we have to loop backwards
		int added = 0;
		// Loop backwards through heads values array
		for ( int i = this->last; i >= 0; --i )
		{
			// Set reverse to the oppisite position as values
			reverse[ added ] = curr->values[ i ];
			// Increment added because we have gone to the next
			++added;
		}
		// Go to the next node
		curr = curr->next;
		// Loop through the rest of the list
		while ( curr )
		{
			// Loop backwards through teh values array
			for ( int i = this->array_size - 1; i >= 0; --i )
			{
				// Set reverse to the oppisite position as values
				reverse[ added ] = curr->values[ i ];
				// Increment added because we have gone to the next
				++added;
			}
			// Go to the next node
			curr = curr->next;
		}
		// Reset the added to 0 for the reverse loop
		added = 0;
		// Loop through the reverse array in reverse order
		for ( int i = this->in_stack - 1; i >= 0; --i )
		{
			// Reversed reverse becomes the actual
			all[ added ] = reverse[ i ];
			// Increment the index of the actual
			++added;
		}
		// Delete the backwards array
		delete [] reverse;
	}
	// Return the array or lackthereof
	return all;
}



/*
	Class: stack
	Method: peek
	Use: Get last item put on the stack
*/
template <typename data_type>
data_type * stack<data_type>::peek( void )
{
	// If there is anything on the stack
	if ( head )
	{
		// Return a pointer to the first item
		return & head->values[ this->last ];
	}
	// Stack is empty
	return NULL;
}


