
# Makefile 5 --- Contruction de la liste des sources et objets ---

# Variables propres a cette applie
MAIN = main
INCLUDE = ./INCLUDE/
SRC = ./SRC/
OBJ = ./OBJ/

# Variables
CC = gcc -g
CFLAGS = -O4 -W -Wall
CPPFLAGS = -I$(INCLUDE)
LDLIBS = -lm


# cible principale
all : $(MAIN)

# Regle principale avec l'edition de lien
main : $(OBJ)main.o $(OBJ)list.o
	$(CC) $(CPPFLAGS) $(CFLAGS) -o 	$@ $^ $(LDLIBS) 

# Regle de construction des .o
$(OBJ)%.o : $(SRC)%.c $(INCLUDE)%.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers intermediaires
clean : 
	rm $(OBJ); rm *~

# suppression de tous les fichiers issus de la compilation
veryclean : clean
	rm $(MAIN)
