/*
	Author: John Andersen
	Date: 10/15/2014
	Description: Doubley linked list for phrase program
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "phrase_class.cpp"

/*
	Class: dlist
	Use: Stores all of the phrases and methods to
	 asscess and insert them into a linked list;
*/
class dlist
{
private:
	phrase *head;
	phrase *tail;
	unsigned int list_size;
public:
	dlist()
	{
		this->head = NULL;
		this->tail = NULL;
		this->list_size = 0;
	};
	phrase *get_head();
	phrase *get_tail();
	int insert(phrase *newcurr);
	unsigned int size();
	phrase *operator[]( int num );
};

phrase *dlist::operator[]( int num )
{
	phrase *curr = this->get_head();
	for ( int i = 0; curr && i < num; ++i )
	{
		curr = curr->next;
	}
	return curr;
}


/*
		Class: dlist
		Method: get_head
		Use: Returns the pointer to head
*/
phrase *dlist::get_head()
{
	return this->head;
}


/*
		Class: dlist
		Method: get_tail
		Use: Returns the pointer to tail
*/
phrase *dlist::get_tail()
{
	return this->tail;
}


/*
	Class: dlist
	Method: size
	Use: Returns the number of elements in the list
*/
unsigned int dlist::size()
{
	return this->list_size;
}


/*
	Class: dlist
	Method: insert
	Use: Inserts into the list based on the val
*/
int dlist::insert(phrase *newcurr)
{
 
	phrase *walker;
	int x=newcurr->val;

	++this->list_size;
	 
	if(head==NULL)
	{
		head=newcurr;
		tail=newcurr;
	}
 
	else if(x<=head->val)
	{
		newcurr->next=head;
		newcurr->prev=NULL;
		head->prev=newcurr;
		head=newcurr;
	}
 
	else if(x>tail->val)
	{
		tail->next=newcurr;
		newcurr->prev=tail;
		newcurr->next=NULL;
		tail=newcurr;
	}
	else{
		walker=head;
		while(x>walker->val)
		{
			walker=walker->next;
		}
		walker->prev->next=newcurr;
		newcurr->prev=walker->prev;
		newcurr->next=walker;
		walker->prev=newcurr;
	}

	return this->list_size;
}
