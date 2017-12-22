CC=gcc
CFLAGS=-LSDL2 -lpthread
LDFLAGS=
EXEC1=Ruzzle

all1: $(EXEC1)

Ruzzle: Grille.o Arbre.o
	$(CC) -o Ruzzle Grille.o Arbre.o $(LDFLAGS)

Grille.o: Grille.c
	$(CC) -o Grille.o -c Grille.c $(CFLAGS)

Arbre.o: Arbre.c
	$(CC) -o Arbre.o -c Arbre.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC1)