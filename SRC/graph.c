#include "graph.h"

/*
 * Create a graph
 */
void create_graph(Graph *g, int nbNodes)
{
  printf("INFO:\tCreating graph..\n");

  g->isDirected = false;    // Set the graph to undirected by default
  g->nbMaxNodes = nbNodes;  // Set the max number of nodes

  printf("\tAllocating memory for adjacency lists..\n");

  // Allocate memory for adjacency lists
  g->adjList = malloc(sizeof(Adj) * nbNodes);
  if (g->adjList == NULL)
  {
    printf("ERROR:\tmalloc() failed, stopping..");
    exit(1);
  }

  for (int i = 0; i < nbNodes; ++i)
  {
    g->adjList[i].list = NULL;
  }

  printf("\tGraph created!\n");
}

/*
 * Destroy a graph
 */
void destroy_graph(Graph *g)
{
  printf("INFO:\tDestroying graph..\n");

  // Destroy existent adjacency lists
  for (int i = 0; i < g->nbMaxNodes; ++i)
  {
    if (g->adjList[i].list != NULL)
    {
      printf("\tDestroying list for node %d..\n", i+1);
      neighbour_list_destroy(g->adjList[i].list);
    }
  }

  // Free the adjacency array
  free(g->adjList);

  printf("\tGraph destroyed!\n");
}

/*
 * Add a node to a graph
 */
void add_node(Graph *g, int nbNode)
{
  printf("INFO:\tAdding node..\n");
  int realNbNode = nbNode - 1;

  // Check the node number
  if (nbNode <= 0 || nbNode > g->nbMaxNodes)
  {
    printf("ERROR:\tNode %d not added, %d is out of range\n\tMin. node = 1, Max. node = %d\n", nbNode, nbNode, g->nbMaxNodes);
  }
  // Check if the node already exists
  else if (g->adjList[realNbNode].list != NULL)
  {
    printf("ERROR:\tNode %d not added, node %d already exists\n", nbNode, nbNode);
  }
  // Add the node
  else
  {
    // Initialize the adjacency list of the node
    g->adjList[realNbNode].list = malloc(sizeof(Neighbour));
    if (g->adjList[realNbNode].list == NULL)
    {
      printf("ERROR:\tmalloc() failed, stopping..");
      exit(1);
    }

    // Add a "negative" neighbour to specify the existence of the node
    neighbour_create(g->adjList[realNbNode].list, -1, 0);

    printf("\tNode %d has been added to the graph!\n", nbNode);
  }
}

/*
 * Remove a node of a graph
 */
void remove_node(Graph *g, int node)
{
  // TODO
  printf("WIP!");
}

/*
 * Add an edge to the graph
 */
void add_edge(Graph *g, int nodeStart, int nodeEnd, bool symmetric, int weight)
{
  printf("INFO:\tAdding edge..\n");
  int realNodeStart = nodeStart - 1;
  int realNodeEnd = nodeEnd - 1;

  // Check the range of the starting node
  if (nodeStart <= 0 || nodeStart > g->nbMaxNodes)
  {
    printf("ERROR:\tEdge not added, node %d doesn't exists\n", nodeStart);
  }
  // Check the range of the ending node
  else if (nodeEnd <= 0 || nodeEnd > g->nbMaxNodes)
  {
    printf("ERROR:\tEdge not added, node %d doesn't exists\n", nodeEnd);
  }
  // Check the existence of the starting node
  else if (g->adjList[realNodeStart].list == NULL)
  {
    printf("ERROR:\tEdge not added, node %d doesn't exists\n\tMin. node = 1, Max. node = %d\n", nodeStart, g->nbMaxNodes);
  }
  // Check the existence of the ending node
  else if (g->adjList[realNodeEnd].list == NULL)
  {
    printf("ERROR:\tEdge not added, node %d doesn't exists\n\tMin. node = 1, Max. node = %d\n", nodeEnd, g->nbMaxNodes);
  }
  // Add the edge
  else
  {
    // If the edge is symmetric
    if (symmetric)
    {
      // Create neighbours
      Neighbour neighbourStart, neighbourEnd;
      neighbour_create(&neighbourStart, realNodeStart, weight);
      neighbour_create(&neighbourEnd, realNodeEnd, weight);

      // Add neighbours to the front of the list
      neighbour_add_front(g->adjList[realNodeStart].list, &neighbourEnd);
      neighbour_add_front(g->adjList[realNodeEnd].list, &neighbourStart);
    }
    // If the edge isn't symmetric
    else
    {
      // Create neighbour
      Neighbour neighbourEnd;
      neighbour_create(&neighbourEnd, realNodeEnd, weight);

      // Add neighbour to the front of the list
      neighbour_add_front(g->adjList[realNodeStart].list, &neighbourEnd);

      // Change the graph to directed
      g->isDirected = true;
    }

    printf("\tThe edge between %d and %d has been added!\n", nodeStart, nodeEnd);
  }
}

/*
 * Destroy an edge of a graph
 */
void remove_edge(Graph *g, int nodeStart, int nodeEnd)
{
  // TODO
  printf("WIP!");
}

/*
 * Save the graph in a text format
 */
void save_graph(Graph *g, char *path)
{
  // TODO
  printf("WIP!");
}

/*
 * Load a graph
 */
void load_graph(Graph *g, char *path)
{
  // TODO
  printf("WIP!");
}

/*
 * View the graph in the terminal
 */
void view_graph(Graph *g)
{
  printf("\n----- VIEW GRAPH -----\n- directed: %s\n- nbMaxNodes: %d\n", g->isDirected ? "true" : "false", g->nbMaxNodes);

  printf("- Graph structure:\n");
  for (int i = 0; i < g->nbMaxNodes; ++i)
  {
    printf("\tNode %d: ", i+1);
    list_dump(g->adjList[i].list);
    printf("\n");
  }
  printf("\n");
}
