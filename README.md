To compile the project, the users has to be at the root and just enter "make" in a command line.

To execute the project, he must be at the root an enter "./BIN/main" in a command line after the compilation.

The program then will offers some possibilites to the user. He can select one by entering the numbber of this possibilitie.

There are differents folders :
	BIN : contains the binary produced by the compilation
	DOC : contains the little report
	INCLUDE : contains all the ".h" files
	LIB : contains the ".a" which are produced with the compilation
	OBJ : contains the ".o" which are produced with the compilation
	SAVE : contains the graph that the users wanted to save
	SRC : contains all the sources files

The SRC contains different files :
	graph.c : a library with a lot of methods which are used to do operation on a graph
	list.c : a library to manipulate the adjency list of the graph
	linkedlist.c : a library to manipulate the path used in DFS, BFS and Floyw-Warshall
	main.c : the main program
