#include "list.h"

struct list_node {
  int value;
  struct list_node *next;
  // struct list_node *prev;
};

/*
 * Create an empty list
 */
void list_create(struct list *self) {
  self->first = NULL;
}

/*
 * Destroy a list
 */
void list_node_destroy(struct list_node *self) {
  if (self->next != NULL) {
    list_node_destroy(self->next);
  }
  free(self);
}

void list_destroy(struct list *self) {
  if (self->first != NULL) {
    list_node_destroy(self->first);
  }
  self->first = NULL;
}

/*
 * Compare the list to an array (data and size)
 */
bool list_equals(const struct list *self, const int *data, size_t size) {
  struct list_node *l = self->first;
  int i = 0;
  while (l != NULL) {
    if (data[i] == l->value) {
      l = l->next;
      ++i;
    }
    else {
      return false;
    }
  }

  if (i == size) {
    return true;
  }
  return false;
}

/*
 * Print a list to stdout
 */
void list_node_dump(struct list_node *self) {
  if (self != NULL) {
    printf("%d ", self->value);
    if (self->next != NULL) {
      list_node_dump(self->next);
    }
  }
}

void list_dump(const struct list *self) {
  printf("( ");
  list_node_dump(self->first);
  printf(" )\n");
}

/*
 * Add an element in the list at the end
 */
void list_node_add_back(struct list_node *self, int value) {
  if (self->next == NULL) {
    struct list_node *l = malloc(sizeof(struct list_node));
    l->value = value;
    l->next = NULL;
    self->next = l;
  }
  else {
    list_node_add_back(self->next, value);
  }
}

void list_add_back(struct list *self, int value) {
  if (self->first == NULL) {
    self->first = malloc(sizeof(struct list_node));
    self->first->value = value;
    self->first->next = NULL;
  }
  else {
    list_node_add_back(self->first, value);
  }
}

/*
 * Add an element in the list at the beginning
 */
void list_add_front(struct list *self, int value) {
  struct list_node *l = malloc(sizeof(struct list_node));
  l->value = value;
  l->next = self->first;
  self->first = l;
}

/*
 * Insert an element in the list (preserving the order)
 */
void list_insert(struct list *self, int value, size_t index) {
  if (index == 0) {
    struct list_node *l = malloc(sizeof(struct list_node));
    l->value = value;
    l->next = self->first;
    self->first = l;
  }
  else {
    int counter = 1;
    struct list_node *curr = self->first;
    while (counter < index && curr->next != NULL) {
      curr = curr->next;
      ++counter;
    }

    struct list_node *l = malloc(sizeof(struct list_node));
    l->value = value;
    l->next = curr->next;
    curr->next = l;
  }
}

/*
 * Remove an element in the list (preserving the order)
 */
void list_remove(struct list *self, size_t index) {
  if (index == 0) {
    struct list_node *l = self->first->next;
    free(self->first);
    self->first = l;
  }
  else {
    int counter = 1;
    struct list_node *curr = self->first;
    while (counter < index && curr->next != NULL) {
      curr = curr->next;
      ++counter;
    }

    struct list_node *l = curr->next->next;
    free(curr->next);
    curr->next = l;
  }
}

/*
 * Get a pointer to the element at the specified index in the list
 */
int *list_get(const struct list *self, size_t index) {
  if (self->first != NULL) {
    struct list_node *l = self->first;
    for (size_t i = 0; i < index; ++i) {
            l = l->next;
    }
    return &l->value;
  }
  return 0;
}

/*
 * Tell if the list is empty
 */
bool list_is_empty(const struct list *self) {
  if (self->first != NULL) {
    return false;
  }
  return true;
}

/*
 * Get the size of the list
 */
size_t list_size(const struct list *self) {
  size_t i = 0;
  if (self->first != NULL) {
    struct list_node *l = self->first;
    while(l != NULL) {
      ++i;
      l = l->next;
    }
  }
  return i;
}

/*
 * Search for an element in the list.
 */
size_t list_node_search(const struct list_node *self, int value) {
  if (self == NULL) {
    return 0;
  }
  if (self->value == value) {
    return 0;
  }

  return 1 + list_node_search(self->next, value);
}

size_t list_search(const struct list *self, int value) {
  return list_node_search(self->first, value);
}

/*
 * Import an array in a list
 */
void list_import(struct list *self, const int *other, size_t size) {
  list_destroy(self);
  for (int i = 0; i < size; ++i) {
    list_add_back(self, other[i]);
  }
}

/*
 * Tell if a list is sorted
 */
bool list_is_sorted(const struct list *self) {
  if (self->first != NULL) {
    struct list_node *curr = self->first;
    int n = curr->value;
    while (curr->next != NULL) {
      int m = curr->next->value;
      if (m < n) {
        return false;
      }
      n = m;
      curr = curr->next;
    }
  }
  return true;
}

/*
 * Sort a list with merge sort
 */
struct list_node* merge(struct list_node *a, struct list_node *b) {
  if (a == NULL) {
     return b;
  }
  if (b == NULL) {
     return a;
  }

  struct list_node *result = NULL;
  if (a->value <= b->value) {
     result = a;
     result->next = merge(a->next, b);
  }
  else {
     result = b;
     result->next = merge(a, b->next);
  }
  return(result);
}

void split(struct list_node *source, struct list_node **frontRef, struct list_node **backRef) {
  if (source==NULL || source->next==NULL) {
    *frontRef = source;
    *backRef = NULL;
  }
  else {
    struct list_node* fast;
    struct list_node* slow;

    slow = source;
    fast = source->next;

    while (fast != NULL)
    {
      fast = fast->next;
      if (fast != NULL)
      {
        slow = slow->next;
        fast = fast->next;
      }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
  }
}

void merge_sort(struct list_node **headRef) {
  struct list_node* head = *headRef;
  struct list_node* a;
  struct list_node* b;

  if ((head == NULL) || (head->next == NULL))
  {
    return;
  }

  split(head, &a, &b);
  merge_sort(&a);
  merge_sort(&b);
  *headRef = merge(a, b);
}

void list_merge_sort(struct list *self) {
  merge_sort(&self->first);
}
