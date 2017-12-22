CC=gcc
CFLAGS=-LSDL2 -lpthread
LDFLAGS=
EXEC1=SDL

all1: $(EXEC1)

SDL: main.c
	$(CC) main.c -o SDL $(LDFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC1)