/*
	Author: John Andersen
	Date: 02/19/2015
	Description: Binary Tree
*/



/*
	Class: tree
	Method: Constructor
	Use: Initialises data members
	Input: None
	Output: None
*/
template <typename data_type>
tree<data_type>::tree()
{
	init();
}



/*
	Class: tree
	Method: Destructor
	Use: Deallocates all nodes
	Input: None
	Output: None
*/
template <typename data_type>
tree<data_type>::~tree()
{
	destroy();
}



/*
	Class: tree
	Method: init
	Use: Initialises data members
	Input: None
	Output: None
*/
template <typename data_type>
void tree<data_type>::init( void )
{
	root = NULL;
	in_tree = 0;
}



/*
	Class: tree
	Method: destroy
	Use: Deallocates all nodes
	Input: None
	Output: None
*/
template <typename data_type>
void tree<data_type>::destroy( void )
{
	destroy( root );
	in_tree = 0;
}



/*
	Class: tree
	Method: destroy
	Use: Deallocates all nodes recursivly
	Input: Root of tree
	Output: None
*/
template <typename data_type>
void tree<data_type>::destroy( tree_node<data_type> * & root )
{
	if ( !root )
		return;
	// Go down booth sides
	destroy( root->left );
	destroy( root->right );
	// Deallocate the key string
	delete [] root->key;
	// Delete the node
	delete root;
	// Set to to NULL
	root = NULL;
}



/*
	Class: tree
	Method: operator []
	Use: Access values as if the tree was a sorted array
	Input: Index of item
	Output: Value of node found
*/
template <typename data_type>
data_type & tree<data_type>::operator [] ( unsigned int num )
{
	return get( num );
}



/*
	Class: tree
	Method: operator []
	Use: Gets a key in the tree
	Input: Key to search for
	Output: Value of node found 
*/
template <typename data_type>
data_type & tree<data_type>::operator [] ( char * key )
{
	return get( key );
}



/*
	Class: tree
	Method: key
	Use: Access keys as if the tree was a sorted array
	Input: Index of key
	Output: Key of node found
*/
template <typename data_type>
char * tree<data_type>::key( unsigned int num )
{
	// It cant be in the tree if its bigger than the number of item sin it
	if ( in_tree <= num )
	{
		return NULL;
	}
	unsigned int index = 0;
	return get( num, index, root )->key;
}



/*
	Class: tree
	Method: get
	Use: Access values as if the tree was a sorted array
	Input: Index of item
	Output: Value of node found
*/
template <typename data_type>
data_type & tree<data_type>::get( unsigned int num )
{
	// It wont be found so create it
	if ( in_tree <= num )
	{
		char key [20];
		sprintf( key, "%d", num );
		return insert( key );
	}
	// Find it
	unsigned int index = 0;
	return get( num, index, root )->value;
}



/*
	Class: tree
	Method: get
	Use: Access nodes as if the tree was a sorted array
	Input: Index of item to find, current index, and root of the tree
	Output: Node found
*/
template <typename data_type>
tree_node<data_type> * tree<data_type>::get( unsigned int & num, unsigned int & index, tree_node<data_type> * root )
{
	if ( !root )
		return NULL;
	// To see if one of the sides found it
	tree_node<data_type> * found = NULL;
	// Look of the index on the left, that will be index 0 if its the leftmost node
	found = get( num, index, root->left );
	if ( found )
	{
		return found;
	}
	// Check if this node is the index
	if ( num == index )
	{
		return root;
	}
	// increment the index
	++index;
	// Look of the index on the right
	found = get( num, index, root->right );
	if ( found )
	{
		return found;
	}
	return NULL;
}



/*
	Class: tree
	Method: get
	Use: Finds the value of a key in the tree
	Input: Key to search for
	Output: Value of node found
*/
template <typename data_type>
data_type & tree<data_type>::get( char * key )
{
	// Try to get if that doesnt work then insert
	if ( !get( key, root ) )
	{
		return insert( key );
	}
	return get( key, root )->value;
}



/*
	Class: tree
	Method: get
	Use: Finds a node coresponding to a key in the tree
	Input: Key to search for and root of the tree
	Output: Node found
*/
template <typename data_type>
tree_node<data_type> * tree<data_type>::get( char * key, tree_node<data_type> * root )
{
	// Look for the key this si a simple binary search algoritham 
	if ( !root )
	{
		return NULL;
	}
	// If key return
	if ( 0 == strcmp( root->key, key ) )
	{
		return root;
	}
	// If less go left
	else if ( 0 < strcmp( root->key, key ) )
	{
		return get( key, root->left );
	}
	// If greater than or equal to go right
	return get( key, root->right );
}



/*
	Class: tree
	Method: insert
	Use: Inserts a node into the tree
	Input: Key to insert
	Output: Values of the inserted node
*/
template <typename data_type>
data_type & tree<data_type>::insert( char * key )
{
	return insert( key, root )->value;
}



/*
	Class: tree
	Method: insert
	Use: Inserts a node into the tree
	Input: Key to insert and the root of the tree
	Output: Node inserted
*/
template <typename data_type>
tree_node<data_type> * tree<data_type>::insert( char * key, tree_node<data_type> * & root )
{
	// Allocate the node
	if ( !root )
	{
		root = new tree_node<data_type>;
		// allocate the key
		root->key = new char [ strlen( key ) + 1 ];
		strcpy( root->key, key );
		// Make sure left and right are null
		root->left = root->right = NULL;
		++in_tree;
		return root;
	}
	// Binary search
	else if ( 0 < strcmp( root->key, key ) )
	{
		return insert( key, root->left );
	}
	return insert( key, root->right );
}



