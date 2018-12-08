/***********************************************************************
 * Program :		linkedlist.c
 *
 * Authors :		BARBEAUT Reynald, GUY Timothée Guy
 *
 * Resume :			Library for linked list manipulation
 *
 ************************************************************************/

#include "linkedlist.h"

/*
 * Create an empty list
 */
void linkedlist_create(struct linkedlist *self) {
    self->first = NULL;
}

/*
 * Destroy a linkedlist
 */
void linkedlist_node_destroy(struct list_node *self) {
    if (self->next != NULL) {
        linkedlist_node_destroy(self->next);
    }
    free(self);
}

void linkedlist_destroy(struct linkedlist *self) {
    if (self->first != NULL) {
        linkedlist_node_destroy(self->first);
    }
    self->first = NULL;
}


/*
 * Print a linkedlist to stdout
 */
void linkedlist_node_dump(struct list_node *self) {
    if (self != NULL) {
        printf("%d ", self->value+1);
        if (self->next != NULL) {
            linkedlist_node_dump(self->next);
        }
    }
}

void linkedlist_dump(const struct linkedlist *self) {
    printf("( ");
    linkedlist_node_dump(self->first);
    printf(" )\n");
}

/*
 * Add an element in the linkedlist at the end
 */
void linkedlist_node_add_back(struct list_node *self, int value) {
    if (self->next == NULL) {
        struct list_node *l = malloc(sizeof(struct list_node));
        l->value = value;
        l->next = NULL;
        self->next = l;
    }
    else {
        linkedlist_node_add_back(self->next, value);
    }
}

void linkedlist_add_back(struct linkedlist *self, int value) {
    if (self->first == NULL) {
        self->first = malloc(sizeof(struct list_node));
        self->first->value = value;
        self->first->next = NULL;
    }
    else {
        linkedlist_node_add_back(self->first, value);
    }
}

/*
 * Add an element in the linkedlist at the beginning
 */
void linkedlist_add_front(struct linkedlist *self, int value) {
    struct list_node *l = malloc(sizeof(struct list_node));
    l->value = value;
    l->next = self->first;
    self->first = l;
}

/*
 * Remove an element in the linkedlist (preserving the order)
 */
void linkedlist_remove(struct linkedlist *self, size_t index) {
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
int linkedlist_get(const struct linkedlist *self, size_t index) {
    if (self->first != NULL) {
        struct list_node *l = self->first;
        for (size_t i = 0; i < index; ++i) {
            l = l->next;
        }
        return l->value;
    }
    return 0;
}

/*
 * Tell if the linkedlist is empty
 */
bool linkedlist_is_empty(const struct linkedlist *self) {
    if (self->first != NULL) {
        return false;
    }
    return true;
}

/*
 * Get the size of the list
 */
size_t linkedlist_size(const struct linkedlist *self) {
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
size_t linkedlist_node_search(const struct list_node *self, int value) {
    if (self == NULL) {
        return 0;
    }
    if (self->value == value) {
        return 0;
    }

    return 1 + linkedlist_node_search(self->next, value);
}

size_t linkedlist_search(const struct linkedlist *self, int value) {
    return linkedlist_node_search(self->first, value);
}


/*
 * Transform the parent array to a path thanks to ending and starting node
 */
void linkedlist_parent_to_path(struct linkedlist *self, int * parent, int nodeStart, int nodeEnd){

    linkedlist_add_front(self,nodeEnd);
    int i = parent[nodeEnd];

    while(i != nodeStart){
        linkedlist_add_front(self,i);
        i = parent[i];
    }
    linkedlist_add_front(self,nodeStart);
}
