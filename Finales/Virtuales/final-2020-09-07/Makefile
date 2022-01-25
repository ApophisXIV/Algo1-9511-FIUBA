CFLAGS = -std=c99 -Wall -pedantic -g -Werror=vla
CC = gcc

all: tuit_pruebas

tuit_pruebas: pruebas.o tuit.o
	$(CC) $(CFLAGS) pruebas.o tuit.o -o tuit_pruebas

pruebas.o: pruebas.c tuit.h
	$(CC) $(CFLAGS) -c pruebas.c

tuit.o: tuit.c tuit.h
	$(CC) $(CFLAGS) -c tuit.c

clean:
	rm -fv *.o tuit_pruebas tuit.bin
