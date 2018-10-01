#include "list.h"

/*
 * Create an empty neighbour
 */
void neighbour_create(struct Neighbour *self)
{
	self->neighbour = 0;
	self->weight = 0;
	self->nextneighbour = NULL;
	self->previousneighbour = NULL;
}

/*
 * Add an element in the list at the end
 */
void neighbour_add_back(struct Neighbour *self, struct Neighbour *back)
{
	if (self->nextneighbour != NULL)
	{
		neighbour_add_back(self->nextneighbour, back);
	}
	else
	{
		self->nextneighbour = malloc(sizeof(struct Neighbour));
		self->nextneighbour = back;
		back->previousneighbour = malloc(sizeof(struct Neighbour));
		back->previousneighbour = self;
		back->nextneighbour = NULL;
	}
}

/*
 * Add an element in the list at the beginning
 */
void neighbour_add_front(struct Neighbour *self, struct Neighbour *front)
{
	struct Neighbour empty;
	neighbour_go_first(self,&empty);
	empty.nextneighbour->previousneighbour = malloc(sizeof(struct Neighbour));
	empty.nextneighbour->previousneighbour = front;
	front->nextneighbour = empty.nextneighbour;
}

/*
 * Insert an neighbour between two neighbour
 */
void neighbour_insert(struct Neighbour *self, struct Neighbour *previous, struct Neighbour *next)
{
	self->previousneighbour = previous;
	previous->nextneighbour = self;
	self->nextneighbour = next;
	next->previousneighbour = self;
}

/*
 * Destroy a neighbour
 */
void neighbour_destroy(struct Neighbour *self)
{
	self->neighbour = 0;
	self->weight = 0;

	if (self->nextneighbour != NULL)
	{
		self->nextneighbour->previousneighbour = NULL;
	}

	if (self->previousneighbour != NULL)
	{
		self->previousneighbour->nextneighbour = NULL;
	}

	self->nextneighbour = NULL;
	self->previousneighbour = NULL;
}

/*
* Destroy a list of neighbour
*/
void neighbour_list_destroy(struct Neighbour *self)
{
	if (self->previousneighbour != NULL)
	{
		struct Neighbour empty;
		neighbour_go_first(self->previousneighbour, &empty);
		neighbour_list_destroy_help(empty.nextneighbour);
	}
	else
	{
		neighbour_list_destroy_help(self);
	}
}

void neighbour_list_destroy_help(struct Neighbour *self)
{
	if (self->nextneighbour != NULL)
	{
		struct Neighbour empty;
		empty.nextneighbour = self->nextneighbour;
		neighbour_destroy(self);
		neighbour_list_destroy_help(empty.nextneighbour);
	}
}

/*
* Go to the first neighbour from a neighbour
*/
void neighbour_go_first(struct Neighbour *self, struct Neighbour *empty)
{
	if (self->previousneighbour!=NULL)
	{
		neighbour_go_first(self, empty);
	}
	else
	{
		empty->nextneighbour = self;
	}
}

/*
* Dump a neighbour
*/
void neighbour_dump(struct Neighbour *self)
{
	if (self != NULL)
	{
		printf("(%d/%d)", self->neighbour, self->weight);
	}
}

/*
* Dump a list
*/
void list_dump(struct Neighbour *self)
{
	if (self->previousneighbour != NULL)
	{
		struct Neighbour empty;
		neighbour_go_first(self->previousneighbour, &empty);
		list_dump_help(empty.nextneighbour);
	}
	else
	{
		list_dump_help(self);
	}
}

void list_dump_help(struct Neighbour *self)
{
	neighbour_dump(self);
	if (self->nextneighbour != NULL)
	{
		printf(", ");
		list_dump_help(self->nextneighbour);
	}
}
