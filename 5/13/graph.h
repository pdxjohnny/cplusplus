/*
	Author: John Andersen
	Date: 03/19/2015
	Class: CS 163, Portland State University
	Assignment: Homework 5
	Description: Class to create a graph where
		data items are vertexes and they can be
		connectied by edges
*/



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
		// None
		graph();
		// None
		~graph();
		// Inserts a vertex with its data into thte graph
		int insert_vertex( char * name, const vert_data_type & to_add );
		// Creates a edge connection between two vertexes
		int insert_edge( char * current_vertex, char * to_attach, const edge_data_type & to_add );
		// Finds the adjacent given the index in the ll
		vert_data_type & adjacent( char * key_value, int index );
		// Finds the edge_index using recursion
		edge< edge_data_type > * edge_index( edge< edge_data_type > * walk, int index, int on );
		// Finds the data for a edge at a given index
		edge_data_type & connection( char * key_value, int index );
		// Find the length of a depth first path
		int path_length( vertex< vert_data_type > * to, edge< edge_data_type > * walk, tree<int> & been_to );
		// Finds the path depth first through the graph
		int path_length( char * from, char * to );
		// Fills an array with edges for a path
		int edge_path( vertex< vert_data_type > * to, edge< edge_data_type > * walk, tree<int> & been_to, int & index, edge< edge_data_type > ** array );
		// Array of vertex data created from finding a path
		vert_data_type * path( char * from, char * to );
		// Array of edge data created from finding a path
		edge_data_type * path_edges( char * from, char * to );
		// Loops through all items and displays the keys
		int display_all(void);
		// Gets a vertexs and sets values if nesicary
		vertex< vert_data_type > * get_vertex(char * key_value );
private:
		// Holds vertexes
		tree< vertex< vert_data_type > > all;
		// Holds edges
		tree< edge< edge_data_type > > edges;
};

#include "graph.cpp"
