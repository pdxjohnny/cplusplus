


/*
	Class: graph
	Method: Constructor
	Use: 
	Input: 
	Output: 
*/
template <typename vert_data_type, typename edge_data_type>
graph< void( vert_data_type, edge_data_type ) >::graph()
{
}



/*
	Class: graph
	Method: Destructor
	Use: 
	Input: 
	Output: 
*/
template <typename vert_data_type, typename edge_data_type>
graph< void( vert_data_type, edge_data_type ) >::~graph()
{
}



/*
	Class: graph
	Method: insert_vertex
	Use: 
	Input: 
	Output: 
*/
template <typename vert_data_type, typename edge_data_type>
int graph< void( vert_data_type, edge_data_type ) >::insert_vertex( char * name, const vert_data_type & to_add )
{
	vertex< vert_data_type > * add = get_vertex( name );
	add->data = to_add;
}



/*
	Class: graph
	Method: insert_edge
	Use: 
	Input: 
	Output: 
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
}



/*
	Class: graph
	Method: find_adjacent
	Use: Finds the adjacent given the index in the ll
	Input: 
	Output: 
*/
template <typename vert_data_type, typename edge_data_type>
vert_data_type & graph< void( vert_data_type, edge_data_type ) >::adjacent( char * key_value, int index )
{
	edge< edge_data_type > * walk = ( edge< edge_data_type > * )get_vertex( key_value )->head;
	return ( ( vertex< vert_data_type > * )edge_index( walk, index, 0 )->adjacent )->data;
}



/*
	Class: graph
	Method: find_adjacent
	Use: Finds the edge_index using recursion
	Input: 
	Output: 
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
	Method: find_adjacent
	Use: 
	Input: 
	Output: 
*/
template <typename vert_data_type, typename edge_data_type>
edge_data_type & graph< void( vert_data_type, edge_data_type ) >::connection( char * key_value, int index )
{
	edge< edge_data_type > * walk = ( edge< edge_data_type > * )get_vertex( key_value )->head;
	return edge_index( walk, index, 0 )->data;
}



/*
	Class: graph
	Method: display_adjacent
	Use: 
	Input: 
	Output: 
*/
template <typename vert_data_type, typename edge_data_type>
int graph< void( vert_data_type, edge_data_type ) >::display_adjacent(char * key_value)
{
	edge< edge_data_type > * walk = ( edge< edge_data_type > * )get_vertex( key_value )->head;
	for ( int i = 0; walk; ++i )
	{
		walk = walk->next;
	}
}



/*
	Class: graph
	Method: path_length
	Use: 
	Input: 
	Output: 
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
	Use: 
	Input: 
	Output: 
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
	Use: 
	Input: 
	Output: 
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
	Use: 
	Input: 
	Output: 
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
	Use: 
	Input: 
	Output: 
*/
template <typename vert_data_type, typename edge_data_type>
edge_data_type * graph< void( vert_data_type, edge_data_type ) >::path_edges( char * from, char * to )
{
}



/*
	Class: graph
	Method: all_paths_recurse
	Use: 
	Input: 
	Output: 
*/
template <typename vert_data_type, typename edge_data_type>
int graph< void( vert_data_type, edge_data_type ) >::all_paths_recurse( char * key_value, tree<char *> & been_to )
{
	vertex< vert_data_type > * vert;
	char * key;
	edge< edge_data_type > * walk = get_vertex( key_value )->head;
	for ( int i = 0; walk; ++i )
	{
		vert = ( vertex< vert_data_type > * )walk->adjacent;
		if ( !been_to.contains( key ) )
		{
			all_paths_recurse( key, been_to );
			been_to.remove( key );
		}
		been_to.insert( key );
		walk = walk->next;
	}
}



/*
	Class: graph
	Method: display_all
	Use: 
	Input: 
	Output: 
*/
template <typename vert_data_type, typename edge_data_type>
int graph< void( vert_data_type, edge_data_type ) >::display_all(void)
{
	for (int i = 0; i < all.size(); ++i)
	{
		std::cout << all.key( i ) << '\n';
	}
}



/*
	Class: graph
	Method: get_vertex
	Use: 
	Input: 
	Output: 
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


