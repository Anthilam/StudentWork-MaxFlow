# Makefile --- Contruction de la liste des sources et objets ---

# Variables propres a cette application
MAIN = main
BIN = ./BIN/
INCLUDE = ./INCLUDE/
SRC = ./SRC/
OBJ = ./OBJ/
LIB = ./LIB/

# Variables
CC = gcc -g
CFLAGS = -O4 -W -Wall
CPPFLAGS = -I$(INCLUDE)
LDLIBS = -L$(LIB) -lm -lgraph -llist

# Cible principale
all : $(BIN)main

# Regle principale avec l'edition de lien
$(BIN)main: $(OBJ)main.o $(LIB)liblist.a $(LIB)libgraph.a
	$(CC) $(CPPFLAGS) $(CFLAGS) -o 	$@ $^ $(LDLIBS)

# Regle de construction des .o
$(OBJ)%.o : $(SRC)%.c $(INCLUDE)%.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(LIB)liblist.a : $(OBJ)list.o
	ar rcs $(LIB)liblist.a $(OBJ)list.o

$(LIB)libgraph.a : $(OBJ)graph.o
	ar rcs $(LIB)libgraph.a $(OBJ)graph.o

# Nettoyage des fichiers intermediaires
clean :
	rm -f $(OBJ)*

# Suppression de tous les fichiers issus de la compilation
veryclean : clean
	rm -f $(BIN)*
	rm -f $(LIB)*
