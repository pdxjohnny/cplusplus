/*
	Author: John Andersen
	Date: 03/19/2015
	Class: CS 163, Portland State University
	Assignment: Homework 5
	Description: Class to create a graph where
		data items are vertexes and they can be
		connectied by edges methods
*/



/*
	Class: graph
	Method: Constructor
	Use: None
	Input: None
	Output: None
*/
template <typename vert_data_type, typename edge_data_type>
graph< void( vert_data_type, edge_data_type ) >::graph()
{
}



/*
	Class: graph
	Method: Destructor
	Use: None
	Input: None
	Output: None
*/
template <typename vert_data_type, typename edge_data_type>
graph< void( vert_data_type, edge_data_type ) >::~graph()
{
}



/*
	Class: graph
	Method: insert_vertex
	Use: Inserts a vertex with its data into thte graph
	Input: The vertex name and data
	Output: None
*/
template <typename vert_data_type, typename edge_data_type>
int graph< void( vert_data_type, edge_data_type ) >::insert_vertex( char * name, const vert_data_type & to_add )
{
	vertex< vert_data_type > * add = get_vertex( name );
	add->data = to_add;
	return 1;
}



/*
	Class: graph
	Method: insert_edge
	Use: Creates a edge connection between two vertexes
	Input: The names of the vertexes to connect and the data
		that is in the connection, the "weight" of the edge
	Output: 1 for success, hopefully
*/
template <typename vert_data_type, typename edge_data_type>
int graph< void( vert_data_type, edge_data_type ) >::insert_edge( char * current_vertex, char * to_attach, const edge_data_type & to_add )
{
	vertex< vert_data_type > * curr_vertex = get_vertex( current_vertex );
	vertex< vert_data_type > * attach_vertex = get_vertex( to_attach );
	char edge_name [ 255 ];
	sprintf( edge_name, "%s_%s", current_vertex, to_attach );
	edge< edge_data_type > * add_edge = & edges[ edge_name ];
	add_edge->adjacent = attach_vertex;
	add_edge->data = to_add;
	add_edge->next = NULL;
	if ( !curr_vertex->head )
	{
		curr_vertex->head = add_edge;
	}
	else
	{
		edge< edge_data_type > * walk = ( edge< edge_data_type > * )curr_vertex->head;
		while ( walk->next )
		{
			walk = walk->next;
		}
		walk->next = add_edge;
	}
	return 1;
}



/*
	Class: graph
	Method: adjacent
	Use: Finds the adjacent given the index in the ll
	Input: Vertex key and indes in vertex connection array
	Output: Data of connected vertex
*/
template <typename vert_data_type, typename edge_data_type>
vert_data_type & graph< void( vert_data_type, edge_data_type ) >::adjacent( char * key_value, int index )
{
	edge< edge_data_type > * walk = ( edge< edge_data_type > * )get_vertex( key_value )->head;
	return ( ( vertex< vert_data_type > * )edge_index( walk, index, 0 )->adjacent )->data;
}



/*
	Class: graph
	Method: edge_index
	Use: Finds the edge_index using recursion
	Input: Pointer to edge and index on in the list
	Output: Edge that is at the correct index
*/
template <typename vert_data_type, typename edge_data_type>
edge< edge_data_type > * graph< void( vert_data_type, edge_data_type ) >::edge_index( edge< edge_data_type > * walk, int index, int on )
{
	if ( !walk )
	{
		return NULL;
	}
	else if ( index == on )
	{
		return walk;
	}
	return edge_index( walk->next, index, on + 1 );
}



/*
	Class: graph
	Method: connection
	Use: Finds the data for a edge at a given index
	Input: The vertex key and indes
	Output: Edge's data
*/
template <typename vert_data_type, typename edge_data_type>
edge_data_type & graph< void( vert_data_type, edge_data_type ) >::connection( char * key_value, int index )
{
	edge< edge_data_type > * walk = ( edge< edge_data_type > * )get_vertex( key_value )->head;
	return edge_index( walk, index, 0 )->data;
}



/*
	Class: graph
	Method: path_length
	Use: Find the length of a depth first path
	Input: The end vertex current vertex and tree of
		what has been visted
	Output: Depth of path as int
*/
template <typename vert_data_type, typename edge_data_type>
int graph< void( vert_data_type, edge_data_type ) >::path_length( vertex< vert_data_type > * to, edge< edge_data_type > * walk, tree<int> & been_to )
{
	char addr [ 100 ];
	sprintf( addr, "%p", walk );
	if ( !been_to.contains( addr ) )
	{
		been_to.insert( addr );
	}
	else
	{
		return 0;
	}
	if ( !walk || !to )
	{
		return 0;
	}
	else if ( walk->adjacent == to )
	{
		return 1;
	}
	else
	{
		int in_chain = path_length( to, ( edge< edge_data_type > * )( ( vertex< vert_data_type > * )walk->adjacent)->head, been_to );
		if ( in_chain )
		{
			return 1 + in_chain;
		}
		else
		{
			in_chain = path_length( to, walk->next, been_to );
			if ( in_chain )
				return in_chain;
			else
				return 0;
		}
	}
	return 0;
}



