
# Makefile 5 --- Contruction de la liste des sources et objets ---

# Variables
CC = gcc -g
CFLAGS = -O4 -W -Wall
CPPFLAGS = -I.
LDLIBS = -lm

# Variables propres a cette applie
MAIN = main
SRC = ./SRC/main.c
OBJ = $(SRC:.c=.o)

# cible principale
all : $(MAIN)

# Regle principale avec l'edition de lien
main : $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) -o 	$@ $^ $(LDLIBS) 

# Regle de construction des .o
%.o : %.c %.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

# Nettoyage des fichiers intermediaires
clean : 
	rm $(OBJ); rm *~

# suppression de tous les fichiers issus de la compilation
veryclean : clean
	rm $(MAIN)
