CFLAGS = -std=c99 -Wall -pedantic -g -Werror=vla
CC = gcc

all: img_pruebas

img_pruebas: pruebas.o rgba.o img.o tipografia8x8.o
	$(CC) $(CFLAGS) pruebas.o tipografia8x8.o rgba.o img.o -o img_pruebas

pruebas.o: pruebas.c img.h
	$(CC) $(CFLAGS) -c pruebas.c

img.o: img.c img.h rgba.h
	$(CC) $(CFLAGS) -c img.c

rgba.o: rgba.c rgba.h
	$(CC) $(CFLAGS) -c rgba.c

tipografia8x8.o: tipografia8x8.c tipografia8x8.h
	$(CC) $(CFLAGS) -c tipografia8x8.c

clean:
	rm -fv *.o img_pruebas img.bin
