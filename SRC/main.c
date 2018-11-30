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
	create_graph(&g, 5, true);
	add_node(&g, 1);
	add_node(&g, 2);
	add_node(&g, 3);
	add_node(&g, 4);
	add_node(&g, 5);

	add_edge(&g,1,3,false,2);
	add_edge(&g,1,2,false,2);
    add_edge(&g,1,1,false,2);
	add_edge(&g,3,5,false,1);


	add_edge(&g,2,3,false,2);
	add_edge(&g,2,1,false,2);
	add_edge(&g,2,2,false,2);
	add_edge(&g,3,5,false,1);



	add_edge(&g,3,4,false,1);
	add_edge(&g,3,1,false,1);
	add_edge(&g,3,2,false,1);
	add_edge(&g,3,3,false,1);
	add_edge(&g,3,5,false,1);


	view_graph(&g,stdout,false);
	struct linkedlist *path = malloc(sizeof(struct linkedlist));
	linkedlist_create(path);
	struct linkedlist *path2 = malloc(sizeof(struct linkedlist));
	linkedlist_create(path2);

	bool test = has_path_BFS(&g,1,4, path);
	bool test2 = has_path_DFS(&g,1,4,path2);
	if(test){
		printf("cébon c dedans lol\n");
		linkedlist_dump(path);
	}

	if(test2){
		printf("cébon c dedans 3 lol\n");
		linkedlist_dump(path2);
	}

	linkedlist_destroy(path);
	linkedlist_destroy(path2);
	free(path);
	free(path2);

	/*
	bool was_created = false, isDirected, symmetric;
	char *string = malloc(sizeof(char *));
	char *string2 = malloc(sizeof(char *));
	int res = 0, res2 = 0, cmp = 1, size, nodeStart, nodeEnd, weight;

	// Create help string
	char *help = "\nPossibles commands for this programm : \n\t1: create graph : graph creation\n\t2: load graph : graph loading from a text file\n\t3: add neighbour : insertion of a neighbour in the graph\n\t4: add edge : insertion of an edge in the graph\n\t5: remove neighbour : deletion of a neighbour from the graph\n\t6: remove edge : deletion of an edge from the graph\n\t7: view graph : graph display\n\t8: save graph : graph saving in the text format\n\t9: help : display know commands\n\t10: quit : exit the program\n";

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
				// Exit program
				case 10:
					cmp = 0;
					break;
				// Wrong command
				default:
					printf("Error unknown command !\n");
					printf("%s",help);
			}
		}
	}

	// Free memory
	if (was_created)
	{*/
		destroy_graph(&g);
	/*}
	free(string);
	free(string2);*/
}
