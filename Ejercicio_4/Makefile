PROGRAM = main
CC = gcc
CFLAGS = -Wall -Werror -std=c99 -pedantic -g
LDFLAGS = -lm

all: $(PROGRAM) clean

$(PROGRAM): main.o parser.o core.o imagen.o mandelbrot.o vector.o ppm.o bmp.o
	$(CC) $(CFLAGS) main.o parser.o core.o imagen.o mandelbrot.o vector.o ppm.o bmp.o -o $(PROGRAM) $(LDFLAGS)

#Para hacer el main.o necesito...
main.o: src/main.c include/parser.h include/imagen.h include/mandelbrot.h
	$(CC) $(CFLAGS) -c src/main.c

#Para hacer el parser.o necesito...
parser.o: src/core/parser.c include/parser.h
	$(CC) $(CFLAGS) -c src/core/parser.c

#Para hacer el parser.o necesito...
core.o: src/core/core.c include/core.h
	$(CC) $(CFLAGS) -c src/core/core.c

#Para hacer el imagen.o necesito...
imagen.o: src/core/canvas/imagen.c include/imagen.h include/color.h
	$(CC) $(CFLAGS) -c src/core/canvas/imagen.c

#Para hacer el mandelbrot.o necesito...
mandelbrot.o: src/core/shapes/mandelbrot.c include/mandelbrot.h include/vector.h include/color.h
	$(CC) $(CFLAGS) -c src/core/shapes/mandelbrot.c

#Para hacer el vector.o necesito...
vector.o: src/core/shapes/vector.c include/vector.h
	$(CC) $(CFLAGS) -c src/core/shapes/vector.c

#Para hacer el ppm.o necesito...
ppm.o: src/core/formats/ppm.c include/ppm.h
	$(CC) $(CFLAGS) -c src/core/formats/ppm.c

#Para hacer el bmp.o necesito...
bmp.o: src/core/formats/bmp.c include/bmp.h
	$(CC) $(CFLAGS) -c src/core/formats/bmp.c

clean:
	rm *o
