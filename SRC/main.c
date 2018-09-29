
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
	struct Neighbour zero, first, second, third, empty;
	neighbour_create(&first);
	neighbour_create(&second);
	neighbour_create(&third);
	neighbour_create(&zero);
	neighbour_create(&empty);


	third.neighbour=3;
	third.weight=3;
	zero.neighbour=1;
	zero.weight=1;
	first.neighbour = 1;
	first.weight = 4;
	second.neighbour = 2;
	second.weight = 3;
	first.nextNeighbour = &second;


	second.previousNeighbour = &first;

	list_dump(&second);
	printf("\n");

	neighbour_destroy(&first);

	list_dump(&second);
	printf("\n");

	printf("Back :");
	neighbour_add_back(&second,&third);

	list_dump(&second);
	printf("\n");


	printf("Front: ");
	neighbour_add_front(&second,&zero);
	list_dump(&second);
	printf("\n");

	neighbour_list_destroy(&second);
	printf("Destroy :");
	list_dump(&second);
	printf("\n");

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
    
