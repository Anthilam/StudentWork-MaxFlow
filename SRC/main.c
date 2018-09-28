
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
/* Programme principal */
/*---------------------*/

int main() {
	struct Neighbour first, second, empty;
	neighbour_create(&first);
	neighbour_create(&second);
	neighbour_create(&empty);

	first.neighbour = 1;
	first.weight = 4;
	second.neighbour = 2;
	second.weight = 3;
	first.nextNeighbour = malloc(sizeof(struct Neighbour));
	first.nextNeighbour = &second;

	printf("%d\n",first.neighbour);
	printf("%d\n",second.neighbour);

	second.previousNeighbour = malloc(sizeof(struct Neighbour));
	second.previousNeighbour = &first;
	//printf("%d\n",second.previousNeighbour->neighbour);
	list_dump(&second);
	

	/*
	printf("Possibles commands for this programm : \n");
	printf("\t create graph : graph creation\n");
	printf("\t load graph : graph loading from a text file\n");
	printf("\t add node : insertion of a node in the graph\n");
	printf("\t add edge : insertion of an edge in the graph\n");
	printf("\t remove node : deletion of a node from the graph\n");
	printf("\t remove edge : deletion of an edge from the graph\n");
	printf("\t view graph : graph display\n");
   	printf("\t save graph : graph saving in the text format\n");
	printf("\t quit : exit the program\n");
	*/


}
    
