#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"

// Graph structure
struct Graph {
  bool isDirected;
  int nbMaxNodes;
  struct Adj *adjList;
};

// Adjacency list structure
struct Adj {
  struct Neighbour *list;
};

/*
 * Create a graph
 */
void create_graph(struct Graph *g, int nbNodes);

/*
 * Load a graph
 */
void load_graph(char *path);

/*
 * Add a node to a graph
 */
void add_node(struct Graph *g, int nbNode);

/*
 * Add an edge to a graph
 */
void add_edge(struct Graph *g, int nodeStart, int nodeEnd, bool symmetric);

/*
 * Remove a node of a graph
 */
void remove_node(struct Graph *g, int node);

/*
 * Destroy an edge of a graph
 */
void remove_edge(struct Graph *g, int nodeStart, int nodeEnd);

/*
 * View the graph in the terminal
 */
void view_graph(struct Graph *g);

/*
 * Save the graph in a text format
 */
void save_graph(struct Graph *g);

/*
 * Destroy a graph
 */
void destroy_graph(struct Graph *g);

#endif // GRAPH_H