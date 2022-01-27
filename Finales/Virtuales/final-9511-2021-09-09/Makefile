CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -g

EJERCICIOS = ej1 ej2 ej3 ej4 ej5

all: $(EJERCICIOS)

$(EJERCICIOS): %: %.c
	$(CC) $(CFLAGS) $(filter %.c, $^) -o $@

clean:
	rm -fv $(EJERCICIOS)

.PHONY: clean