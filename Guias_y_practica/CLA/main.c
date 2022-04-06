
/**
 * @file main.c
 * @authors
 * Francisco Fanzi
 * Guido Rodriguez (guerodriguez@fi.uba.ar)
 *
 * @brief Guia CLA
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_EJERCICIO 15

/* -------------------------------------------------------------------------- */
/*                       Argumentos en línea de comandos                      */
/* -------------------------------------------------------------------------- */

#if N_EJERCICIO == 1

// Describa qué son, qué tipos las definen y qué contienen las variables argc y argv en la ejecucion de un programa.

// argc cuenta el número de argumentos. Cuenta el nombre del archivo como primer argumento. (es un int)

// El argv [] contiene el número total de argumentos. El primer argumento es el nombre del archivo siempre. (es un char*)

// Ejemplo de aplicacion
int main(int argc, char *argv[]);

#elif N_EJERCICIO == 2

#elif EJERCICIO == 2
/*
Dada la siguiente ejecucion de un programa:

$ ./programa -s "Hola Mundo!"

¿cuánto vale argc?
Haga un diagrama que muestre el contenido de argv.*/

argc = 3 argv[3]-- > [0] =./ programa, [1] = -s, [2] = "Hola Mundo!"

#endif

/* -------------------------------------------------------------------------- */
/*                           Argumentos posicionales                          */
/* -------------------------------------------------------------------------- */

#if N_EJERCICIO == 3

