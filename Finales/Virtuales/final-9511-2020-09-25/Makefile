CFLAGS = -std=c99 -Wall -pedantic -g -Werror=vla
CC = gcc

all: unicode_pruebas

unicode_pruebas: pruebas.o unicode.o
	$(CC) $(CFLAGS) pruebas.o unicode.o -o unicode_pruebas

pruebas.o: pruebas.c unicode.h
	$(CC) $(CFLAGS) -c pruebas.c

unicode.o: unicode.c unicode.h
	$(CC) $(CFLAGS) -c unicode.c

clean:
	rm -fv *.o unicode_pruebas
