CFLAGS = -std=c99 -Wall -pedantic -g -Werror=vla
CC = gcc

all: actordb_pruebas

actordb_pruebas: pruebas.o actordb.o
	$(CC) $(CFLAGS) pruebas.o actordb.o -o actordb_pruebas

pruebas.o: pruebas.c actordb.h
	$(CC) $(CFLAGS) -c pruebas.c

actordb.o: actordb.c actordb.h
	$(CC) $(CFLAGS) -c actordb.c

clean:
	rm -fv *.o actordb_pruebas
