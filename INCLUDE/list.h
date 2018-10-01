#ifndef node_H
#define node_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Structure representing a node in a graph
struct node {
	int n;
	int weight;
	struct node *nextnode;
	struct node *previousnode;
};

/*
 * Create an empty node
 */
void node_create(struct node *self);

/*
 * Init a node
 */
void node_init(struct node *self, int value, struct node *previous, struct node *next);

/*
 * Destroy a node
 */
void node_destroy(struct node *self);

/*
 * Destroy a list
 */
void node_list_destroy(struct node *self);

/*
 * Help to destroy a list
 */
void node_list_destroy_help(struct node *self);

/*
* Go to first node
*/
void node_go_first(struct node *self, struct node *empty);

/*
 * Add an element in the list at the end
 */
void node_add_back(struct node *self, struct node *back);

/*
 * Add an element in the list at the beginning
 */
void node_add_front(struct node *self, struct node *front);

/*
 * Insert an node between two node
 */
void node_insert(struct node *self, struct node *previous, struct node *next);

/*
 * Remove an element in the list (preserving the order)
 */
void node_remove(struct node *self, size_t index);

/*
 * Print a node to stdout
 */
void node_dump(struct node *self);

/*
 * Print a list
 */
void list_dump(struct node *self);

/*
 * Help to print a list
 */
void list_dump_help(struct node *self);

#endif // LIST_H
