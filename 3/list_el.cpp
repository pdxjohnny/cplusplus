/*
	Author: John Andersen
	Date: 11/4/2014
	Description: list_el class methods.
*/

//#ifndef LIST_EL
//    #include "list_el.h"
//#endif
// This is intentionally commented out, explination in is dlist.h


/*
	Class: list_el
	Method: Constructor
	Use: Initialises data members
*/
template <typename data_value>
list_el<data_value>::list_el()
{
	this->val = 0;
	this->key = NULL;
	// this->data = NULL;
	this->next = NULL;
	this->prev = NULL;
}


/*
	Class: list_el
	Method: deconstructor
	Use: deletes whatever data is pointing to
*/
template <typename data_value>
list_el<data_value>::~list_el()
{
	// delete this->data;
	if ( this->key )
	{
		delete [] this->key;
	}
}

/*
	Class: list_el
	Method: set_val
	Use: set_vals the value of the private val to val
*/
template <typename data_value>
void list_el<data_value>::set_val(unsigned int val)
{
	this->val = val;
};


/*
	Class: list_el
	Method: set_key
	Use: set_keys the value of the private val to val
*/
template <typename data_value>
void list_el<data_value>::set_key( char * new_key )
{
	if ( this->key != NULL )
	{
		delete [] this->key;
	}
	this->key = new char[ strlen( new_key ) + 1 ];
	strcpy( this->key, new_key );
};


/*
	Class: list_el
	Method: set_data
	Use: set_datas the value of the private val to val
*/
template <typename data_value>
void list_el<data_value>::set_data( data_value data )
{
	this->data = data;
};


/*
	Class: list_el
	Method: set_next
	Use: set_nexts the value of the private val to val
*/
template <typename data_value>
void list_el<data_value>::set_next( list_el<data_value> *next)
{
	this->next = next;
};



/*
	Class: list_el
	Method: set_prev
	Use: set_prevs the value of the private val to val
*/
template <typename data_value>
void list_el<data_value>::set_prev( list_el<data_value> *prev)
{
	this->prev = prev;
};


/*
	Class: list_el
	Method: get_val
	Use: gets the value / position in list of this list_el<data_value>
*/
template <typename data_value>
unsigned int list_el<data_value>::get_val(void)
{
	return this->val;
};


/*
	Class: list_el
	Method: get_key
	Use: gets the value / position in list of this list_el<data_value>
*/
template <typename data_value>
char * list_el<data_value>::get_key(void)
{
	return this->key;
};


/*
	Class: list_el
	Method:get_data
	Use: get_data the value of the private val to val
*/
template <typename data_value>
data_value * list_el<data_value>::get_data( void )
{
	return &this->data;
};


/*
	Class: list_el
	Method: get_next
	Use: gets the value / position in list of this list_el<data_value>
*/
template <typename data_value>
list_el<data_value> *list_el<data_value>::get_next(void)
{
	return this->next;
};


/*
	Class: list_el
	Method: get_prev
	Use: gets the value / position in list of this list_el<data_value>
*/
template <typename data_value>
list_el<data_value> *list_el<data_value>::get_prev(void)
{
	return this->prev;
};
