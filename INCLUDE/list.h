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
	struct Neighbour *nextneighbour;
	struct Neighbour *previousneighbour;
};

/*
 * Create an empty neighbour
 */
void neighbour_create(struct Neighbour *self);

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
 * Help to destroy a list
 */
void neighbour_list_destroy_help(struct Neighbour *self);

/*
* Go to first neighbour
*/
void neighbour_go_first(struct Neighbour *self, struct Neighbour *empty);

/*
 * Add an element in the list at the end
 */
void neighbour_add_back(struct Neighbour *self, struct Neighbour *back);

/*
 * Add an element in the list at the beginning
 */
void neighbour_add_front(struct Neighbour *self, struct Neighbour *front);

/*
 * Insert an neighbour between two neighbour
 */
void neighbour_insert(struct Neighbour *self, struct Neighbour *previous, struct Neighbour *next);

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

/*
 * Help to print a list
 */
void list_dump_help(struct Neighbour *self);

#endif // LIST_H
