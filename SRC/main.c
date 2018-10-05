
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
	neighbour_create(&first,1,1);
	neighbour_create(&second,2,2);
	neighbour_create(&third,3,3);
	neighbour_create(&zero,-1,0);
	neighbour_create(&empty,0,0);
	printf("Beginning of the programm :\n");

	printf("Front: ");
	neighbour_add_front(&zero,&third);
	neighbour_add_front(&third,&second);
	neighbour_add_front(&second,&first);

	list_dump(&first);
	printf("\n");

	neighbour_destroy(&first);

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
	printf("\t add neighbour : insertion of a neighbour in the graph\n");
	printf("\t add edge : insertion of an edge in the graph\n");
	printf("\t remove neighbour : deletion of a neighbour from the graph\n");
	printf("\t remove edge : deletion of an edge from the graph\n");
	printf("\t view graph : graph display\n");
   	printf("\t save graph : graph saving in the text format\n");
	printf("\t quit : exit the program\n");
	*/


}
