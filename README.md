# Maximum Flow project

## Build

To compile the project, go to the root folder and enter `make` in the terminal.

You also have the following :
	`make clean` : cleans the OBJ folder
	`make veryclean` : cleans the OBJ, BIN and LIB folders

## Launch

To execute the project, go to the root folder an enter `./BIN/main` in the terminal after compiling the project.

The program will begin with a menu displaying all the features given to the user.
Enter the wanted number in the terminal input and hit ENTER.

## File structure

There are differents folders :
	- BIN : contains the binary produced by the compilation
	- DOC : contains the little report
	- INCLUDE : contains all the ".h" files
	- LIB : contains the ".a" which are produced with the compilation
	- OBJ : contains the ".o" which are produced with the compilation
	- SAVE : contains the graph that the users wanted to save
	- SRC : contains all the sources files

The SRC contains different files :
	- graph.c : a library with a lot of methods which are used to do operation on a graph
	- list.c : a library to manipulate the adjacency list of the graph
	- linkedlist.c : a library to manipulate the path used in DFS, BFS and Floyw-Warshall
	- main.c : the main program
