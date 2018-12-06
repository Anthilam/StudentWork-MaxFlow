

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef GRAPH_LINKEDLIST_H
#define GRAPH_LINKEDLIST_H


struct list_node;

typedef struct linkedlist {
    struct list_node *first;
};

/*
 * Create an empty list
 */
void linkedlist_create(struct linkedlist *self);

/*
 * Destroy a list
 */
void linkedlist_node_destroy(struct list_node *self);

void linkedlist_destroy(struct linkedlist *self);


/*
 * Print a linkedlist to stdout
 */
void linkedlist_node_dump(struct list_node *self);

void linkedlist_dump(const struct linkedlist *self);

/*
 * Add an element in the linkedlist at the end
 */
void linkedlist_node_add_back(struct list_node *self, int value);

void linkedlist_add_back(struct linkedlist *self, int value);


/*
 * Insert an element in the linkedlist (preserving the order)
 */
void linkedlist_insert(struct linkedlist *self, int value, size_t index);

/*
 * Remove an element in the linkedlist (preserving the order)
 */
void linkedlist_remove(struct linkedlist *self, size_t index);

/*
 * Get a pointer to the element at the specified index in the list
 */
int linkedlist_get(const struct linkedlist *self, size_t index);

/*
 * Tell if the linkedlist is empty
 */
bool linkedlist_is_empty(const struct linkedlist *self);

/*
 * Get the size of the list
 */
size_t linkedlist_size(const struct linkedlist *self);

/*
 * Search for an element in the list.
 */
size_t linkedlist_node_search(const struct list_node *self, int value);

/*
 * Transform the parent array to a path thanks to ending and starting node
 */
void linkedlist_parent_to_path(struct linkedlist *self, int * parent, int nodeStart, int nodeEnd);

/*
 * Search if a value is in the linked list
 */
size_t linkedlist_search(const struct linkedlist *self, int value);






#endif //GRAPH_LINKEDLIST_H
