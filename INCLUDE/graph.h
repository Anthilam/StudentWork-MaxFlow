#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "list.h"

// Adjacency list structure
typedef struct Adj {
  Neighbour *list;
} Adj;

// Graph structure
typedef struct Graph {
  bool isDirected;
  int nbMaxNodes;
  Adj *adjList;
} Graph;

/*
 * Create a graph
 */
void create_graph(Graph *g, int nbNodes);

/*
 * Destroy a graph
 */
void destroy_graph(Graph *g);

/*
 * Add a node to a graph
 */
void add_node(Graph *g, int nbNode);

/*
 * Remove a node of a graph
 */
void remove_node(Graph *g, int node);

/*
 * Add an edge to a graph
 */
void add_edge(Graph *g, int nodeStart, int nodeEnd, bool symmetric, int weight);

/*
 * Destroy an edge of a graph
 */
void remove_edge(Graph *g, int nodeStart, int nodeEnd);

/*
 * Save the graph in a text format
 */
void save_graph(Graph *g);

/*
 * Load a graph
 */
void load_graph(Graph *g, char *path);

/*
 * View the graph in the terminal
 */
void view_graph(Graph *g, FILE *out);

#endif // GRAPH_H
