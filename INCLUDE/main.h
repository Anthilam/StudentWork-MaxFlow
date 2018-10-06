#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "graph.h"

void clean_stdin(void){
	int c = 0;
	while ((c = getchar()) != '\n' && c != EOF);

}
