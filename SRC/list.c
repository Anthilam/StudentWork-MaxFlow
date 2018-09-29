#include "list.h"



/*
 * Create an empty list
 */
void neighbour_create(struct Neighbour *self) {
	self->neighbour = 0;
	self->weight = 0;
	self->nextNeighbour = NULL;
	self->previousNeighbour = NULL;
}



/*
 * Add an element in the list at the end
 */
void neighbour_add_back(struct Neighbour *self, struct Neighbour *back){
	if(self->nextNeighbour != NULL){
		neighbour_add_back(self->nextNeighbour, back);
	}else{
		self->nextNeighbour = malloc(sizeof(struct Neighbour));
		self->nextNeighbour = back;
		back->previousNeighbour = malloc(sizeof(struct Neighbour));
		back->previousNeighbour = self;
		back->nextNeighbour = NULL;
		
	}
}



/*
 * Add an element in the list at the beginning
 */
void neighbour_add_front(struct Neighbour *self, struct Neighbour *front){
	struct Neighbour empty;
	neighbour_go_first(self,&empty);
	empty.nextNeighbour->previousNeighbour = malloc(sizeof(struct Neighbour));
	empty.nextNeighbour->previousNeighbour = front;
	front->nextNeighbour = empty.nextNeighbour;
}


/*
 * Destroy a neighbour
 */
void neighbour_destroy(struct Neighbour *self){
	self->neighbour = 0;
	self->weight = 0;
	if(self->nextNeighbour != NULL){
		self->nextNeighbour->previousNeighbour = NULL;
	}
	if(self->previousNeighbour != NULL){
		self->previousNeighbour->nextNeighbour = NULL;
	}
	self->nextNeighbour = NULL;
	self->previousNeighbour = NULL;
}


/*
* Destroy a list of neighbour
*/
void neighbour_list_destroy(struct Neighbour *self){
	if(self->previousNeighbour != NULL){
		struct Neighbour empty;
		neighbour_go_first(self->previousNeighbour,&empty);
		neighbour_list_destroy_help(empty.nextNeighbour);
	}else{
		neighbour_list_destroy_help(self);
	}
}

void neighbour_list_destroy_help(struct Neighbour *self){
	if(self->nextNeighbour != NULL){
		struct Neighbour empty;
		empty.nextNeighbour = self->nextNeighbour;
		neighbour_destroy(self);
		neighbour_list_destroy_help(empty.nextNeighbour);
	}
}

/*
* Go to the first neighbour from a neighbour
*/
void neighbour_go_first(struct Neighbour *self, struct Neighbour *empty){
	if(self->previousNeighbour!=NULL){
		neighbour_go_first(self,empty);
	}else{
		empty->nextNeighbour = self;
	}	
}


/*
* Dump a neighbour
*/
void neighbour_dump(struct Neighbour *self) {
	if(self != NULL){
		printf("(%d/%d)",self->neighbour,self->weight);
	}
}


/*
* Dump a list
*/
void list_dump(struct Neighbour *self) {
	if(self->previousNeighbour != NULL){
		struct Neighbour empty;
		neighbour_go_first(self->previousNeighbour,&empty);
		list_dump_help(empty.nextNeighbour);
	}else{
		list_dump_help(self);
	}
}

void list_dump_help(struct Neighbour *self){
	neighbour_dump(self);
	if(self->nextNeighbour != NULL){
		printf(", ");
		list_dump_help(self->nextNeighbour);
	}
}

/*


void list_add_front(struct list *self, int value) {
  struct list_node *l = malloc(sizeof(struct list_node));
  l->value = value;
  l->next = self->first;
  self->first = l;
}

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


bool list_is_empty(const struct list *self) {
  if (self->first != NULL) {
    return false;
  }
  return true;
}


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


void list_import(struct list *self, const int *other, size_t size) {
  list_destroy(self);
  for (int i = 0; i < size; ++i) {
    list_add_back(self, other[i]);
  }
}


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
}*/
