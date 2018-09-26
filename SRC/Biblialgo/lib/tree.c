#include "tree.h"

struct tree_node {
  int value;
  struct tree_node *left;
  struct tree_node *right;
};

/*
 * Create an empty tree
 */
void tree_create(struct tree *self) {
  self->root = NULL;
}

/*
 * Destroy a tree
 */
void tree_node_destroy(struct tree_node *self) {
  if (self->left != NULL) {
    tree_node_destroy(self->left);
  }
  if (self->right != NULL) {
    tree_node_destroy(self->right);
  }
  free(self);
}

void tree_destroy(struct tree *self) {
  if (self->root != NULL) {
    tree_node_destroy(self->root);
  }
}

/*
 * Tell if a value is present in the tree
 */
bool tree_node_contains(const struct tree_node *self, int value) {
  if (self == NULL) {
    return false;
  }
  if (value < self->value) {
    return tree_node_contains(self->left, value);
  }
  if (value > self->value) {
    return tree_node_contains(self->right, value);
  }
  return true;
}

bool tree_contains(const struct tree *self, int value) {
  return tree_node_contains(self->root, value);
}

/*
 * Insert a value into a tree
 */
struct tree_node *tree_node_insert(struct tree_node *self, int value) {
  if (self == NULL) {
    struct tree_node *t = malloc(sizeof(struct tree_node));
    t->left = t->right = NULL;
    t->value = value;
    self = t;
  }
  if (value < self->value) {
    self->left = tree_node_insert(self->left, value);
    return self;
  }
  if (value > self->value) {
    self->right = tree_node_insert(self->right, value);
    return self;
  }
  return self;
}

void tree_insert(struct tree *self, int value) {
  if (self->root == NULL) {
    struct tree_node *t = malloc(sizeof(struct tree_node));
    t->left = t->right = NULL;
    t->value = value;
    self->root = t;
  }
  else {
    self->root = tree_node_insert(self->root, value);
  }
}

/*
 * Remove a value from a tree
 */
struct tree_node *tree_node_delete_minimum(struct tree_node *self, struct tree_node **min) {
  if (self->left == NULL) {
    struct tree_node *right = self->right;
    self->right = NULL;
    *min = self;
    return right;
  }
  self->left = tree_node_delete_minimum(self->left, min);
  return self;
}

struct tree_node *tree_node_delete(struct tree_node *self) {
  struct tree_node *left = self->left;
  struct tree_node *right = self->right;
  free(self);
  self = NULL;
  if (left == NULL && right == NULL) {
    return NULL;
  }
  if (left == NULL) {
    return right;
  }
  if (right == NULL) {
    return left;
  }
  right = tree_node_delete_minimum(right, &self);
  self->left = left;
  self->right = right;
  return self;
}

struct tree_node *tree_node_remove(struct tree_node *self, int value) {
  if (self == NULL) {
    return NULL;
  }
  if (value < self->value) {
    self->left = tree_node_remove(self->left, value);
    return self;
  }
  if (value > self->value) {
    self->right = tree_node_remove(self->right, value);
    return self;
  }
  return tree_node_delete(self);
}

void tree_remove(struct tree *self, int value) {
  self->root = tree_node_remove(self->root, value);
}

/*
 * Tell if a tree is empty or not
 */
bool tree_is_empty(const struct tree *self) {
  if (self->root == NULL) {
    return true;
  }
  return false;
}

/*
 * Return the size of a tree
 */
size_t tree_node_size(const struct tree_node *self) {
  if (self == NULL) {
    return 0;
  }
  if (self->right == NULL && self->left == NULL) {
    return 1;
  }
  return 1 + tree_node_size(self->left) + tree_node_size(self->right);
}

size_t tree_size(const struct tree *self) {
  return tree_node_size(self->root);
}

/*
 * Return the height of a tree
 */
size_t tree_node_height(const struct tree_node *self) {
  if (self == NULL) {
    return 0;
  }
  return 1 + tree_node_height(self->left) + tree_node_height(self->right);
}

size_t tree_height(const struct tree *self) {
  return tree_node_height(self->root);
}

/*
 * Other functions not used here
 */
void tree_walk_pre_order(const struct tree *self, tree_func_t func, void *user_data)  {

}

void tree_walk_in_order(const struct tree *self, tree_func_t func, void *user_data) {

}

void tree_walk_post_order(const struct tree *self, tree_func_t func, void *user_data) {

}

void tree_dump(const struct tree *self) {

}
