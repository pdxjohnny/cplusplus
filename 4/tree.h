/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Binary Tree
*/



// For NULL
#ifndef NULL
	#define NULL 0
#endif

// Ensure nothing gets redeclared
#ifndef TREE
	#define TREE 1

#include <cstdio>
#include <cstdlib>
#include <cstring>

/*
	Struct: tree_node
	Use: Holds the left right and data for a key in the tree
*/
template <typename data_type>
struct tree_node
{
	char * key;
	data_type value;
	tree_node * left;
	tree_node * right;
};


/*
	Class: tree
	Use: A binary tree organised by key
*/
template <typename data_type>
class tree
{
public:
	// Constructor and deconstructor
	tree<data_type>();
	~tree<data_type>();
	// Allocates the tree
	void init( void );
	// Deallocates the tree
	void destroy( void );
	void destroy( tree_node<data_type> * & root );
	// Allows access by key value
	data_type & operator [] ( unsigned int num );
	data_type & operator [] ( char * key );
	// Access by index when ordered by key
	char * key( unsigned int num );
	data_type & get( unsigned int num );
	tree_node<data_type> * get( unsigned int & num, unsigned int & index, tree_node<data_type> * root );
	// Allows access by key value
	data_type & get( char * key );
	tree_node<data_type> * get( char * key, tree_node<data_type> * root );
	// Inserts a data of the tree type into the tree
	data_type & insert( char * key );
	tree_node<data_type> * insert( char * key, tree_node<data_type> * & root );
	// Check if key is present
	bool contains( char * key );
	// Returns the number of elements in the tree
	unsigned int size( void );
	// Returns the keys of the elements in the tree
	data_type ** all( void );
	void all( unsigned int & index , data_type ** array, tree_node<data_type> * root );
	// Returns the keys of the elements in the tree
	char ** keys( void );
	void keys( unsigned int & index , char ** array, tree_node<data_type> * root );
	// Removes an element from the array
	bool remove( char * key );
	bool remove( char * key, tree_node<data_type> * & root );
	tree_node<data_type> * inorder( tree_node<data_type> * root, tree_node<data_type> * & parent );
private:
	// Root of the tree
	tree_node<data_type> * root;
	// Number of nodes in the tree
	unsigned int in_tree;
};


#include "tree.cpp"
#endif
