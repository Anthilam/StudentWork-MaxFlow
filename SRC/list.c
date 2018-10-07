#include "list.h"

/*
 * Create an empty neighbour
 */
void neighbour_create(Neighbour *self, int neighbour, int weight)
{
	self->neighbour = neighbour;
	self->weight = weight;
	self->nextNeighbour = NULL;
}

/*
 * Add an element in the list at the beginning
 */
void neighbour_add_front(Neighbour *self, Neighbour *front)
{
	Neighbour temp; // Temporary neighbour

	// Save self into temp
	if (memcpy(&temp, self, sizeof(Neighbour)) == NULL)
	{
		printf("ERROR:\tmemcpy() failed, stopping..");
		exit(1);
	}
	
	// Overwrite self with front
	if (memcpy(self, front, sizeof(Neighbour)) == NULL)
	{
		printf("ERROR:\tmemcpy() failed, stopping..");
		exit(1);
	}

	self->nextNeighbour = malloc(sizeof(Neighbour));
	if (self->nextNeighbour == NULL)
	{
		printf("ERROR:\tmalloc() failed, stopping..");
		exit(1);
	}

	// Copy temp (first self) to the nextNeighbour of the new self
	if (memcpy(self->nextNeighbour, &temp, sizeof(Neighbour)) == NULL)
	{
		printf("ERROR:\tmemcpy() failed, stopping..");
		exit(1);
	}
}

/*
* Destroy a list of neighbour
*/
void neighbour_list_destroy(Neighbour *self)
{
	if (self != NULL)
	{
		if (self->nextNeighbour != NULL)
		{
			neighbour_list_destroy(self->nextNeighbour);
		}
		free(self);
	}
}

/*
* Dump a neighbour
*/
void neighbour_dump(Neighbour *self)
{
	if (self != NULL)
	{
		if (self->neighbour >= 0)
		{
			printf("(%d/%d)", self->neighbour+1, self->weight);
		}
		// If it's a negative neighbour
		else
		{
			printf("(%d/%d)", self->neighbour, self->weight);
		}
	}
}

/*
* Dump a list
*/
void list_dump(Neighbour *self)
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
