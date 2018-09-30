#include "list.h"



/*
 * Create an empty neighbour
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
 * Insert an neighbour between two neighbour
 */
void neighbour_insert(struct Neighbour *self, struct Neighbour *previous, struct Neighbour *next){
	self->previousNeighbour = previous;
	previous->nextNeighbour = self;
	self->nextNeighbour = next;
	next->previousNeighbour = self;
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

