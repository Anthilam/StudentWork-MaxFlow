#include "list.h"

/*
 * Create an empty node
 */
void node_create(struct node *self)
{
	self->n = 0;
	self->weight = 0;
	self->nextnode = NULL;
	self->previousnode = NULL;
}

/*
 * Add an element in the list at the end
 */
void node_add_back(struct node *self, struct node *back)
{
	if (self->nextnode != NULL)
	{
		node_add_back(self->nextnode, back);
	}
	else
	{
		self->nextnode = malloc(sizeof(struct node));
		self->nextnode = back;
		back->previousnode = malloc(sizeof(struct node));
		back->previousnode = self;
		back->nextnode = NULL;
	}
}

/*
 * Add an element in the list at the beginning
 */
void node_add_front(struct node *self, struct node *front)
{
	struct node empty;
	node_go_first(self,&empty);
	empty.nextnode->previousnode = malloc(sizeof(struct node));
	empty.nextnode->previousnode = front;
	front->nextnode = empty.nextnode;
}

/*
 * Insert an node between two node
 */
void node_insert(struct node *self, struct node *previous, struct node *next)
{
	self->previousnode = previous;
	previous->nextnode = self;
	self->nextnode = next;
	next->previousnode = self;
}

/*
 * Destroy a node
 */
void node_destroy(struct node *self)
{
	self->n = 0;
	self->weight = 0;

	if (self->nextnode != NULL)
	{
		self->nextnode->previousnode = NULL;
	}

	if (self->previousnode != NULL)
	{
		self->previousnode->nextnode = NULL;
	}

	self->nextnode = NULL;
	self->previousnode = NULL;
}

/*
* Destroy a list of node
*/
void node_list_destroy(struct node *self)
{
	if (self->previousnode != NULL)
	{
		struct node empty;
		node_go_first(self->previousnode, &empty);
		node_list_destroy_help(empty.nextnode);
	}
	else
	{
		node_list_destroy_help(self);
	}
}

void node_list_destroy_help(struct node *self)
{
	if (self->nextnode != NULL)
	{
		struct node empty;
		empty.nextnode = self->nextnode;
		node_destroy(self);
		node_list_destroy_help(empty.nextnode);
	}
}

/*
* Go to the first node from a node
*/
void node_go_first(struct node *self, struct node *empty)
{
	if (self->previousnode!=NULL)
	{
		node_go_first(self, empty);
	}
	else
	{
		empty->nextnode = self;
	}
}

/*
* Dump a node
*/
void node_dump(struct node *self)
{
	if (self != NULL)
	{
		printf("(%d/%d)", self->n, self->weight);
	}
}

/*
* Dump a list
*/
void list_dump(struct node *self)
{
	if (self->previousnode != NULL)
	{
		struct node empty;
		node_go_first(self->previousnode, &empty);
		list_dump_help(empty.nextnode);
	}
	else
	{
		list_dump_help(self);
	}
}

void list_dump_help(struct node *self)
{
	node_dump(self);
	if (self->nextnode != NULL)
	{
		printf(", ");
		list_dump_help(self->nextnode);
	}
}
