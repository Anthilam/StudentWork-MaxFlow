# Makefile --- Contruction de la liste des sources et objets ---

# Variables propres a cette application
MAIN = main
BIN = ./BIN/
INCLUDE = ./INCLUDE/
SRC = ./SRC/
OBJ = ./OBJ/

# Variables
CC = gcc -g
CFLAGS = -O4 -W -Wall
CPPFLAGS = -I$(INCLUDE)
LDLIBS = -lm

# Cible principale
all : $(BIN)main

# Regle principale avec l'edition de lien
$(BIN)main: $(OBJ)main.o $(OBJ)list.o $(OBJ)graph.o
	$(CC) $(CPPFLAGS) $(CFLAGS) -o 	$@ $^ $(LDLIBS)

# Regle de construction des .o
$(OBJ)%.o : $(SRC)%.c $(INCLUDE)%.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers intermediaires
clean :
	rm -f $(OBJ)*

# Suppression de tous les fichiers issus de la compilation
veryclean : clean
	rm -f $(BIN)*
