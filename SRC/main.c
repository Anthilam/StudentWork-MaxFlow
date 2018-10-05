
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

	char *string = malloc(sizeof(char *));
	int res = 0, cmp = 1;
	printf("Possibles commands for this programm : \n");
	printf("\t create graph : graph creation\n");
	printf("\t load graph : graph loading from a text file\n");
	printf("\t add neighbour : insertion of a neighbour in the graph\n");
	printf("\t add edge : insertion of an edge in the graph\n");
	printf("\t remove neighbour : deletion of a neighbour from the graph\n");
	printf("\t remove edge : deletion of an edge from the graph\n");
	printf("\t view graph : graph display\n");
   	printf("\t save graph : graph saving in the text format\n");
	printf("\t help : print this text \n");
	printf("\t quit : exit the program\n");

	
	while(cmp != 0){
		res = scanf("%s",string);
		if(res == 0)
		{
			printf("The character given is not a string !\n");
			exit(0);
		}
		cmp = strcmp(string,"quit");
		

	}
	



}
