#ifndef TREE_H
#define TREE_H

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct tree_node;

struct tree {
  struct tree_node *root;
};

/*
 * Create an empty tree
 */
void tree_create(struct tree *self);

/*
 * Destroy a tree
 */
void tree_node_destroy(struct tree_node *self);
void tree_destroy(struct tree *self);

/*
 * Tell if a value is present in the tree
 */
bool tree_node_contains(const struct tree_node *self, int value);
bool tree_contains(const struct tree *self, int value);

/*
 * Insert a value into a tree
 */
struct tree_node *tree_node_insert(struct tree_node *self, int value);
void tree_insert(struct tree *self, int value);

/*
 * Remove a value from a tree
 */
struct tree_node *tree_node_delete_minimum(struct tree_node *self, struct tree_node **min);
struct tree_node *tree_node_delete(struct tree_node *self);
struct tree_node *tree_node_remove(struct tree_node *self, int value);
void tree_remove(struct tree *self, int value);

/*
 * Tell if a tree is empty or not
 */
bool tree_is_empty(const struct tree *self);

/*
 * Return the size of a tree
 */
size_t tree_node_size(const struct tree_node *self);
size_t tree_size(const struct tree *self);

/*
 * Return the height of a tree
 */
size_t tree_node_height(const struct tree_node *self);
size_t tree_height(const struct tree *self);

/*
 * Other functions not used here
 */
typedef void (*tree_func_t)(int value, void *user_data);

void tree_walk_pre_order(const struct tree *self, tree_func_t func, void *user_data);

void tree_walk_in_order(const struct tree *self, tree_func_t func, void *user_data);

void tree_walk_post_order(const struct tree *self, tree_func_t func, void *user_data);

void tree_dump(const struct tree *self);

#ifdef __cplusplus
}
#endif

#endif /* TREE_H */
