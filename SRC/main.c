
/***********************************************************************
 * Programme : main.c
 *
 * auteur :    Timothée Guy, Reynald Barbeaut
 *
 * resume :    Some algorithm about graph
 *
 * date :      21/02/05
 *
 ***********************************************************************
 */


#include "main.h"

/*---------------------*/
/* Main programm */
/*---------------------*/

int main() {
	Graph g;
	bool was_created = false, isDirected, symmetric;
	char *string = malloc(sizeof(char *));
	char *string2 = malloc(sizeof(char *));
	int res = 0, res2 = 0, cmp = 1, size, nodeStart, nodeEnd, weight;
	char help[512];
	strcpy(help,"Possibles commands for this programm : \n");
	strcat(help, "\t1: create graph : graph creation\n");
	strcat(help,"\t2: load graph : graph loading from a text file\n");
	strcat(help,"\t3: add neighbour : insertion of a neighbour in the graph\n");
	strcat(help,"\t4: add edge : insertion of an edge in the graph\n");
	strcat(help,"\t5: remove neighbour : deletion of a neighbour from the graph\n");
	strcat(help,"\t6: remove edge : deletion of an edge from the graph\n");
	strcat(help,"\t7: view graph : graph display\n");
	strcat(help,"\t8: save graph : graph saving in the text format\n");
	strcat(help,"\t9: help : display know commands\n");
	strcat(help,"\t10: quit : exit the program\n");


	printf("%s",help);

	while(cmp != 0){
		printf("Enter the number of the command you want to execute : \n");
		res = scanf("%s",string);
		printf("%s", string);
		if(res == 0)
		{
			printf("The character given is not a string !\n");
		}else{
			switch (atoi(string)){
				case 1:
					if(was_created){
						destroy_graph(&g);
					}
					was_created = true;
					printf("\nIs the graph directed ? 1:Yes, 2:No\n");
					res2 = scanf("%s",string2);

					if(atoi(string2) == 1){
						isDirected = true;
					}else if(atoi(string2) == 2){
						isDirected = false;
					}else{
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}

					printf("Which size the graph is ?\n");

					res2 = scanf("%s",string2);

					if(atoi(string2) == 0 || res2 == 0){
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					size = atoi(string2);
					create_graph(&g, size, isDirected);

					printf("Graph created.\n");
					break;

				case 2:
					if(was_created){
						destroy_graph(&g);
					}
					was_created = true;
					list_saved_file(&g);
					printf("Graph loaded.\n");
						
				break;

				case 3:
					if(!was_created){
						printf("Error the graph must be created before !\n");
						exit(1);
					}
					printf("Enter the number of the node you want to add :\n");

					res2 = scanf("%s",string2);

					if(atoi(string2) == 0 || res2 == 0){
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					
					add_node(&g, atoi(string2));
					printf("Node added.\n");
				break;

				case 4:
					if(!was_created){
						printf("Error the graph must be created before !\n");
						exit(1);
					}
					printf("Enter the number of the starting node of the edge :\n");

					res2 = scanf("%s",string2);

					if(atoi(string2) == 0 || res2 == 0){
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					nodeStart = atoi(string2);

					printf("Enter the number of the ending node of the edge :\n");

					res2 = scanf("%s",string2);

					if(atoi(string2) == 0 || res2 == 0){
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					nodeEnd = atoi(string2);
					
					if(!isDirected){
						symmetric = true;
					}else{
						printf("\nIs the edge symmetric ? 1:Yes, 2:No\n");
						res2 = scanf("%s",string2);

						if(atoi(string2) == 1){
							symmetric = true;
						}else if(atoi(string2) == 2){
							symmetric = false;
						}else{
							printf("Error the given answer wasn't a number.\n");
							exit(1);
						}

					}

					printf("Enter the weight of the edge :\n");

					res2 = scanf("%s",string2);

					if(atoi(string2) == 0 || res2 == 0){
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					weight = atoi(string2);
					add_edge(&g,nodeStart,nodeEnd,symmetric,weight);
					printf("Edge added.\n");
				break;
				
				case 5:
					if(!was_created){
						printf("Error the graph must be created before !\n");
						exit(1);
					}
					printf("Enter the number of the node you want to remove :\n");

					res2 = scanf("%s",string2);

					if(atoi(string2) == 0 || res2 == 0){
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					
					remove_node(&g, atoi(string2));
					printf("Node removed.\n");
				break;
				
				case 6:
					if(!was_created){
						printf("Error the graph must be created before !\n");
						exit(1);
					}

					printf("Enter the number of the starting node of the edge :\n");

					res2 = scanf("%s",string2);

					if(atoi(string2) == 0 || res2 == 0){
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					nodeStart = atoi(string2);

					printf("Enter the number of the ending node of the edge :\n");

					res2 = scanf("%s",string2);

					if(atoi(string2) == 0 || res2 == 0){
						printf("Error the given answer wasn't a number.\n");
						exit(1);
					}
					nodeEnd = atoi(string2);
					remove_edge(&g,nodeStart,nodeEnd);
					printf("Edge removed.\n");
				break;

				case 7:	
					if(!was_created){
						printf("Error the graph must be created before !\n");
						exit(1);
					}
					view_graph(&g,stdout,false);
				break;

				case 8:
					if(!was_created){
						printf("Error the graph must be created before !\n");
						exit(1);
					}
					save_graph(&g);
					printf("Graph saved.\n");
				break;

				case 9:
					printf("%s",help);
				break;
				
				case 10:
					cmp = 0;
				break;

				default:
					printf("Error unknown command !\n");
					printf("%s",help);
			}
		}		
	}
	if(was_created){
		destroy_graph(&g);
	}
}