/*
	Class: tree
	Method: contains
	Use: Checks if a key is in the tree
	Input: Key to search for
	Output: True or false that is set due to a not found being
		NULL and a found being the pointer so true
*/
template <typename data_type>
bool tree<data_type>::contains( char * key )
{
	return get( key, root );
}



/*
	Class: tree
	Method: size
	Use: How many items are in the tree
	Input: None
	Output: Number of nodes in the tree
*/
template <typename data_type>
unsigned int tree<data_type>::size( void )
{
	return in_tree;
}


/*
	Class: tree
	Method: all
	Use: Creates an array to access tree values
	Input: None
	Output: An array whos members a pointers to the values of nodes
		this allows a client to eficently opperate on the tree as if
		it were a sorted array without the need to find the thoretical
		position every time the subscript operator is used
*/
template <typename data_type>
data_type ** tree<data_type>::all( void )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	unsigned int index = 0;
	data_type ** array = new data_type * [ in_tree ];
	all( index, array, root );
	return array;
}



/*
	Class: tree
	Method: all
	Use: Fills an array with the pointers to node values
	Input: Current index, array to fill, and pointer to root
	Output: None
*/
template <typename data_type>
void tree<data_type>::all( unsigned int & index , data_type ** array, tree_node<data_type> * root )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	if ( !root )
		return;
	all( index, array, root->left );
	array[ index ] = & root->value;
	++index;
	all( index, array, root->right );
	return;
}



/*
	Class: tree
	Method: keys
	Use: Creates an array to access tree keys
	Input: None
	Output: An array whos members a pointers to the keys of nodes
		this allows a client to eficently opperate on the tree as if
		it were a sorted array without the need to find the thoretical
		position every time the subscript operator is used
*/
template <typename data_type>
char ** tree<data_type>::keys( void )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	unsigned int index = 0;
	char ** array = new char * [ in_tree ];
	keys( index, array, root );
	return array;
}



/*
	Class: tree
	Method: keys
	Use: Fills an array with the pointers to node keys
	Input: Current index, array to fill, and pointer to root
	Output: None
*/
template <typename data_type>
void tree<data_type>::keys( unsigned int & index , char ** array, tree_node<data_type> * root )
{
	// More indexing, see get ( unsigned int num ) for explination of how this works
	if ( !root )
		return;
	keys( index, array, root->left );
	array[ index ] = root->key;
	++index;
	keys( index, array, root->right );
	return;
}



/*
	Class: tree
	Method: remove
	Use: Removes a node from the tree
	Input: Key to remove
	Output: 1 for removed 0 for not	found
*/
template <typename data_type>
bool tree<data_type>::remove( char * key )
{
	return remove( key, root );
}



/*
	Class: tree
	Method: remove
	Use: Removes a node from the tree
	Input: Key of node to remove and root of tree
	Output: 1 for removed 0 for not	found
*/
template <typename data_type>
bool tree<data_type>::remove( char * key, tree_node<data_type> * & root )
{
	if ( !root )
	{
		return false;
	}
	if ( 0 == strcmp( root->key, key ) )
	{
		// We know we are goiong to delete root
		tree_node<data_type> * del = root;
		// If its a leaf then no problem delete
		if ( !root->left && !root->right )
		{
			root = NULL;
		}
		// If it has a left and not a right just replace
		else if ( root->left && !root->right )
		{
			root = root->left;
		}
		// If it has a right and not a left just replace
		else if ( root->right && !root->left )
		{
			root = root->right;
		}
		// If it has two children
		else
		{
			// Find inorder successor
			tree_node<data_type> * successor = NULL;
			tree_node<data_type> * parent = NULL;
			// Find the inorder successor to the tree_node
			successor = inorder( root, parent );
			// Set the left of the parent of the inorder
			// to the inorder's right, it will have no left
			// if it did then it wouldn't be the inorder
			successor->left = root->left;
			if ( parent )
				parent->left = successor->right;
			// Make suer we arent seting the right to ourself
			if ( parent && parent->right != root->right )
				successor->right = root->right;
			root = successor;
		}
		// Delete
		delete [] del->key;
		delete del;
		--in_tree;
		return true;
	}
	// Binary search
	else if ( 0 < strcmp( root->key, key ) )
	{
		return remove( key, root->left );
	}
	return remove( key, root->right );
}



/*
	Class: tree
	Method: inorder
	Use: Finds the inorder successor to a node in the tree
	Input: The node whose inorder successor is being found
		and the node which will point to the parent of the successor 
	Output: The successor and the parent of the successor is also set
*/
template <typename data_type>
tree_node<data_type> * tree<data_type>::inorder( tree_node<data_type> * root, tree_node<data_type> * & parent )
{
	// Goes right then all the way left and returns
	if ( !root )
	{
		return NULL;
	}
	if ( root->right )
	{
		parent = root;
		root = root->right;
	}
	while ( root->left )
	{
		parent = root;
		root = root->left;
	}
	return root;
}


