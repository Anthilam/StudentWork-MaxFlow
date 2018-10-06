#include "list.h"

/*
 * Create an empty neighbour
 */
void neighbour_create(struct Neighbour *self, int neighbour, int weight)
{
	self->neighbour = neighbour;
	self->weight = weight;
	self->previousNeighbour = NULL;
	self->nextNeighbour = NULL;
}


/*
 * Add an element in the list at the beginning
 */
void neighbour_add_front(struct Neighbour *self, struct Neighbour *front)
{
	self->previousNeighbour = malloc(sizeof(struct Neighbour));
	self->previousNeighbour = front;
	front->nextNeighbour = self;
}


/*
 * Destroy a neighbour
 */
void neighbour_destroy(struct Neighbour *self)
{
	if (self->nextNeighbour != NULL)
	{
		self->nextNeighbour->previousNeighbour = NULL;
	}

	if (self->previousNeighbour != NULL)
	{
		self->previousNeighbour->nextNeighbour = NULL;
	}

	self->nextNeighbour = NULL;
	self->previousNeighbour = NULL;
	self = NULL;
}

/*
* Destroy a list of neighbour
*/
void neighbour_list_destroy(struct Neighbour *self)
{
	if (self->nextNeighbour != NULL)
	{
		struct Neighbour empty;
		empty.nextNeighbour = self->nextNeighbour;
		neighbour_destroy(self);
		neighbour_list_destroy(empty.nextNeighbour);
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
	if (self != NULL)
	{
		neighbour_dump(self);
		if (self->nextNeighbour != NULL)
		{
			printf(", ");
			list_dump(self->nextNeighbour);
		}
	}
}
