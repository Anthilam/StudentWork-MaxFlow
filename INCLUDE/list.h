#ifndef neighbour_H
#define neighbour_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Structure representing a neighbour in a graph
struct Neighbour {
	int neighbour;
	int weight;
	struct Neighbour *nextNeighbour;
	struct Neighbour *previousNeighbour;
};

/*
 * Create an empty neighbour
 */
void neighbour_create(struct Neighbour *self, int neighbour, int weight);

/*
 * Init a neighbour
 */
void neighbour_init(struct Neighbour *self, int value, struct Neighbour *previous, struct Neighbour *next);

/*
 * Destroy a neighbour
 */
void neighbour_destroy(struct Neighbour *self);

/*
 * Destroy a list
 */
void neighbour_list_destroy(struct Neighbour *self);

/*
 * Add an element in the list at the beginning
 */
void neighbour_add_front(struct Neighbour *self, struct Neighbour *front);

/*
 * Remove an element in the list (preserving the order)
 */
void neighbour_remove(struct Neighbour *self, size_t index);

/*
 * Print a neighbour to stdout
 */
void neighbour_dump(struct Neighbour *self);

/*
 * Print a list
 */
void list_dump(struct Neighbour *self);

#endif // LIST_H
