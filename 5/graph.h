#include "tree.h"



template <typename vert_data_type>
struct vertex
{
	vert_data_type data;
	void * head;
};



template <typename edge_data_type>
struct edge
{
	edge_data_type data;
	void * adjacent;
	edge< edge_data_type > * next;
};


template <typename> class graph;


template <typename vert_data_type, typename edge_data_type>
class graph< void( vert_data_type, edge_data_type ) >
{
public:
		graph( void );
		~graph( void );
		int insert_vertex( char * name, const vert_data_type & to_add );
		int insert_edge( char * current_vertex, char * to_attach, const edge_data_type & to_add );
		vert_data_type & adjacent( char * key_value, int index );
		edge< edge_data_type > * edge_index( edge< edge_data_type > * walk, int index, int on );
		edge_data_type & connection( char * key_value, int index );
		int display_adjacent( char * key_value );
		int path_length( vertex< vert_data_type > * to, edge< edge_data_type > * walk, tree<int> & been_to );
		int path_length( char * from, char * to );
		int edge_path( vertex< vert_data_type > * to, edge< edge_data_type > * walk, tree<int> & been_to, int & index, edge< edge_data_type > ** array );
		vert_data_type * path( char * from, char * to );
		edge_data_type * path_edges( char * from, char * to );
		int all_paths_recurse( char * key_value, tree<char *> & been_to );
		int display_all( void );
private:
		vertex< vert_data_type > * get_vertex( char * key_value );
		int graph_size;
		tree< vertex< vert_data_type > > all;
		tree< edge< edge_data_type > > edges;
};

#include "graph.cpp"
