/***********************************************************************
 * Program :		graph.c
 *
 * Authors :		BARBEAUT Reynald, GUY Timothée Guy
 *
 * Resume :			Library for graph manipulation
 *
 ************************************************************************/


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

	// We open the directory where the saved graph are stored
	rep = opendir("./SAVE");
	struct dirent *lecture;
	printf("Here is the list of the available saved graph.\n");

	while ((lecture = readdir(rep)))
	{
		//We list the saved file
		if (strcmp(".", lecture->d_name) != 0 && strcmp("..", lecture->d_name) != 0 && strcmp(".blank", lecture->d_name) != 0)
		{
			printf("File number : %zu ; File name : %s\n", i, lecture->d_name);
			i++;
		}
	}

	printf("Enter the complete (filename.txt) name of the file that you want to open :\n");
	res = scanf("%s",string);
	strcat(path,string);

	if (res == 0)
	{
		printf("The character given is not a string !\n");
	}
	//If the name of the file is correct we load it
	else
	{
		load_graph(g, path);
	}

	if (closedir(rep) < 0)
	{
		printf("Error while closing SAVE folder\n");
	}
	free(string);
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

	// Loading file where graph is stored
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
  {
		printf("Error the file wasn't found !\n");
		exit(1);
	}

	// Parsing each line of the file
	while (fgets(line, sizeof(line), fp))
  {
		position = strchr(line,'#');
		if (position == NULL)
    {
			// Checking the number of the line
			switch (lineNumber)
      {
				case 0 :
					// First real line is the size of the graph
					size = atoi(line);
					printf("%d\n",size);
					break;
				case 1 :
					// This line says if the graph is directed or not
					direction = strchr(line, 'y');
					if (direction != NULL)
          {
						create_graph(g, size, true);
					}

					direction = strchr(line, 'n');
					if (direction != NULL)
          {
						create_graph(g, size, false);
					}
					break;
				default :
					// Else we parse the lines which correspond to nodes
					if ((inNode = atoi(line)) != 0)
          {
						// We add starting nodes to the graph
						if (!is_in_graph(g,inNode))
            {
							add_node(g,inNode);
						}
					}

					token = strtok_r(line,":(),", &saveptr1);

					while (token != NULL)
    			{
						// We juste wants ending nodes with their weigths
						direction = strchr(token, '/');
						if (direction != NULL)
						{
							subtoken = strtok_r(token, "/", &saveptr2);

							while (subtoken != NULL)
              {
								if (c == 1)
								{
									outNode = atoi(subtoken);
									c++;
								}
                else
								{
									weight = atoi(subtoken);
									c--;

									// Adding ending nodes to the graph
									if (outNode != -1 && weight != 0)
									{
										if (!is_in_graph(g,outNode))
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
	if (ret != 0)
  {
		printf("Error while closing file !.\n");
		exit(1);
	}
}

/*
 * View the graph in the terminal
 */
void view_graph(Graph *g, FILE *out, bool forSave)
{
  if (!forSave)
  {
	  fprintf(out, "----- VIEW GRAPH -----\n");
  }

  fprintf(out, "# maximum number of nodes\n%d\n#directed\n%s\n", g->nbMaxNodes, g->isDirected ? "y" : "n");

  fprintf(out,"# node: neighbours\n");
  for (int i = 0; i < g->nbMaxNodes; ++i)
  {
		if (g->adjList[i].list != NULL)
        {
	        fprintf(out, "%d: ", i+1);
  	        list_dump(g->adjList[i].list, out);
  	        fprintf(out, "\n");
		}
  }

  if (!forSave)
  {
    fprintf(out, "----------------------\n");
  }
}


/*
 * Check if there is a node between two nodes
 */
bool has_path_BFS(Graph *g, int nodeStart, int nodeEnd, struct linkedlist *path)
{
    if(nodeStart == nodeEnd)
    {
        linkedlist_add_back(path,nodeStart);
        return true;
    }
    size_t queueSize;
    int u,v;
    int *color = malloc(sizeof(int) * g->nbMaxNodes);
    int *d = malloc(sizeof(int) * g->nbMaxNodes);
    int *parent = malloc(sizeof(int) * g->nbMaxNodes);
    struct linkedlist *queue = malloc(sizeof(struct linkedlist));
    struct Neighbour *current, *next;

    for (int i = 0; i < g->nbMaxNodes; i++)
    {
        color[i] = 0;
        d[i] = -1;
        parent[i] = -1;
    }

    color[nodeStart-1] = 1;
    d[nodeStart] = 0;

    linkedlist_create(queue);
    linkedlist_add_back(queue,nodeStart-1);

    while(!linkedlist_is_empty(queue))
    {
        queueSize = linkedlist_size(queue);
        u = linkedlist_get(queue, queueSize-1);
        if(u == nodeEnd-1)
        {
            linkedlist_parent_to_path(path, parent, nodeStart-1, nodeEnd-1);
            linkedlist_destroy(queue);
            free(queue);
            free(color);
            free(d);
            free(parent);
            return true;
        }
        linkedlist_remove(queue,queueSize-1);

        current = g->adjList[u].list;
        next = g->adjList[u].list->nextNeighbour;

        while(current->neighbour != -1)
        {
            v = current->neighbour;
            if(color[v] == 0)
            {
                color[v] = 1;
                d[v] = d[u] + 1;
                parent[v] = u;
                linkedlist_add_back(queue,v);
            }
            current = next;
            next = current->nextNeighbour;
        }
        color[u] = 3;
    }
    linkedlist_destroy(queue);
    free(queue);
    free(color);
    free(d);
    free(parent);
    return false;
}


/*
* Check if there is a path between two nodes with DFS
*/
bool has_path_DFS(Graph *g, int nodeStart, int nodeEnd, struct linkedlist *path){
    int *color = malloc(sizeof(int) * g->nbMaxNodes);
    int *parent = malloc(sizeof(int) * g->nbMaxNodes);
    struct Neighbour *current, *next;
    int v;
    bool retour;
    for(int i = 0; i < g->nbMaxNodes; i++){
        color[i] = 0;
        parent[i] = -1;
    }
    color[nodeStart-1] = 1;

    current = g->adjList[nodeStart-1].list;
    next = g->adjList[nodeStart-1].list->nextNeighbour;

    while(current->neighbour != -1)
    {
        v = current->neighbour;
        if(color[v] == 0)
        {
            parent[v] = nodeStart - 1;
            retour = DFS_visit(g,nodeEnd,v,color, parent, path);
            if(retour)
            {
                for(int i = 0; i < g->nbMaxNodes; i++){
                    printf("%d - > %d \n",i+1,parent[i]+1);
                }
                linkedlist_parent_to_path(path, parent, nodeStart-1, nodeEnd-1);
                free(parent);
                free(color);
                return retour;
            }
        }

        current = next;
        next = current->nextNeighbour;
    }
    free(parent);
    free(color);
    return false;
}

/*
* Visit for the recursive method
*/
bool DFS_visit(Graph *g, int nodeEnd, int node, int * color, int * parent, struct linkedlist *path){
    struct Neighbour *current, *next;
    int v;
    bool retour;

    color[node] = 1;

    current = g->adjList[node].list;
    next = g->adjList[node].list->nextNeighbour;

    while(current->neighbour != -1)
    {
        v = current->neighbour;


        if(color[v] == 0)
        {
            parent[v] = node;

            if(v == nodeEnd-1)
            {
                return true;
            }

            retour = DFS_visit(g,nodeEnd,v,color,parent,path);
            if(retour)
            {
                return retour;
            }
        }

        current = next;
        next = current->nextNeighbour;
    }
    return false;
}
/*
* Check if there is a path between two nodes with Floyd-Warshall
*/
bool has_path_FloydWarshall(Graph *g, int nodeStart, int nodeEnd, struct linkedlist *path){
    int **M = malloc(sizeof(int *) * g->nbMaxNodes);
    int **prec = malloc(sizeof(int *) * g->nbMaxNodes);
    bool ret = false;
    struct Neighbour *current, *next;

    for(int i = 0; i < g->nbMaxNodes; i++)
    {
        M[i] = malloc((sizeof(int) * g->nbMaxNodes));
        prec[i] = malloc((sizeof(int) * g->nbMaxNodes));
    }

    for(int i = 0; i < g->nbMaxNodes; i++)
    {
        for(int j = 0; j < g->nbMaxNodes; j++)
        {
            M[i][j] = INT_MAX;
            prec[i][j] = (i!=j)?j:-1;
        }
    }


    for(int i = 0; i < g->nbMaxNodes; i++)
    {
        current = g->adjList[i].list;
        next = g->adjList[i].list->nextNeighbour;
        while(current->neighbour != -1)
        {
            M[i][current->neighbour] = current->weight;
            current = next;
            next = current->nextNeighbour;
        }

    }


    for(int z = 0; z < g->nbMaxNodes; z++)
    {
        for(int x = 0; x < g->nbMaxNodes; x++)
        {
            for(int y = 0; y < g->nbMaxNodes; y++)
            {
                if((M[x][z] != INT_MAX) && (M[z][y] != INT_MAX) && (M[x][z] + M[z][y] < M[x][y]))
                {
                    M[x][y] = M[x][z] + M[z][y];
                    prec[x][y] = prec[x][z];
                }
            }
        }
    }


    if(M[nodeStart-1][nodeEnd-1] == INT_MAX)
    {
        ret = false;
    }else{
        int k = nodeStart-1;
        do{
            linkedlist_add_back(path,k);
            k = prec[k][nodeEnd-1];
        }while(k != nodeEnd-1);
        linkedlist_add_back(path,k);
		ret = true;
    }

    for(int i = 0; i < g->nbMaxNodes; i++)
    {
        free(M[i]);
        free(prec[i]);
    }
    free(M);
    free(prec);
    return ret;

}

int ford_felkurson_algorithm(Graph *g, int nodeStart, int nodeEnd, int pathmode)
{
	// Init flow
	int flow = 0;

	// Init flow matrix
	int **flowMatrix = malloc(sizeof(int *) * g->nbMaxNodes);
	for (int i = 0; i < g->nbMaxNodes; i++)
	{
		flowMatrix[i] = malloc(sizeof(int) * g->nbMaxNodes);
		for (int j = 0; j < g->nbMaxNodes; j++)
		{
			flowMatrix[i][j] = 0;
		}
	}

	// Init path list
	linkedlist *path = malloc(sizeof(linkedlist));
	linkedlist_create(path);
	linkedlist *lastpath = malloc(sizeof(linkedlist));
	linkedlist_create(lastpath);

	// Copy the graph
	Graph g_residual;
	create_graph(&g_residual, g->nbMaxNodes, g->isDirected);
	for (int i = 1; i <= g->nbMaxNodes; i++)
	{
		add_node(&g_residual, i);
	}

	for (int i = 0; i < g->nbMaxNodes; i++)
	{
		Neighbour *node = g->adjList[i].list;
		while (node != NULL)
		{
			if (node->neighbour != -1)
			{
				add_edge(&g_residual, i+1, node->neighbour+1, false, node->weight);
			}

			node = node->nextNeighbour;
		}
	}

	view_graph(&g_residual, stdout, false);

	// Compute path
	bool has_path;

	if (pathmode == 1)
	{
		has_path = has_path_BFS(&g_residual, nodeStart, nodeEnd, path);
	}
	else if (pathmode == 2)
	{
		has_path = has_path_DFS(&g_residual, nodeStart, nodeEnd, path);
	}
	else
	{
		has_path = has_path_FloydWarshall(&g_residual, nodeStart, nodeEnd, path);
	}

	while (has_path)
	{
		printf("\nPATH:");
		linkedlist_dump(path);

		if (same_path(path, lastpath))
		{
			break;
		}

		// Check that residual capacity is > 0
		int min_residual_capacity = INT_MAX;
		bool residual_capacity_ok = compute_residual_capacity(&g_residual, path, flowMatrix, &min_residual_capacity);

		if (residual_capacity_ok)
		{
			// Update flow matrix
			update_flow_matrix(&g_residual, path, flowMatrix, &min_residual_capacity);

			struct list_node *l = path->first;
			if (l == NULL)
			{
				exit(1);
			}

			// Update the residual graph
			while (l->next != NULL)
			{
				// Update the first member of an edge
				Neighbour *first = g_residual.adjList[l->value].list;
				while (first != NULL)
				{
					if (first->neighbour == l->next->value)
					{
						int capacity = first->weight - flowMatrix[l->value][l->next->value];
						if (capacity > 0)
						{
							first->weightResidual = capacity;
						}
						else
						{
							remove_edge(&g_residual, l->value+1, l->next->value+1);
						}
					}

					first = first->nextNeighbour;
				}

				// Update the second member of the edge
				Neighbour *second = g_residual.adjList[l->next->value].list;
				int brek = 0;
				while (second != NULL)
				{
					if (second->neighbour == l->value)
					{
						if (second->weight > 0)
						{
							second->weightResidual = second->weight - flowMatrix[l->next->value][l->value];
							second->weight = second->weightResidual;

							Neighbour *firstagain = g_residual.adjList[l->value].list;
							while (firstagain != NULL)
							{
								if (firstagain->neighbour == l->next->value)
								{
									firstagain->weightResidual = -firstagain->weightResidual;
									firstagain->weight = firstagain->weightResidual;
									break;
								}

								firstagain = firstagain->nextNeighbour;
							}

							brek = 1;
							break;
						}
						else
						{
							remove_edge(&g_residual, l->next->value+1, l->value+1);
							add_edge(&g_residual, l->next->value+1, l->value+1, false, flowMatrix[l->next->value][l->value]);
							brek = 2;
							break;
						}
					}

					second = second->nextNeighbour;
				}

				if (brek == 0)
				{
					add_edge(&g_residual, l->next->value+1, l->value+1, false, flowMatrix[l->next->value][l->value]);
				}

				l = l->next;
			}

			view_graph(&g_residual, stdout, false);

			dump_flow_matrix(flowMatrix, g->nbMaxNodes);
		}

		linkedlist_destroy(lastpath);
		linkedlist_create(lastpath);

		struct list_node *cp = path->first;
		while (cp != NULL)
		{
			linkedlist_add_back(lastpath, cp->value);
			cp = cp->next;
		}

		linkedlist_destroy(path);
		linkedlist_create(path);

		//has_path = false;
		has_path = has_path_DFS(&g_residual, nodeStart, nodeEnd, path);
	}

	Neighbour *node = g->adjList[nodeStart-1].list;
	while (node != NULL)
	{
		if (node->neighbour >= 0)
		{
			flow += flowMatrix[nodeStart-1][node->neighbour];
		}
		node = node->nextNeighbour;
	}

	// Memory cleanup
	linkedlist_destroy(path);
	linkedlist_destroy(lastpath);
	free(path);
	free(lastpath);
	for (int i = 0; i < g->nbMaxNodes; i++)
	{
		free(flowMatrix[i]);
	}
	free(flowMatrix);
	destroy_graph(&g_residual);

	return flow;
}

bool compute_residual_capacity(Graph *g, linkedlist *path, int **flowMatrix, int *min_residual_capacity)
{
	struct list_node *l = path->first;
	int capacity;

	if (l == NULL)
	{
		return false;
	}

	// Loop path
	while (l->next != NULL)
	{
		// Get the proper edge
		Neighbour *node = g->adjList[l->value].list;
		while (node != NULL)
		{
			if (node->neighbour == l->next->value)
			{
				// Compute residual capacity of the current edge, if <= 0, no more flow can go through so return false
				capacity = node->weight - flowMatrix[l->value][l->next->value];
				if (capacity <= 0)
				{
					capacity = -capacity;
				}

				// If computed capacity is smaller than the last computed capacity
				if (capacity < *min_residual_capacity)
				{
					*min_residual_capacity = capacity;
				}
			}

			node = node->nextNeighbour;
		}

		l = l->next;
	}

	return true;
}

void update_flow_matrix(Graph *g, linkedlist *path, int **flowMatrix, int *min_residual_capacity)
{
	struct list_node *l = path->first;

	if (l == NULL)
	{
		return;
	}

	// Loop path
	while (l->next != NULL)
	{
		// Get the proper edge
		Neighbour *node = g->adjList[l->value].list;
		while (node != NULL)
		{
			if (node->neighbour == l->next->value)
			{
				if (flowMatrix[l->value][l->next->value] < 0)
				{
					// Send flow along the path
					flowMatrix[l->value][l->next->value] += *min_residual_capacity;
					// We updated a negative, we can improve the flow back
					flowMatrix[l->next->value][l->value] += *min_residual_capacity;
				}
				else
				{
					// Send flow along the path
					flowMatrix[l->value][l->next->value] += *min_residual_capacity;
					// The flow might be return later
					if (flowMatrix[l->next->value][l->value] > -flowMatrix[l->value][l->next->value])
					{
						flowMatrix[l->next->value][l->value] = -flowMatrix[l->value][l->next->value];
					}
				}
			}

			node = node->nextNeighbour;
		}

		l = l->next;
	}
}

void dump_flow_matrix(int **flowMatrix, int size)
{
	printf("flowMatrix :\n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("[%d]", flowMatrix[i][j]);
		}
		printf("\n");
	}
}

bool same_path(linkedlist *path, linkedlist *lastpath)
{
	struct list_node *a = path->first;
	struct list_node *b = lastpath->first;

	while (true)
	{
		if (a == NULL && b == NULL)
		{
			return true;
		}

		if ((a == NULL && b != NULL) || (a != NULL && b == NULL))
		{
			return false;
		}

		if (a->value != b->value)
		{
			return false;
		}

		a = a->next;
		b = b->next;
	}
}
