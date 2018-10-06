#include "graph.h"

/*
 * Create a graph
 */
void create_graph(struct Graph *g, int nbNodes)
{
  printf("INFO:\tCreating graph..\n");

  g->isDirected = false;    // Set the graph to undirected by default
  g->nbMaxNodes = nbNodes;  // Set the max number of nodes

  printf("\tAllocating memory for adjacency lists..\n");

  // Allocate memory for adjacency lists
  g->adjList = malloc(sizeof(struct Adj) * nbNodes);
  for (int i = 0; i < nbNodes; ++i)
  {
    g->adjList[i].list = NULL;
  }

  printf("\tGraph created!\n");
}

/*
 * Add a node to a graph
 */
void add_node(struct Graph *g, int nbNode)
{
  // Check the node number
  if (nbNode == 0 || nbNode > g->nbMaxNodes)
  {
    printf("Error:\tNode %d not added, node %d doesn't exists\n\tMin. node = 1, Max. node = %d\n", nbNode, nbNode, g->nbMaxNodes);
  }
  else
  {
    int realNbNode = nbNode - 1;

    // Check if the node already exists
    if (g->adjList[realNbNode].list != NULL)
    {
      printf("Error:\tNode %d not added, node %d already exists\n", nbNode, nbNode);
    }
    else
    {
      // Initialize the adjacency list of the node
      g->adjList[realNbNode].list = malloc(sizeof(struct Neighbour));

      // Add a "negative" neighbour to specify the existence of the node
      neighbour_create(g->adjList[realNbNode].list, -1, 0);

      printf("INFO:\tNode %d has been added to the graph\n", nbNode);
    }
  }
}

/*
 * Destroy a graph
 */
void destroy_graph(struct Graph *g)
{
  printf("INFO:\tDestroying graph..\n");

  // Destroy existent adjacency lists
  for (int i = 0; i < g->nbMaxNodes; ++i)
  {
    if (g->adjList[i].list != NULL)
    {
      printf("\tDestroying list for node %d..\n", i+1);
      neighbour_list_destroy(g->adjList[i].list);
      free(g->adjList[i].list);
    }
  }

  free(g->adjList);

  printf("\tGraph destroyed!\n");
}

/*
 * View the graph in the terminal
 */
void view_graph(struct Graph *g)
{
  printf("\n----- VIEW GRAPH -----\n- isDirected: %d\n- nbMaxNodes: %d\n", g->isDirected, g->nbMaxNodes);

  printf("- Graph structure:\n");
  for (int i = 0; i < g->nbMaxNodes; ++i)
  {
    printf("\tNode %d: ", i+1);
    list_dump(g->adjList[i].list);
    printf("\n");
  }
  printf("\n");
}
