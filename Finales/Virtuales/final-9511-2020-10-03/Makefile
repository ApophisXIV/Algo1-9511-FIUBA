CFLAGS = -std=c99 -Wall -pedantic -g -Werror=vla
CC = gcc

all: aerodb_pruebas

aerodb_pruebas: pruebas.o aerodb.o db.o
	$(CC) $(CFLAGS) pruebas.o aerodb.o db.o -o aerodb_pruebas

pruebas.o: pruebas.c aerodb.h
	$(CC) $(CFLAGS) -c pruebas.c

db.o: db.c aerodb.h
	$(CC) $(CFLAGS) -c db.c

aerodb.o: aerodb.c aerodb.h
	$(CC) $(CFLAGS) -c aerodb.c

clean:
	rm -fv *.o aerodb_pruebas
