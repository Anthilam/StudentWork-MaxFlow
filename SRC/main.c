
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

/* Main for test */
int main()
{
	Graph g;

	create_graph(&g, 10);

	add_node(&g, 0);
	add_node(&g, 1);
	add_node(&g, 25);
	add_node(&g, 5);
	add_node(&g, 1);
	add_node(&g, 2);
	add_node(&g, 10);
	add_node(&g, 3);

	add_edge(&g, -1, 1, false, 2);
	add_edge(&g, 1, 9959, false, 9);
	add_edge(&g, 5, 1, false, 69);
	add_edge(&g, 1, 2, true, 100);
	add_edge(&g, 1, 10, false, 25);
	add_edge(&g, 2, 10, true, 50);
	add_edge(&g, 3, 2, true, 6565);

	view_graph(&g,stdout);

	remove_node(&g, -1);
	remove_node(&g, 65);
	remove_node(&g, 1);
	remove_node(&g, 1);

	view_graph(&g,stdout);

	remove_node(&g, 10);
	remove_node(&g, 5);

	view_graph(&g,stdout);

	destroy_graph(&g);
}


/*---------------------*/
/* Main programm */
/*---------------------*/

/*int main() {
	char *string = malloc(sizeof(char *));
	int res = 0, cmp = 1;
	char help[512];
	strcpy(help,"Possibles commands for this programm : \n");
	strcat(help, "\t create graph : graph creation\n");
	strcat(help,"\t load graph : graph loading from a text file\n");
	strcat(help,"\t add neighbour : insertion of a neighbour in the graph\n");
	strcat(help,"\t add edge : insertion of an edge in the graph\n");
	strcat(help,"\t remove neighbour : deletion of a neighbour from the graph\n");
	strcat(help,"\t remove edge : deletion of an edge from the graph\n");
	strcat(help,"\t view graph : graph display\n");
	strcat(help,"\t save graph : graph saving in the text format\n");
	strcat(help,"\t help : display know commands\n");
	strcat(help,"\t quit : exit the program\n");


	printf("%s",help);

	while(cmp != 0){
		res = scanf("%s[^\n]",string);
		clean_stdin();
		if(res == 0)
		{
			printf("The character given is not a string !\n");
		}else{
			cmp = strcmp(string,"quit");

			if(strcmp(string,"create graph") == 0){
				//Create graph
				printf("Graph created.\n");
			}else if(strcmp(string,"load graph") == 0){
				//Load graph
				printf("Graph loaded.\n");
			}else if(strcmp(string,"add neighbour") == 0){
				//Add neighbour
				printf("Neighbour added.\n");
			}else if(strcmp(string,"add edge") == 0){
				//Add edge
				printf("Edge added.\n");
			}else if(strcmp(string,"remove neighbour") == 0){
				//Remove neighbour
				printf("Neighbour removed.\n");
			}else if(strcmp(string,"remove edge") == 0){
				//Remove edge
				printf("Edge removed.\n");
			}else if(strcmp(string,"view graph") == 0){
				//Print graph to stdout
			}else if(strcmp(string,"save graph") == 0){
				//Save graph
				printf("Graph saved.\n");
			}else if(strcmp(string,"help") == 0){
				printf("%s",help);
			}else{
				printf("Error unknown command !\n");
				printf("%s",help);
			}
		}
	}
}*/
