#ifndef NEIGHBOUR_H
#define NEIGHBOUR_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Neighbour {
	int neighbour, weight;
	struct Neighbour *nextNeighbour;
	struct Neighbour *previousNeighbour;
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
 * Destroy a list
 */
void neighbour_destroy(struct Neighbour *self);

/*
* Go to first neighbour
*/
void neighbour_go_first(struct Neighbour *self, struct Neighbour *empty);

/*
 * Add an element in the list at the end
 */
void neighbour_add_back(struct Neighbour *self, int value, int weight);

/*
 * Add an element in the list at the beginning
 */
void neighbour_add_front(struct Neighbour *self, int value);

/*
 * Insert an element in the list (preserving the order)
 */
void neighbour_insert(struct Neighbour *self, int value, size_t index);

/*
 * Remove an element in the list (preserving the order)
 */
void neighbour_remove(struct Neighbour *self, size_t index);

/*
 * Get a pointer to the element at the specified index in the list
 */
int *neighbour_get(const struct Neighbour *self, size_t index);

/*
 * Tell if the list is empty
 */
bool neighbour_is_empty(const struct Neighbour *self);

/*
 * Get the size of the list
 */
size_t neighbour_size(const struct Neighbour *self);

/*
 * Search for an element in the list.
 */
size_t neighbour_search(const struct Neighbour *self, int value);

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


#ifdef __cplusplus
}
#endif

#endif // LIST_H
