#include "graph.h"

/*
 * Create a graph
 */
void create_graph(Graph *g, int nbNodes, bool isDirected)
{
  printf("INFO:\tCreating graph..\n");

  g->isDirected = isDirected;    // Set the graph to undirected by default
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
  else if (is_in_graph(g,nbNode))
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
* Check is a node is in the graph
*/
bool is_in_graph(Graph *g, int nbNode){
	printf("INFO:\tChecking node..\n");
  int realNbNode = nbNode - 1;

  // Check the node number
  if (nbNode <= 0 || nbNode > g->nbMaxNodes)
  {
    printf("ERROR:\tNode %d not added, %d is out of range\n\tMin. node = 1, Max. node = %d\n", nbNode, nbNode, g->nbMaxNodes);
  }

	if (g->adjList[realNbNode].list != NULL)
	{
		return true;
	}
	return false;
}

/*
 * Remove a node of a graph
 */
void remove_node(Graph *g, int node)
{
  printf("INFO:\tRemoving node %d..\n", node);
  int realNbNode = node - 1;

  // Check the node number
  if (node <= 0 || node > g->nbMaxNodes)
  {
    printf("ERROR:\tNode %d not deleted, %d is out of range\n\tMin. node = 1, Max. node = %d\n", node, node, g->nbMaxNodes);
  }
  else if (g->adjList[realNbNode].list != NULL)
  {
    for (int i = 0; i < g->nbMaxNodes; ++i)
    {
      if (g->adjList[i].list != NULL && i != realNbNode)
      {
        printf("\tRemoving node from list %d\n", i);
        neighbour_remove(g->adjList[i].list, realNbNode);
      }
    }

    printf("\tDestroying node %d\n", node);
    neighbour_list_destroy(g->adjList[realNbNode].list);
    g->adjList[realNbNode].list = NULL;

    printf("\tNode %d removed!\n", node);
  }
  else {
    printf("ERROR:\tNode %d doesn't exists\n", node);
  }
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
  printf("INFO:\tRemoving edge between %d and %d..\n", nodeStart, nodeEnd);
  int realNodeStart = nodeStart - 1;
  int realNodeEnd = nodeEnd - 1;

  // Check the starting node number
  if (nodeStart <= 0 || nodeStart > g->nbMaxNodes)
  {
    printf("ERROR:\tNode %d is out of range\n\tMin. node = 1, Max. node = %d\n", nodeStart, g->nbMaxNodes);
  }
  // Check the ending node number
  else if (nodeEnd <= 0 || nodeEnd > g->nbMaxNodes)
  {
    printf("ERROR:\tNode %d is out of range\n\tMin. node = 1, Max. node = %d\n", nodeEnd, g->nbMaxNodes);
  }
  // Check the existence of the starting node
  else if (g->adjList[realNodeStart].list == NULL)
  {
    printf("ERROR:\tNode %d doesn't exists\n", nodeStart);
  }
  // Check the existence of the ending node
  else if (g->adjList[realNodeEnd].list == NULL)
  {
    printf("ERROR:\tNode %d doesn't exists\n", nodeEnd);
  }
  // Remove the edge between the two nodes
  else
  {
    printf("\tRemoving node from list %d\n", realNodeStart);
    neighbour_remove(g->adjList[realNodeStart].list, realNodeEnd);

    if (!g->isDirected)
    {
      printf("\tRemoving node from list %d\n", realNodeEnd);
      neighbour_remove(g->adjList[realNodeEnd].list, realNodeStart);
    }

    printf("\tEdge between %d and %d removed!\n", nodeStart, nodeEnd);
  }
}


/*
* Open the directory and list all the saved graph
*/
void list_saved_file(Graph *g){
	DIR *rep;	
	size_t i = 0;
	char *string = malloc(sizeof(char *));
	char path[32] = "./SAVE/";
	int res = 0;

	//We open the directory where the saved graph are stored
	rep = opendir("./SAVE");
	struct dirent *lecture;
	printf("Here is the list of the available saved graph.\n");
	while ((lecture = readdir(rep)))
	{
		//We list the saved file
		if(strcmp(".",lecture->d_name) != 0 && strcmp("..",lecture->d_name) != 0 && strcmp(".blank",lecture->d_name) != 0)
		{
			printf("File number : %zu ; File name : %s\n",i, lecture->d_name);
			i++;
		}		
	}
	printf("Enter the complete (filename.txt) name of the file that you want to open :\n");
	res = scanf("%s",string);
	strcat(path,string);
	if(res == 0)
	{
		printf("The character given is not a string !\n");
	}else
	{
		//If the name of the file is correct we load it
		load_graph(g, path);
	}
}

/*
 * Save the graph in a text format
 */
void save_graph(Graph *g)
{
	char *name = malloc(sizeof(char *) * 10);
	char *file = malloc(sizeof(char *) * 10);
	int res = 0, res2 = 0;
	bool isSaved = false;
	FILE *savedFile;

  strcpy(file, "./SAVE/");

	while (!isSaved && res == 0)
  {
    // Ask user input
		printf("Please, write down the name of the graph :\n");
		res = scanf("%s", name);

		if (res != 0)
    {
      // Open the file descriptor to save the graph
			strcat(name, ".txt");
			strcat(file, name);
			savedFile = fopen(file, "w");

			if (savedFile == NULL)
			{
		    printf("ERROR:\tError when opening file!\n");
		 		exit(1);
			}

      // "Print" the graph in the file descriptor specified before
			view_graph(g, savedFile, true);
			res2 = fclose(savedFile);

			if (res2 == 0)
      {
				isSaved = true;
			}
		}
    else
    {
			printf("ERROR:\tThe given name wasn't a string\n");
		}
	}

  free(name);
  free(file);
	printf("INFO:\tThe graph was successfully saved!\n");
}

/*
 * Load a graph
 */
void load_graph(Graph *g, char *path)
{
	char line[128];
	int size = 0, lineNumber = 0, inNode, c = 1, outNode, weight, ret;
	char *position = malloc(sizeof(char *));
	char *direction = malloc(sizeof(char *));
	char *token, *subtoken;
	char *saveptr1, *saveptr2;

	//Loading file where graph is stored
	FILE *fp = fopen(path, "r");
	if(fp == NULL){
		printf("Error the file wasn't found !\n");
		exit(1);
	}
	//Parsing each line of the file
	while(fgets(line, sizeof(line), fp)){
		position = strchr(line,'#');
		if(position == NULL){
			//Checking the number of the line
			switch (lineNumber){
				case 0 :
					//First real line is the size of the graph
					size = atoi(line);
					printf("%d\n",size);
					break;
			
			
				case 1 :
					//This line says if the graph is directed or not
					direction = strchr(line, 'y');
					if(direction != NULL){
						create_graph(g, size, true);
					}
			
					direction = strchr(line, 'n');
					if(direction != NULL){
						create_graph(g, size, false);
					}
					break;

				default :
					//Else we parse the lines which correspond to nodes
					if((inNode = atoi(line)) != 0){
						//We add starting nodes to the graph
						if(!is_in_graph(g,inNode)){
							add_node(g,inNode);
						}
					}
					token = strtok_r(line,":(),", &saveptr1);
					while (token != NULL)
    			{		
						//We juste wants ending nodes with their weigths
						direction = strchr(token, '/');
						if(direction != NULL)
						{
							subtoken = strtok_r(token, "/", &saveptr2);
							while(subtoken != NULL){
								if(c == 1)
								{
									outNode = atoi(subtoken);
									c++;
								}else
								{
									weight = atoi(subtoken);
									c--;
									//Adding ending nodes to the graph
									if(outNode != -1 && weight != 0)
									{
										if(!is_in_graph(g,outNode))
										{
											add_node(g,outNode);
										}
										//Adding the edges which are stored in the file
										add_edge(g, inNode, outNode, false, weight);
									}
								}
								subtoken = strtok_r(NULL, "/", &saveptr2);
							}
						}
						token = strtok_r(NULL, ":(),", &saveptr1);
					}
			}
			lineNumber ++;
		}		
	}
	ret = fclose(fp);
	if(ret != 0){
		printf("Error while closing file !.\n");
		exit(1);
	}
}

/*
 * View the graph in the terminal
 */
void view_graph(Graph *g, FILE *out, bool forSave)
{
  if(!forSave){
	fprintf(out, "----- VIEW GRAPH -----\n");
  }
  fprintf(out, "# maximum number of nodes\n%d\n#directed\n%s\n", g->nbMaxNodes, g->isDirected ? "y" : "n");

  fprintf(out,"# node: neighbours\n");
  for (int i = 0; i < g->nbMaxNodes; ++i)
  {
		if(g->adjList[i].list != NULL){
	    fprintf(out, "%d: ", i+1);
  	  list_dump(g->adjList[i].list,out);
  	  fprintf(out, "\n");
		}
  }
  if(!forSave){
    fprintf(out, "----------------------\n");
  }
}
