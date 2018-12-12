/***********************************************************************
 * Program :		main.c
 *
 * Authors :		BARBEAUT Reynald, GUY Timothée Guy
 *
 * Resume :			Main program, I/O with the user
 *
 ************************************************************************/

#include "main.h"

int main() {

	Graph g;
	bool was_created = false, isDirected, symmetric;
	char *string = malloc(sizeof(char *));
	char *string2 = malloc(sizeof(char *));
	int res = 0, res2 = 0, cmp = 1, size, nodeStart, nodeEnd, weight,method;

	// Create help string
	char *help = "\nPossibles commands for this programm : \n\t1: create graph : graph creation\n\t2: load graph : graph loading from a text file\n\t3: add neighbour : insertion of a neighbour in the graph\n\t4: add edge : insertion of an edge in the graph\n\t5: remove neighbour : deletion of a neighbour from the graph\n\t6: remove edge : deletion of an edge from the graph\n\t7: view graph : graph display\n\t8: save graph : graph saving in the text format\n\t9: help : display know commands\n\t10: compute : compute the maximum flow in a flow network\n\t11: quit : exit the program\n";

	// Welcome message
	printf("----------<>  IT'S A GRAPH!  <>----------\n- A program to create/modify/save graph -\n-----------------------------------------\n%s",help);

	while (cmp != 0)
	{
		printf("Enter the number of the command you want to execute : \n");
		res = scanf("%s", string);

		if (res == 0)
		{
			printf("The character given is not a string !\n");
		}
		else
		{
			switch (atoi(string))
			{
				// Create graph
				case 1:
					if (was_created)
					{
						destroy_graph(&g);
					}

					was_created = true;
					printf("\nIs the graph directed ? 1:Yes, 2:No\n");
					res2 = scanf("%s",string2);

					if (atoi(string2) == 1)
					{
						isDirected = true;
					}
					else if (atoi(string2) == 2)
					{
						isDirected = false;
					}
					else
					{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}

					printf("Which size the graph is ?\n");
					res2 = scanf("%s",string2);

					if (atoi(string2) == 0 || res2 == 0)
					{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}

					size = atoi(string2);
					create_graph(&g, size, isDirected);
					printf("Graph created.\n");

					break;
				// Load graph
				case 2:
					if (was_created)
					{
						destroy_graph(&g);
					}
					was_created = true;
					list_saved_file(&g);
					printf("Graph loaded.\n");
					break;
				// Add node
				case 3:
					if (!was_created)
					{
						printf("Error the graph must be created before !\n");
						exit(1);
					}

					printf("Enter the number of the node you want to add :\n");
					res2 = scanf("%s",string2);

					if (atoi(string2) == 0 || res2 == 0)
					{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					add_node(&g, atoi(string2));

					printf("Node added.\n");
					break;
				// Add edge
				case 4:
					if (!was_created)
					{
						printf("Error the graph must be created before !\n");
						exit(1);
					}

					printf("Enter the number of the starting node of the edge :\n");
					res2 = scanf("%s",string2);

					if (atoi(string2) == 0 || res2 == 0)
					{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					nodeStart = atoi(string2);

					printf("Enter the number of the ending node of the edge :\n");
					res2 = scanf("%s",string2);

					if (atoi(string2) == 0 || res2 == 0)
					{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					nodeEnd = atoi(string2);

					if (!isDirected)
					{
						symmetric = true;
					}
					else
					{
						printf("\nIs the edge symmetric ? 1:Yes, 2:No\n");
						res2 = scanf("%s",string2);

						if (atoi(string2) == 1)
						{
							symmetric = true;
						}
						else if (atoi(string2) == 2)
						{
							symmetric = false;
						}
						else
						{
							printf("Error the given answer wasn't a number.\n");
							exit(1);
						}
					}

					printf("Enter the weight of the edge :\n");
					res2 = scanf("%s",string2);

					if (atoi(string2) == 0 || res2 == 0)
					{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					weight = atoi(string2);

					add_edge(&g,nodeStart,nodeEnd,symmetric,weight);
					printf("Edge added.\n");
					break;
				// Remove node
				case 5:
					if (!was_created)
					{
						printf("Error the graph must be created before !\n");
						exit(1);
					}

					printf("Enter the number of the node you want to remove :\n");
					res2 = scanf("%s",string2);

					if (atoi(string2) == 0 || res2 == 0)
					{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}

					remove_node(&g, atoi(string2));
					printf("Node removed.\n");
					break;
				// Remove edge
				case 6:
					if (!was_created)
					{
						printf("Error the graph must be created before !\n");
						exit(1);
					}

					printf("Enter the number of the starting node of the edge :\n");
					res2 = scanf("%s",string2);

					if (atoi(string2) == 0 || res2 == 0)
					{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					nodeStart = atoi(string2);

					printf("Enter the number of the ending node of the edge :\n");
					res2 = scanf("%s",string2);

					if (atoi(string2) == 0 || res2 == 0)
					{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}

					nodeEnd = atoi(string2);
					remove_edge(&g,nodeStart,nodeEnd);
					printf("Edge removed.\n");
					break;
				// View graph
				case 7:
					if (!was_created)
					{
						printf("Error the graph must be created before !\n");
					}
					else
					{
						view_graph(&g,stdout,false);
					}
					break;
				// Save graph
				case 8:
					if (!was_created)
					{
						printf("Error the graph must be created before !\n");
						exit(1);
					}

					save_graph(&g);
					printf("Graph saved.\n");
					break;
				// Display help
				case 9:
					printf("%s",help);
					break;
				// Compute the maximum flow in a flow network
				case 10:
					if (!was_created)
					{
						printf("Error the graph must be created before !\n");
						exit(1);
					}

					printf("\t\tEnter the number of the algorithm you want to use :\n\t\t\t1 : BFS.\n\t\t\t2 : DFS.\n\t\t\t3 : Floyd-Warshall. \n");
					res2 = scanf("%s",string2);
					method = atoi(string2);
					if (method == 0 || res2 == 0)
					{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}

					if(method < 1 || method > 3)
					{
						printf("Error the given answer needs to be between 1 and 3.\n");
						exit(1);
					}


					printf("Enter the number of the starting node :\n");
					res2 = scanf("%s",string2);

					if (atoi(string2) == 0 || res2 == 0)
					{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}

					nodeStart = atoi(string2);

					printf("Enter the number of the ending node :\n");
					res2 = scanf("%s",string2);

					if (atoi(string2) == 0 || res2 == 0)
					{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}

					nodeEnd = atoi(string2);

					int flow = ford_felkurson_algorithm(&g, nodeStart, nodeEnd, method);
					if (method == 1)
					{
						printf("\nMaximum flow with BFS: %d\n", flow);
					}
					else if (method == 2)
					{
						printf("\nMaximum flow with DFS: %d\n", flow);
					}
					else
					{
						printf("\nMaximum flow with Floyd-Warshall: %d\n", flow);
					}

					break;
				// Exit program
				case 11:
					cmp = 0;
					break;
				// Wrong command
				default:
					printf("Error unknown command !\n");
					printf("%s",help);
			}
		}
	}

	// Memory cleanup
	if (was_created)
	{
		destroy_graph(&g);
	}
	free(string);
	free(string2);
}