int main(int argc, char *argv[]) {

	for (size_t i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	return 0;
}

#elif N_EJERCICIO == 4

int main(int argc, char *argv[]) {

	if (argc != 2) {
		fprintf(stderr, "Lo ingresado no es valido\n");
		return 1;
	}

	printf("La longitud de la cadena es: %zd\n", mi_strlen(argv[1]));

	return 0;
}

#elif N_EJERCICIO == 5

int main(int argc, char **argv) {
	return 0;
}

#elif N_EJERCICIO == 6

int main(int argc, char **argv) {
	return 0;
}

#elif N_EJERCICIO == 7

int main(int argc, char **argv) {
	return 0;
}

#elif N_EJERCICIO == 8

int main(int argc, char **argv) {
	return 0;
}

#elif N_EJERCICIO == 9

/*
El siguiente programa generará muestras aleatorias en un intervalo dado por el usuario.
El programa debe recibir como argumentos el inicio del intervalo, , el fin del intervalo,
, y la cantidad de muestras a generar, , de forma tal que se ejecute de la siguiente manera:
./random x_i x_f n

$ ./g07e09 -3 2.65 10
2.0284
1.5767
0.4812
-1.1543
-0.7098
-0.1651
2.0144
0.2328
0.2302
1.3886
*/

float prng_f_range(float x_i, float x_f) {
	return x_i + ((float)rand() / (RAND_MAX - 1)) * (x_f - x_i);
}

int main(int argc, char **argv) {

	if (argc != 4) {
		fprintf(stderr, "Argumentos invalidos\n");
		return 1;
	}

	char *err_ptr;
	float x_i = strtof(argv[1], &err_ptr);
	if (*err_ptr != '\0') {
		fprintf(stderr, "Argumento invalido\n");
		return 1;
	}

	float x_f = strtof(argv[2], &err_ptr);
	if (*err_ptr != '\0') {
		fprintf(stderr, "Argumento invalido\n");
		return 1;
	}

	int n = strtol(argv[3], &err_ptr, 10);
	if (*err_ptr != '\0' || n < 0) {
		fprintf(stderr, "Argumento invalido\n");
		return 1;
	}

	srand(time(NULL));

	for (size_t i = 0; i < n; ++i)
		printf("%.4f\n", prng_f_range(x_i, x_f));

	return 0;
}

#elif N_EJERCICIO == 10

/*
El siguiente programa procesará las lineas por stdin e imprimirá datos de las mismas.
Escriba un programa que reciba como parámetros una posicion y un ancho e imprima, de
cada linea, los datos que comienzan en la posicion posicion y se componen de ancho
caracteres. La ejecucion del mismo es:

$ cat archivo.txt | ./extraer posicion ancho
Este programa es de utilidad cuando se trabaja con datos almacenados en archivos
formados por registros con campos de ancho fijo. El utilizar este tipo de formato
permite un procesamiento muy veloz de los datos, y archivos más pequeños que la
gran mayoria de los formatos (sin compresion). Un ejemplo de un archivo de este estilo:

Lista 4 bibliografia.txt

| Autores_1| Autores_2                    | Titulo                     | Editorial     | Año  | ISBN          |
| Kernighan Ritchie         | The C Programming Language | Prentice-Hall | 1988 | 9780131103702 |
| Kernighan Ritchie         | El lenguaje de programacio | Pearson Educa | 1991 | 9789688802052 |
| Aguilar           Zahoner | Programacion en C: metodol | McGraw-Hill   | 2005 | 9788448198442 |
| Deitel   Deitel           | C: How to Program          | Pearson       | 2012 | 9780132990448 |
| Bowman                    | Algorithms and Data Struct | Oxford Univer | 2004 | 9780195174809 |
| Bowman   Hernánd          | Algoritmos y estructuras d | Oxford Univer | 1999 | 9789706134592 |
| Kruse    Tondo            | Data Structures and Progra | Pearson Educa | 2007 | 9788177584233 |

Kruse    Tondo  Data Structures and PrograPearson Educa20079788177584233

Los campos del documento son:

Autor 1:   posicion: 1,  ancho: 9
Autor 2:   posicion: 10, ancho: 7
Titulo:    posicion: 17, ancho: 26
Editorial: posicion: 43, ancho: 13
Año:       posicion: 56, ancho: 4
ISBN:      posicion: 60, ancho: 13
																												./CLA10
Ejemplo de ejecucion:

$ cat bibliografia.txt | ./g07e10 60 13
9780131103702
9789688802052
9788448198442
9780132990448
9780195174809
9789706134592
9788177584233
*/

#define CENTINELA 1

/**
 * @brief Lee una linea de longitud indefinida
 * @pre El archivo viene abierto en modo lectura
 * @pre La funcion no reconoce caracteres UNICODE.
 * @param  *f: Archivo abierto en modo texto
 * @retval Cadena de caracteres leida
 */
char *leer_lineas(FILE *f) {

	int c;

	char *l_ptr = NULL;

	size_t n = 0;

	while ((c = fgetc(f)) != EOF) {

		char *c_aux = realloc(l_ptr, sizeof(char) * (n + 1) + CENTINELA);

		if (c_aux == NULL) {
			if (l_ptr != NULL)
				free(l_ptr);
			return NULL;
		}

		l_ptr = c_aux;
		l_ptr[n++] = c;
		l_ptr[n] = '\0';

		if (c == '\n')	  // Lo pongo aca porque si no, no incluye en la cadena el \n de la linea.
			return l_ptr;
	}

	return l_ptr;
}

int main(int argc, char **argv) {

	if (argc != 3) {
		fprintf(stderr, "Error\n");
		return 1;
	}
	char *err_ptr;
	int posicion = strtol(argv[1], &err_ptr, 10);
	if (*err_ptr != '\0' && posicion < 0) {
		fprintf(stderr, "Error\n");
		return 1;
	}
	int ancho = strtol(argv[2], &err_ptr, 10);
	if (*err_ptr != '\0' && ancho < 0) {
		fprintf(stderr, "Error\n");
		return 1;
	}
	char *linea;
	while ((linea = leer_lineas(stdin)) != NULL) {
		for (size_t i = posicion - 1; i < posicion - 1 + ancho; i++)
			printf("%c", linea[i]);
		putchar('\n');
		free(linea);
	}
	return 0;
}

#elif N_EJERCICIO == 11

/*
El siguiente programa trabajará con archivos con campos separados por delimitadores (DSV)
1.El más común de ellos es el que utiliza comas (,) como separadores, el CSV
2.El archivo anterior podría escribirse como:

---------------------------- bibliografia.csv ----------------------------
Kernighan,Ritchie,The C Programming Language,Prentice Hall,1988,9780131103702
Kernighan,Ritchie,El lenguaje de programación C,Pearson Educación,1991,9789688802052
Aguilar,Zahonero,Programación en C: metodología, algoritmos y estructuras de datos,McGraw-Hill,2005,9788448198442
Deitel,Deitel.C: How to Program,Pearson,2012,9780132990448.
Bowman,,Algorithms and Data Structures: An Approach in C,Oxford University Press,2004,9780195174809
Bowman,Hernández,Algoritmos y estructuras de datos: aproximación en C,Oxford University Press,1999,9789706134592
Kruse,Tondo,Data Structures and Program Design in C,Pearson Education,2007,9788177584233

En este caso, implemente un programa que reciba como argumento el número de campo e imprima el campo correspondiente.
Los números de campo comienzan en 1, mientras que el 0 corresponde a la línea completa.
*/

#define CENTINELA 1

/**
 * @brief Lee una linea de longitud indefinida
 * @pre El archivo viene abierto en modo lectura
 * @pre La funcion no reconoce caracteres UNICODE.
 * @param  *f: Archivo abierto en modo texto
 * @retval Cadena de caracteres leida
 */
char *leer_lineas(FILE *f) {

	int c;

	char *l_ptr = NULL;

	size_t n = 0;

	while ((c = fgetc(f)) != EOF) {

		char *c_aux = realloc(l_ptr, sizeof(char) * (n + 1) + CENTINELA);

		if (c_aux == NULL) {
			if (l_ptr != NULL)
				free(l_ptr);
			return NULL;
		}

		l_ptr = c_aux;
		l_ptr[n++] = c;
		l_ptr[n] = '\0';

		if (c == '\n')	  // Lo pongo aca porque si no, no incluye en la cadena el \n de la linea.
			return l_ptr;
	}

	return l_ptr;
}

/**
 * @brief Devuelve el campo correspondiente al número de campo
 * @pre Los datos del archivo deben estar separados por comas (,). No pueden hallarse 2 o más comas consecutivas.
 */
int main(int argc, char **argv) {

	if (argc != 2) {
		perror("Error\n");
		return 1;
	}

	char *err_ptr;
	int campo = strtol(argv[1], &err_ptr, 10);
	if (*err_ptr != '\0' && campo < 0) {
		perror("Error\n");
		return 1;
	}

	char *linea;
	while ((linea = leer_lineas(stdin)) != NULL) {

		char *token;
		token = strtok(linea, ",");

		for (int i = 1; i < campo; i++)
			token = strtok(NULL, ",");

		printf("<%s>", token);
		putchar('\n');
	}

	return 0;
}

#elif N_EJERCICIO == 12

/*
Escriba un programa 'expr' que evalúa expresiones en notación Polaca inversa 3 recibidas como argumento. Por ejemplo:

$ ./expr 2 222 111 + "*"
666

evalúa la operación: (111 + 222) * 2 .
*/

int main(int argc, char *argv[]) {

	return 0;
}

#endif

/* -------------------------------------------------------------------------- */
/*                         Argumentos no-posicionales                         */
/* -------------------------------------------------------------------------- */

#if N_EJERCICIO == 13

/*
Modifique el programa del ejercicio 09 para que reciba los argumentos utilizando las siguientes banderas:
-a comienzo del intervalo
-b fin del intervalo
-n cantidad de muestras
-h muestra un mensaje de ayuda, sin realizar ninguna otra funcion

Las banderas deben poder aparecer en cualquier orden, por lo que las siguientes invocaciones del programa son equivalentes:

$ ./g07e13 -a -3 -b 2.65 -n 10
$ ./g07e13 -b 2.65 -a -3 -n 10
$ ./g07e13 -n 10 -b 2.65 -a -3
2.0422
1.6900
-1.0428
-0.3802
-1.7582
-1.3972
-1.5386
-0.0568
-2.3125
-2.6120
$ ./g07e13 -h
NOMBRE
		   g07e13, sampler - genera lotes de números pseudo-aleatorios

SINOPSIS
		   g07e13 [-a A] [-b B] [-n N] [-h]

DESCRIPCIoN
		   Generar un lote de N números pseudo-aleatorios en el intervalo
		   [A,B). La distribucion muestreada es U[A,B).

OPCIONES
		   h
						  muestra esta ayuda.
		   a A
						  comienzo del intervalo. Valor por omision: 0.0.
		   b B
						  fin del intervalo. Valor por omision: 1.0.
		   n N
						  cantidad de muestras a tomar. Valor por omision: 100.

AUTORES
		   Ada Lovelace, Alan Turing

LICENCIA
		   GNU General Public License v3.0
*/

float prng_f_range(float x_i, float x_f) {
	return x_i + ((float)rand() / (RAND_MAX - 1)) * (x_f - x_i);
}

int main(int argc, char **argv) {

	if (argc > 7 || argc < 2) {
		fprintf(stderr, "Argumentos incorrectos.\n");
		return 1;
	}

	const char *help = "\t\tNOMBRE \n\
	   	g07e13, sampler - genera lotes de números pseudo-aleatorios\n\
		\n\
		SINOPSIS\n\
			g07e13 [-a A] [-b B] [-n N] [-h]\n\
		\n\
		DESCRIPCIoN\n\
			Generar un lote de N números pseudo-aleatorios en el intervalo\n\
			[A,B). La distribucion muestreada es U[A,B).\n\
		\n\
		OPCIONES\n\
			h\n\
					muestra esta ayuda.\n\
			a A\n\
					comienzo del intervalo. Valor por omision: 0.0.\n\
			b B\n\
					fin del intervalo. Valor por omision: 1.0.\n\
			n N\n\
					cantidad de muestras a tomar. Valor por omision: 100.\n\
		\n\
		AUTORES\n\
			Ada Lovelace, Alan Turing\n\
		\n\
		LICENCIA\n\
			GNU General Public License v3.0\n";

	float x_a = 0.0f;
	float x_b = 0.0f;
	size_t n = 0;

	bool a_flag = false;
	bool b_flag = false;
	bool n_flag = false;

	char *err_ptr;

	for (size_t i = 1; i < argc; ++i) {

		if (strcmp(argv[i], "-a") == 0) {

			x_a = strtof(argv[i + 1], &err_ptr);
			if (*err_ptr != '\0') {
				fprintf(stderr, "Argumento de minimo incorrecto.\n");
				return 1;
			}
			a_flag = true;

		} else if (strcmp(argv[i], "-b") == 0) {

			x_b = strtof(argv[i + 1], &err_ptr);
			if (*err_ptr != '\0') {
				fprintf(stderr, "Argumento de maximo incorrecto.\n");
				return 1;
			}
			b_flag = true;

		} else if (strcmp(argv[i], "-n") == 0) {

			n = strtol(argv[i + 1], &err_ptr, 10);
			if (*err_ptr != '\0' || n < 1) {
				fprintf(stderr, "Argumento de iteracion incorrecto.\n");
				return 1;
			}
			n_flag = true;

		} else if (strcmp(argv[i], "-h") == 0) {
			printf("%s", help);
			return 0;
		}
	}

	if (!a_flag || !b_flag || !n_flag) {
		fprintf(stderr, "Argumentos invalidos. Error en flags.\n");
		return 1;
	}

	printf("Flags: %c %c %c\n", a_flag ? 'a' : ' ', b_flag ? 'b' : ' ', n_flag ? 'n' : ' ');

	srand(time(NULL));

	for (size_t i = 0; i < n; ++i)
		printf("%.4f\n", prng_f_range(x_a, x_b));

	return 0;
}

#elif N_EJERCICIO == 14
/*
Modifique el programa extractor de campos de ancho fijo (ver aqui) de forma tal que los argumentos del mismo se puedan recibir en cualquier orden. Para ello, agregue las siguientes banderas:

-p posicion del campo
-a ancho del campo
-h muestra un mensaje de ayuda, sin realizar ninguna otra funcion

Ejemplo de ejecucion:

$ cat bibliografia.txt | ./g07e14 -p 60 -a 13
$ cat bibliografia.txt | ./g07e14 -a 13 -p 60
9780131103702
9789688802052
9788448198442
9780132990448
9780195174809
9789706134592
9788177584233
$ ./g07e14 -h
*/
char *leer_lineas(FILE *f) {

	int c;

	char *l_ptr = NULL;

	size_t n = 0;

	while ((c = fgetc(f)) != EOF) {

		char *c_aux = realloc(l_ptr, sizeof(char) * (n + 1) - 1);

		if (c_aux == NULL) {
			if (l_ptr != NULL)
				free(l_ptr);
			return NULL;
		}

		l_ptr = c_aux;
		l_ptr[n++] = c;
		l_ptr[n] = '\0';

		if (c == '\n')	  // Lo pongo aca porque si no, no incluye en la cadena el \n de la linea.
			return l_ptr;
	}

	return l_ptr;
}

int main(int argc, char **argv) {

	const char *help = "\
		NOMBRE\n\
				g07e14, extractor - extrae campos de ancho fijo\n\
\
		SINOPSIS g07e14 -\n\
				p POSICIoN - a ANCHO[-h]\n\
\
		DESCRIPCIoN\n\
				Lee lineas de stdin y extrae porciones de texto de cada\n\
				una de estas.\n\
\
		OPCIONES\n\
				h\n\
						muestra esta ayuda.\n\
				p POSICIoN\n\
						posicion en la que comienza un campo.\n\
				a ANCHO\n\
						ancho del campo a extraer\n\
\
		AUTORES\n\
				Steve Jobs, nah, mentira, \"nunca\" escribio codigo en su\n\
				vida.\n\
\
		LICENCIA\n\
				GNU General Public License v3 .0\n ";

	if (argc > 5 || argc < 2) {
		fprintf(stderr, "Argumentos incorrectos.\n");
		return 1;
	}

	bool p_flag = false;
	bool a_flag = false;

	int p = 0;
	int a = 0;

	char *err_ptr;

	for (size_t i = 1; i < argc; ++i) {

		if (strcmp(argv[i], "-p") == 0) {
			p = strtol(argv[i + 1], &err_ptr, 10);
			if (*err_ptr != '\0' || p < 0) {
				fprintf(stderr, "Argumento -p incorrecto.\n");
				return 1;
			}
			p_flag = true;

		} else if (strcmp(argv[i], "-a") == 0) {
			a = strtol(argv[i + 1], &err_ptr, 10);
			if (*err_ptr != '\0' || a < 0) {
				fprintf(stderr, "Argumento -a incorrecto.\n");
				return 1;
			}
			a_flag = true;

		} else if (strcmp(argv[i], "-h") == 0) {
			printf("%s", help);
			return 0;
		}
	}

	if (!p_flag || !a_flag) {
		fprintf(stderr, "Argumentos invalidos. Error en flags.\n");
		return 1;
	}

	printf("Flags: %c %c\n", p_flag ? 'p' : ' ', a_flag ? 'a' : ' ');

	char *linea;
	while ((linea = leer_lineas(stdin)) != NULL) {
		for (size_t i = p - 1; i < p - 1 + a; i++)
			printf("%c", linea[i]);
		putchar('\n');
		free(linea);
	}

	return 0;
}

#elif N_EJERCICIO == 15

/*
Sea la siguiente forma de onda

f(t) = e^(at) · A · cos(2π · f · t)

Escribir un programa con comandos en línea de órdenes que permita tabular la función dentro del intervalo [T1,T2) utilizando N puntos, aceptando la siguiente invocación:

sampler –alfa <a> -amp <A> -frec <f> -start <T1> -end <T2> -points <N>
Realizar las validaciones pertinentes.

Ejemplo de ejecución:

$ ./g07e15 -amp 3 -frec .6 -end 6 -start 0 -alfa 0.5 -points 10
0       3
0.6     -1.41665
1.2     -0.308511
1.8     1.06884
2.4     -0.84013
3       0.206853
3.6     0.265715
4.2     -0.364472
4.8     0.198392
5.4     0.0126596

$ ./g07e15 -h
NOMBRE
	   g07e15, sampler - muestrea una senoidal con decaimiento
	   exponencial

SINOPSIS
	   g07e15 –alfa a -amp A -frec f -start T1 -end T2 -points N

DESCRIPCIÓN
	   Dada la función:
					   -at
			   f(t) = e    A cos(2 pi f t)
	   toma N muestras a intervalos de tiempo regulares entre T1
	   y T2. El span del intervalo entre muestras es (T2 - T1)/N

OPCIONES
	   h
			  muestra esta ayuda.
	   alfa a
			  tasa de dacaimiento
	   amp A
			  amplitud de la función en tiempo 0
	   frec f
			  frecuencia del oscilador
	   start T1
			  valor inicial del intervalo
	   end T2
			  valor final del intervalo
	   points N
			  cantidad de puntos a imprimir

AUTORES
	   Bill Gatos, nah, mentira, en un mundo sin fronteras ¿para
	   qué queremos puertas (Gates) y ventanas (Windows)?.

LICENCIA
	   GNU General Public License v3.0
*/

#define PI 3.1415927f

float sin_w_exp_dec(float t, float a, float A, float f) {
	return A * exp(-a * t) * cos(2 * PI * f * t);
}

int main(int argc, char **argv) {

	if (argc < 13) {
		fprintf(stderr, "Argumentos incompletos.\n");
		return 1;
	}

	float alfa = 0.0f;
	float amp = 0.0f;
	float frec = 0.0f;
	float start = 0.0f;
	float end = 0.0f;
	size_t points = 0;

	bool alfa_flag = 0.0f;
	bool amp_flag = 0.0f;
	bool frec_flag = 0.0f;
	bool start_flag = 0.0f;
	bool end_flag = 0.0f;
	bool points_flag = 0;

	char *err_ptr;

	for (size_t i = 1; i < argc; ++i) {

		// -alfa
		if (strcmp(argv[i], "-alfa") == 0) {

			alfa = strtof(argv[i + 1], &err_ptr);
			if (*err_ptr != '\0') {
				fprintf(stderr, "Argumento < -alfa > incorrecto.\n");
				return 1;
			}
			alfa_flag = true;

			// -amp
		} else if (strcmp(argv[i], "-amp") == 0) {

			amp = strtof(argv[i + 1], &err_ptr);
			if (*err_ptr != '\0') {
				fprintf(stderr, "Argumento < -amp > incorrecto.\n");
				return 1;
			}
			amp_flag = true;

			// -frec
		} else if (strcmp(argv[i], "-frec") == 0) {

			frec = strtof(argv[i + 1], &err_ptr);
			if (*err_ptr != '\0' || frec < 0) {
				fprintf(stderr, "Argumento < -frec > incorrecto.\n");
				return 1;
			}
			frec_flag = true;

			// -start
		} else if (strcmp(argv[i], "-start") == 0) {

			start = strtof(argv[i + 1], &err_ptr);
			if (*err_ptr != '\0' || start < 0) {
				fprintf(stderr, "Argumento < -start > incorrecto.\n");
				return 1;
			}
			start_flag = true;

			// -end
		} else if (strcmp(argv[i], "-end") == 0) {

			end = strtof(argv[i + 1], &err_ptr);
			if (*err_ptr != '\0' || end < 0 || end <= start) {
				fprintf(stderr, "Argumento < -end > incorrecto.\n");
				return 1;
			}
			end_flag = true;

			// -points
		} else if (strcmp(argv[i], "-points") == 0) {

			points = strtol(argv[i + 1], &err_ptr, 10);
			if (*err_ptr != '\0' || points < 1) {
				fprintf(stderr, "Argumento de < -points > incorrecto.\n");
				return 1;
			}
			points_flag = true;

		} else if (strcmp(argv[i], "-h") == 0) {
			FILE *help = fopen("15_help_file.txt", "r");
			if (help == NULL) {
				fprintf(stderr, "Estamos trabajando en ello. ¯\\_(ツ)_/¯\n");
				return 1;
			}

			int c;
			while ((c = fgetc(help)) != EOF)
				fprintf(stderr, "%c", c);
			return 0;
		}
	}

	if (!alfa_flag && !amp_flag && !frec_flag && !start_flag && !end_flag && !points_flag) {
		fprintf(stderr, "Argumentos invalidos. Error en flags.\n");
		return 1;
	}

	printf("Flags: %c %c %c %c %c %c\n", alfa_flag ? 'a' : ' ', amp_flag ? 'A' : ' ', frec_flag ? 'f' : ' ', start_flag ? 's' : ' ', end_flag ? 'e' : ' ', points_flag ? 'p' : ' ');
	printf("Argumentos: <alfa: %.2f> <amp: %.2f> <frec: %.2f> <start: %.2f> <end: %.2f> <points: %zu>\n", alfa, amp, frec, start, end, points);

	float t = start;
	const float dt = (end - start) / points;

	for (size_t i = 0; i < points; ++i) {
		printf("%.1f\t%f\n", t, sin_w_exp_dec(t, alfa, amp, frec));
		t += dt;
	}

	return 0;
}

#endif