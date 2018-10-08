#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Structure representing a neighbour in a graph
typedef struct Neighbour {
	int neighbour;
	int weight;
	struct Neighbour *nextNeighbour;
	//struct Neighbour *previousNeighbour;
} Neighbour;

/*
 * Create an empty neighbour
 */
void neighbour_create(Neighbour *self, int neighbour, int weight);

/*
 * Destroy a list
 */
void neighbour_list_destroy(Neighbour *self);

/*
 * Add an element in the list at the beginning
 */
void neighbour_add_front(Neighbour *self, Neighbour *front);

/*
 * Remove an element in the list (preserving the order)
 */
void neighbour_remove(Neighbour *self, int nbNode);

/*
 * Print a neighbour to stdout
 */
void neighbour_dump(Neighbour *self);

/*
 * Print a list
 */
void list_dump(Neighbour *self);

#endif // LIST_H