/*
	Class: graph
	Method: path_length
	Use: Finds the path depth first through the graph
	Input: Start and endpoints of the path
	Output: Length of path
*/
template <typename vert_data_type, typename edge_data_type>
int graph< void( vert_data_type, edge_data_type ) >::path_length( char * from, char * to )
{
	tree<int> been_to;
	vertex< vert_data_type > * end = get_vertex( to );
	edge< edge_data_type > * walk = ( edge< edge_data_type > * )get_vertex( from )->head;
	int path = path_length( end, walk, been_to );
	if ( !path )
		return 0;
	return 1 + path;
}



/*
	Class: graph
	Method: edge_path
	Use: Fills an array with edges for a path
	Input: Pionter to the vertex to find, head of the
		edge list, what we've been to, the index of
		the array that we are on.
	Output: The lengh of the path and the array is filled
*/
template <typename vert_data_type, typename edge_data_type>
int graph< void( vert_data_type, edge_data_type ) >::edge_path( vertex< vert_data_type > * to, edge< edge_data_type > * walk, tree<int> & been_to, int & index, edge< edge_data_type > ** array )
{
	char addr [ 100 ];
	sprintf( addr, "%p", walk );
	if ( !been_to.contains( addr ) )
	{
		been_to.insert( addr );
	}
	else
	{
		return 0;
	}
	if ( !walk || !to )
	{
		return 0;
	}
	else if ( walk->adjacent == to )
	{
		array[ index ] = walk;
		--index;
		return 1;
	}
	else
	{
		int in_chain = edge_path( to, ( edge< edge_data_type > * )( ( vertex< vert_data_type > * )walk->adjacent)->head, been_to, index, array );
		if ( in_chain )
		{
			array[ index ] = walk;
			--index;
			return 1 + in_chain;
		}
		else
		{
			in_chain = edge_path( to, walk->next, been_to, index, array );
			if ( in_chain )
				return in_chain;
			else
				return 0;
		}
	}
	return 0;
}



/*
	Class: graph
	Method: path
	Use: Array of vertex data created from finding a path
	Input: Start and endpoints of the path
	Output: Array of points that aare connected
*/
template <typename vert_data_type, typename edge_data_type>
vert_data_type * graph< void( vert_data_type, edge_data_type ) >::path( char * from, char * to )
{
	int path = path_length( from, to );
	if ( !path )
		return NULL;
	int index = path;
	--index;
	tree<int> been_to;
	edge< edge_data_type > * array [ path ];
	vertex< vert_data_type > * start = get_vertex( from );
	vertex< vert_data_type > * end = get_vertex( to );
	edge< edge_data_type > * walk = ( edge< edge_data_type > * )start->head;
	edge_path( end, walk, been_to, index, array );
	vert_data_type * final = new vert_data_type [ path ];
	for (int i = path - 1; i > 0; --i)
	{
		final[ i ] = ( ( vertex< vert_data_type > * )array[ i ]->adjacent)->data;
	}
	final[ 0 ] = start->data;
	return final;
}



/*
	Class: graph
	Method: path_edges
	Use: Array of edge data created from finding a path
	Input: Start and endpoints of the path
	Output: Array of edges connecting the points
*/
template <typename vert_data_type, typename edge_data_type>
edge_data_type * graph< void( vert_data_type, edge_data_type ) >::path_edges( char * from, char * to )
{
	int path = path_length( from, to );
	if ( !path )
		return NULL;
	int index = path;
	--index;
	tree<int> been_to;
	edge< edge_data_type > * array [ path ];
	vertex< vert_data_type > * start = get_vertex( from );
	vertex< vert_data_type > * end = get_vertex( to );
	edge< edge_data_type > * walk = ( edge< edge_data_type > * )start->head;
	edge_path( end, walk, been_to, index, array );
	edge_data_type * final = new edge_data_type [ path - 1 ];
	for (int i = path - 1; i > 0; --i)
	{
		final[ i - 1 ] = array[ i ]->data;
	}
	return final;
}



/*
	Class: graph
	Method: display_all
	Use: Loops through all items and displays the keys
	Input: None
	Output: To screen all keys
*/
template <typename vert_data_type, typename edge_data_type>
int graph< void( vert_data_type, edge_data_type ) >::display_all(void)
{
	for (int i = 0; i < all.size(); ++i)
	{
		std::cout << all.key( i ) << '\n';
	}
	return all.size();
}



/*
	Class: graph
	Method: get_vertex
	Use: Gets a vertexs and sets values if nesicary
	Input: Vertex key
	Output: Vertex foud for key
*/
template <typename vert_data_type, typename edge_data_type>
vertex< vert_data_type > * graph< void( vert_data_type, edge_data_type ) >::get_vertex(char * key_value)
{
	vertex< vert_data_type > * curr_vertex = NULL;
	if ( !all.contains( key_value ) )
	{
		curr_vertex = & all[ key_value ];
		curr_vertex->head = NULL;
	}
	else
	{
		curr_vertex = & all[ key_value ];
	}
	return curr_vertex;
}


