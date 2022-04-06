/**
 * @file main.c
 * @authors
 * Gaspar Derisi
 * Santiago Mogica
 * Francisco Fanzi
 * Johann Pollero
 * Guido Rodriguez (guerodriguez@fi.uba.ar)
 *
 * @brief Arreglos - Guia 2
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N_EJERCICIO 0

/* -------------------------------------------------------------------------- */
/*                              Archivos de texto                             */
/* -------------------------------------------------------------------------- */

#if N_EJERCICIO == 0

#define CENTINELA 1

/**
 * @brief Lee una linea de longitud indefinida
 * @pre El archivo viene abierto en modo lectura
 * @param  *f: Archivo abierto en modo texto
 * @retval Cadena de caracteres leida
 */
char *readline_n_fgetc(FILE *f) {

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

		if (c == '\n')    // Lo pongo aca porque si no, no incluye en la cadena el \n de la linea
			return l_ptr;
	}

	return l_ptr;
}

/**
 * @brief Lee una linea de longitud definida
 * @pre	El archivo viene abierto en modo lectura texto
 * @param  *f: Archivo abierto en modo texto
 * @param  **l: Puntero a la linea leida
 * @retval True si la lectura fue exitosa, False si hubo un error
 */
bool readline_i_fgetc(FILE *f, char **l) {

	int c;

	char *l_ptr = NULL;

	size_t n = 0;

	while ((c = fgetc(f)) != EOF) {

		char *c_aux = realloc(l_ptr, sizeof(char) * (n + 1) + CENTINELA);

		if (c_aux == NULL) {
			if (l_ptr != NULL)
				free(l_ptr);
			return false;
		}

		l_ptr = c_aux;
		l_ptr[n++] = c;
		l_ptr[n] = '\0';

		if (c == '\n') {    // Lo pongo aca porque si no, no incluye en la cadena el \n de la linea
			*l = l_ptr;
			return true;
		}
	}

	*l = l_ptr;
	return true;
}

/**
 * @brief Lee una linea de longitud indefinida
 * @pre El archivo viene abierto en modo lectura
 * @param  *f: Archivo abierto en modo texto
 * @retval Cadena de caracteres leida
 */
char *readline_n_fgets(FILE *f) {

	char buffer[10 + CENTINELA];
	char *l_ptr = NULL;

	// Invariante de ciclo. Registro de la ultima longitud del array
	size_t l_prev = 0;

	while (fgets(buffer, sizeof(buffer), f) != NULL) {    // Siempre el fgets lee n-1 caracter y reserva el ultimo para el centinela. Minimamente el buffer tiene que tener 2 elementos.

		// Mido la longitud real del string en el buffer antes de ir guardando en heap y sumo 1 para el centinela
		// Longitud de la nueva cadena leida con el buffer + Longitud de la cadena actual guardada en el heap + centinela
		char *buff_aux = realloc(l_ptr, sizeof(char) * (strlen(buffer) + l_prev + CENTINELA));

		if (buff_aux == NULL) {
			if (l_ptr != NULL)
				free(l_ptr);
			return NULL;
		}

		l_ptr = buff_aux;
		strcpy(l_ptr + l_prev, buffer);    // strcpy copia la cadena src en dest incluso el Centinela del src
		l_prev += strlen(buffer);          // Sumo a la longitud actual del arreglo dinamico la longitud actual del array

		if (buffer[strlen(buffer) - CENTINELA] == '\n')
			return l_ptr;
	}

	return l_ptr;
}

/**
 * @brief Lee una linea de longitud definida
 * @pre	El archivo viene abierto en modo lectura texto
 * @param  *f: Archivo abierto en modo texto
 * @param  **l: Puntero a la linea leida
 * @retval True si la lectura fue exitosa, False si hubo un error
 */
bool readline_i_fgets(FILE *f, char **l) {

	char buffer[10 + CENTINELA];
	char *l_ptr = NULL;

	// Invariante de ciclo. Registro de la ultima longitud del array
	size_t l_prev = 0;

	while (fgets(buffer, sizeof(buffer), f) != NULL) {    // Siempre el fgets lee n-1 caracter y reserva el ultimo para el centinela. Minimamente el buffer tiene que tener 2 elementos.

		// Mido la longitud real del string en el buffer antes de ir guardando en heap y sumo 1 para el centinela
		// Longitud de la nueva cadena leida con el buffer + Longitud de la cadena actual guardada en el heap + centinela
		char *buff_aux = realloc(l_ptr, sizeof(char) * (strlen(buffer) + l_prev + CENTINELA));

		if (buff_aux == NULL) {
			if (l_ptr != NULL)
				free(l_ptr);
			return false;
		}

		l_ptr = buff_aux;
		strcpy(l_ptr + l_prev, buffer);    // strcpy copia la cadena src en dest incluso el Centinela del src
		l_prev += strlen(buffer);          // Sumo a la longitud actual del arreglo dinamico la longitud actual del array

		if (buffer[strlen(buffer) - CENTINELA] == '\n') {

			*l = l_ptr;
			return true;
		}
	}

	*l = l_ptr;
	return true;
}

int main(void) {

	/* ---------------------------- readline_n_fgetc ---------------------------- */
	FILE *fi = fopen("lineas.txt", "r");
	if (fi == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo.\n");
		return 1;
	}

	char *l = readline_n_fgetc(fi);

	if (l == NULL) {
		fprintf(stderr, "readline_n_fgetc(): Ocurrio un error al leer el archivo o el archivo esta vacio\n");
		return 1;
	}

	printf("readline_n_fgetc -> [%zd]: La cadena es: %s", strlen(l), l);

	free(l);
	fclose(fi);

	/* ---------------------------- readline_i_fgetc ---------------------------- */
	FILE *fi_2 = fopen("lineas.txt", "r");
	if (fi_2 == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo.\n");
		return 1;
	}

	char *l_2 = NULL;

	if (!readline_i_fgetc(fi_2, &l_2)) {
		fprintf(stderr, "readline_i_fgetc(): Ocurrio un error al leer el archivo o el archivo esta vacio\n");
		return 1;
	}

	printf("readline_i_fgetc -> [%zd]: La cadena es: %s", strlen(l_2), l_2);

	free(l_2);
	fclose(fi_2);

	/* ---------------------------- readline_n_fgets ---------------------------- */
	FILE *fi_3 = fopen("lineas.txt", "r");
	if (fi_3 == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo.\n");
		return 1;
	}

	char *l_3 = readline_n_fgets(fi_3);

	if (l_3 == NULL) {
		fprintf(stderr, "readline_n_fgets(): Ocurrio un error al leer el archivo o el archivo esta vacio\n");
		return 1;
	}

	printf("readline_n_fgets -> [%zd]: La cadena es: %s", strlen(l_3), l_3);

	free(l_3);
	fclose(fi_3);

	/* ---------------------------- readline_i_fgets ---------------------------- */
	FILE *fi_4 = fopen("lineas.txt", "r");
	if (fi_4 == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo.\n");
		return 1;
	}

	char *l_4 = NULL;

	if (!readline_i_fgets(fi_4, &l_4)) {
		fprintf(stderr, "readline_i_fgets(): Ocurrio un error al leer el archivo o el archivo esta vacio\n");
		return 1;
	}

	printf("readline_i_fgets -> [%zd]: La cadena es: %s", strlen(l_4), l_4);

	free(l_4);
	fclose(fi_4);

	return 0;
}

#elif N_EJERCICIO == -1

/*
	Escriba un programa que guarde todo lo que el usuario escriba mientras no escriba una cadena centinela pasada como argumento:

	$ ./editor texto.txt "hasta la victoria"
	*** Guardaré todo lo que escribas en el archivo: texto.txt ***
	*** Para terminar, el centinela es: hasta la victoria      ***
	Ayer te vi que subías
	por el camino a la fuente
	dime dónde vas, morena
	dime dónde vas, salada.
	hasta la victoria
	*** Hasta acá llegamos ***
*/

int main(int argc, char **argv) {

	if (argc != 3) {
		fprintf(stderr, "Argumentos inválidos\n");
		return 1;
	}

	FILE *f = fopen(argv[1], "a");
	if (f == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo\n");
		return 1;
	}

	printf("*** Guardaré todo lo que escribas en el archivo: %s ***\n", argv[1]);
	printf("*** Para terminar, el centinela es: %s ***\n", argv[2]);

	char buffer[100];
	while (fgets(buffer, 100, stdin) != NULL) {

		fprintf(f, "%s", buffer);

		if (strstr(buffer, argv[2]) != NULL) {
			printf("*** Hasta acá llegamos ***\n");
			break;
		}
	}

	fclose(f);
	return 0;
}

#elif N_EJERCICIO == -2

/*
Escriba un programa que copie un archivo de texto. Utilice argumentos en línea de comandos para indicar el archivo
de entrada y el archivo de salida.
*/

int main(int argc, char **argv) {

	if (argc != 3) {
		fprintf(stderr, "Argumentos inválidos\n");
		return 1;
	}

	FILE *src = fopen(argv[1], "r");
	if (src == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo origen\n");
		return 1;
	}

	FILE *dst = fopen(argv[2], "a");
	if (dst == NULL) {
		fclose(src);
		fprintf(stderr, "No se pudo abrir el archivo destino\n");
		return 1;
	}

	char buffer[100];
	while (fgets(buffer, sizeof(buffer), src) != NULL)
		fprintf(dst, "%s", buffer);

	fclose(src);
	fclose(dst);

	return 0;
}

#elif N_EJERCICIO == -3

/*
Escriba un programa que lea un archivo de texto y lo imprima, agregando el número de línea al comienzo:

$ ./numerar texto.txt
1: Ayer te vi que subías
2: por el camino a la fuente
3: dime dónde vas, morena
4: dime dónde vas, salada.
Opcional: agregue un argumento al programa para indicar en qué número debe comenzar a imprimir. Interpretación libre.
*/

int main(int argc, char **argv) {

	if (argc > 3) {
		fprintf(stderr, "Argumentos inválidos\n");
		return 1;
	}

	FILE *f = fopen(argv[1], "r");
	if (f == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo\n");
		return 1;
	}

	int aux = 1;
	size_t linea = 1;

	if (argc == 3) {
		char *err_ptr = NULL;
		aux = strtol(argv[2], &err_ptr, 10);
		if (aux < 1 || *err_ptr != '\0') {
			fprintf(stderr, "Error. Numero de linea invalido.\n");
			return 1;
		}
	}

	int c;
	while ((c = fgetc(f)) != EOF) {

		if (c == '\n')
			++linea;

		if (linea >= aux) {
			printf("%c", c);
			if (c == '\n')
				printf("%zd: ", linea);
		}
	}

	return 0;
}

#elif N_EJERCICIO == -4

/*
Escriba un programa que cuente la cantidad de líneas de un archivo, si el programa recibe el argumento -l.
Opcionalmente, agregue al programa la posibilidad de contar palabras si recibe el argumento -w y bytes si recibe
el argumento -c. Si recibe más de un archivo como argumento, imprime los totales, como se muestra a continuación:

$ ./mi_wc -l texto.txt
4 texto.txt
$ ./mi_wc -c texto.txt
98 texto.txt
$ ./mi_wc -w texto.txt
19 texto.txt
$ ./mi_wc -l -c -w texto.txt
 4 19 98 texto.txt
$ ./mi_wc -c -w -l texto.txt
 4 19 98 texto.txt
$ ./mi_wc -w -l -c texto.txt completa.txt
  4  19  98 texto.txt
 16  78 404 completa.txt
 20  97 502 total
*/

int main(int argc, char **argv) {

	if (argc < 3) {
		fprintf(stderr, "Argumentos inválidos\n");
		return 1;
	}

	bool flag_l = false;
	bool flag_w = false;
	bool flag_b = false;

	// Invariante de ciclo
	int i = 1;
	// Arreglo que contiene las posiciones de los flags
	int flags[3] = {0};

	for (; i < argc; ++i) {

		if (strcmp(argv[i], "-l") == 0) {
			flag_l = true;
			flags[0] = i;
		} else if (strcmp(argv[i], "-w") == 0) {
			flag_w = true;
			flags[1] = i;
		} else if (strcmp(argv[i], "-c") == 0) {
			flag_b = true;
			flags[2] = i;
		} else if (strlen(argv[i]) < 3) {    // Si el argumento es menor a 3 no es un flag valido ni un archivo
			fprintf(stderr, "Argumento inválido.\n");
			return 1;
		}
	}

	// Si no se recibio al menos uno de los flags -l, -w, -c, se imprime error
	if (!flag_l && !flag_w && !flag_b) {
		fprintf(stderr, "Argumentos inválidos. No se detectan flags\n");
		return 1;
	}

	printf("Flags: %s%s%s\n", flag_l ? "l" : "", flag_w ? "w" : "", flag_b ? "c" : "");

	size_t total_lineas = 0;
	size_t total_palabras = 0;
	size_t total_bytes = 0;

	size_t cant_archivos = 0;

	int j = 1;
	for (; j < argc; ++j) {

		if (j == flags[0] || j == flags[1] || j == flags[2])
			continue;

		size_t cant_lineas = 0;
		size_t cant_palabras = 0;
		size_t cant_bytes = 0;

		cant_archivos++;

		FILE *f = fopen(argv[j], "r");
		if (f == NULL) {
			fprintf(stderr, "No se pudo abrir el archivo <%s>\n", argv[j]);
			return 1;
		}

		int c;
		while ((c = fgetc(f)) != EOF) {

			if (c == '\n') {
				++cant_lineas;
				++cant_palabras;
			}

			if (c == ' ' || c == '\t')
				++cant_palabras;

			++cant_bytes;
		}

		fclose(f);

		total_lineas += cant_lineas;
		total_palabras += cant_palabras;
		total_bytes += cant_bytes;

		if (flag_l)
			printf("%zu ", cant_lineas);
		if (flag_w)
			printf("%zu ", cant_palabras);
		if (flag_b)
			printf("%zu ", cant_bytes);

		printf("%s\n", argv[j]);
	}

	// Si se recibio mas de un archivo, se imprime el total
	if (cant_archivos > 1) {
		if (flag_l)
			printf("%zu ", total_lineas);
		if (flag_w)
			printf("%zu ", total_palabras);
		if (flag_b)
			printf("%zu ", total_bytes);
		printf("total\n");
	}

	return 0;
}

#elif N_EJERCICIO == -5

/* Escriba un programa que lea uno o varios archivos de texto e imprima únicamente las líneas
del mismo que contengan una determinada palabra pasada como primer argumento al programa:

$ ./mi_grep morena texto.txt
dime dónde vas, morena

$ ./mi_grep morena texto.txt completa.txt
texto.txt:dime dónde vas, morena
completa.txt:dime dónde vas, morena
completa.txt:Dime dónde vas, morena
completa.txt:dime dónde vas, morena

$ ./mi_grep modelo texto.txt completa.txt
completa.txt:Voy a la cárcel modelo

Opcional: permita que programa reciba un argumento, -n, que indique que se desea imprimir
el número de línea correspondiente.

$ ./mi_grep -n morena texto.txt completa.txt
texto.txt:3:dime dónde vas, morena
completa.txt:3:dime dónde vas, morena
completa.txt:9:Dime dónde vas, morena
completa.txt:11:dime dónde vas, morena

*/

#define CASE_INSENSITIVE 1

/**
 * @brief Lee una linea de longitud indefinida
 * @pre El archivo viene abierto en modo lectura
 * @param  *f: Archivo abierto en modo texto
 * @retval Cadena de caracteres leida
 */
char *readline_lower(FILE *f, bool lower_cases) {

	int c;

	char *l_ptr = NULL;

	size_t n = 0;

	while ((c = fgetc(f)) != EOF) {

		char *c_aux = realloc(l_ptr, sizeof(char) * (n + 1) + 1);

		if (c_aux == NULL) {
			if (l_ptr != NULL)
				free(l_ptr);
			return NULL;
		}

		l_ptr = c_aux;
		l_ptr[n++] = lower_cases ? tolower(c) : c;
		l_ptr[n] = '\0';

		if (c == '\n')    // Lo pongo aca porque si no, no incluye en la cadena el \n de la linea
			return l_ptr;
	}

	return l_ptr;
}

int main(int argc, char **argv) {

	if (argc < 3) {
		fprintf(stderr, "Argumentos inválidos\n");
		return 1;
	}

	bool flag_n = false;

	// Invariante de ciclo
	int i = 1;
	// Arreglo que contiene las posiciones de los flags
	int flags[2] = {0};

	char *palabra_clave = argv[1];

	for (; i < argc; ++i) {

		if (strcmp(argv[i], "-n") == 0) {
			flag_n = true;
			flags[0] = i;
			palabra_clave = argv[i + 1];
			flags[1] = i + 1;

		} else if (strlen(argv[i]) < 3) {    // Si el argumento es menor a 3 no es un flag valido ni un archivo
			fprintf(stderr, "Argumento inválido.\n");
			return 1;
		}
	}

	printf("Flags: %s\n", flag_n ? "n" : "Ninguno");

	for (int j = 2; j < argc; ++j) {

		if (j == flags[0] || j == flags[1])
			continue;

		FILE *f = fopen(argv[j], "r");
		if (f == NULL) {
			fprintf(stderr, "No se pudo abrir el archivo <%s>\n", argv[j]);
			return 1;
		}

		size_t linea = 1;

		char *l_ptr = NULL;
		char *coincidencia = NULL;

		while ((l_ptr = readline_lower(f, CASE_INSENSITIVE)) != NULL) {

			++linea;

			coincidencia = strstr(l_ptr, palabra_clave);

			if (coincidencia != NULL) {
				printf("%s : ", argv[j]);
				if (flag_n)
					printf("%zu : ", linea);
				printf("%s", l_ptr);
			}

			free(l_ptr);
		}

		fclose(f);

		if (coincidencia != NULL)
			printf("\n\n");
	}

	return 0;
}

#elif N_EJERCICIO == -6

/*
Escriba un programa que reciba 2 cadenas, nueva y vieja, y reemplace todas las ocurrencias
de vieja por nueva, en los archivos pasados como argumento.

$ ./mi_sed "vieja frase" "somos progre" archivo.txt archivo.tex

*/

/**
 * @brief Lee una linea de longitud indefinida
 * @pre El archivo viene abierto en modo lectura
 * @param  *f: Archivo abierto en modo texto
 * @retval Cadena de caracteres leida
 */
char *readline(FILE *f) {

	int c;

	char *l_ptr = NULL;

	size_t n = 0;

	while ((c = fgetc(f)) != EOF) {

		char *c_aux = realloc(l_ptr, sizeof(char) * (n + 1) + 1);

		if (c_aux == NULL) {
			if (l_ptr != NULL)
				free(l_ptr);
			return NULL;
		}

		l_ptr = c_aux;
		l_ptr[n++] = c;
		l_ptr[n] = '\0';

		if (c == '\n')    // Lo pongo aca porque si no, no incluye en la cadena el \n de la linea
			return l_ptr;
	}

	return l_ptr;
}

char *actualizar_cadena(const char *dest, const char *palabra_nueva, const char *palabra_vieja) {


	//Hago un backup de la cadena
	char *c_aux_backup = malloc(sizeof(char) * (strlen(dest) + 1));
	if (c_aux_backup == NULL)
		return NULL;

	strcpy(c_aux_backup, dest);

	// Cuento cuantas veces aparece la palabra vieja
	size_t veces = 0;
	char *aux_dest_p = c_aux_backup;
	while ((aux_dest_p = strstr(aux_dest_p, palabra_vieja)) != NULL) {
		++veces;
		aux_dest_p += strlen(palabra_vieja);
	}

	// Si no aparece la palabra vieja, no hago nada
	if (veces == 0)
		return c_aux_backup;

	// Reservo memoria para la nueva cadena
	char *nueva_cadena = malloc(sizeof(char) * (strlen(dest) + veces * strlen(palabra_nueva) + 1));    // Tamaño de la cadena + veces * (tamaño de la palabra nueva - tamaño de la palabra vieja) + 1 para el \0
	if (nueva_cadena == NULL) {
		free(c_aux_backup);
		return NULL;
	}
	//Inicializo la cadena
	memset(nueva_cadena, 0, sizeof(char) * (strlen(dest) + veces * strlen(palabra_nueva) + 1));

	char *token = strtok(c_aux_backup, " ");
	while (token != NULL) {

		if (strcmp(token, palabra_vieja) == 0)
			memcpy(nueva_cadena, palabra_nueva, strlen(palabra_nueva));
		else
			memcpy(nueva_cadena, token, strlen(token));
		memcpy(nueva_cadena + strlen(token), " ", 1);

		token = strtok(NULL, " ");
	}

	// nueva_cadena[strlen(nueva_cadena)] = '\0';

	free(c_aux_backup);

	// printf("%s\n", nueva_cadena);

	return nueva_cadena;
}

int main(int argc, char **argv) {

    //Imprimo los argumentos
    // for (int i = 0; i < argc; ++i)
    //     printf("->%s ", argv[i]);

	if (argc < 4) {
		fprintf(stderr, "Argumentos inválidos. Uso: ./main <frase_vieja> <frase_nueva> <archivo/s>\n");
		return 1;
	}

	const char *str_original = argv[1];
	// const size_t str_original_len = strlen(str_original);

	const char *str_nueva = argv[2];
	// const size_t str_nueva_len = strlen(str_nueva);

	for (size_t i = 3; i < argc; ++i) {

		FILE *f = fopen(argv[i], "r");
		if (f == NULL) {
			fprintf(stderr, "Error al abrir el archivo\n");
			return 1;
		}

		//Archivo de swap
		FILE *f_tmp = fopen("tmp_aux.txt", "w");
		if (f_tmp == NULL) {
			fprintf(stderr, "Error al abrir el archivo swap\n");
			return 1;
		}

		char *l_ptr = NULL;

		while ((l_ptr = readline(f))  != NULL) {

			// printf("%s\n", l_ptr);

			// Actualizar cadena
			// printf("%s\n", l_ptr);
			char *c_aux = actualizar_cadena(l_ptr, str_nueva, str_original);
			// printf("%s\n", c_aux);

			if (c_aux == NULL) {
			    fprintf(stderr, "Error al actualizar la cadena\n");
			    return 1;
			}

			// Escribo en el archivo de swap
			fprintf(f_tmp, "%s\n", c_aux);

			// fprintf(f_tmp, "%s", l_ptr);
			// Escribo en el archivo de swap
			// fputs(c_aux, f_tmp);
			// fputs("\n", f_tmp);

			// free(c_aux);

			free(c_aux);
			free(l_ptr);

		}

		free(l_ptr);

		fclose(f_tmp);
		fclose(f);
	}

	return 0;
}

#endif

#if N_EJERCICIO == 1

int main(int argc, char *argv[]) {

	if (argc != 3) {
		fprintf(stderr, "Argumentos inválidos. Uso: ./main <nombre de archivo destino> <frase centinela>\n");
		return 1;
	}

	FILE *archivo = fopen(argv[1], "wt");

	if (archivo == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo para guardar\n");
		return 1;
	}

	printf("*** Guardaré todo lo que escribas en el archivo: %s ***\n", argv[1]);
	printf("*** Para terminar, el centinela es: %s***\n", argv[2]);
	char buffer[100];
	size_t n = 0;
	char *v;
	size_t pedidos = 20;
	while (fgets(buffer, 100, stdin) != NULL) {
		if (n == pedidos) {
			char *aux = realloc(v, (pedidos + 20) * sizeof(char));
			if (aux == NULL) {
				free(v);
				fprintf(stderr, "No alcanzó la memoria\n");
				return 1;
			}
			v = aux;
			pedidos += 20;
		}
		v = buffer;
		n++;
		if (strncmp(v, argv[2], strlen(v) - 1) == 0) {    // Si el buffer es igual al centinela (sin el \n)
			break;
		}
		if (fputs(v, archivo) == EOF) {
			fprintf(stderr, "Fatal error\n");
			return 1;
		}
	}

	printf("*** Hasta acá llegamos ***\n");
	fclose(archivo);
	// free(v);

	return 0;
}

#elif N_EJERCICIO == 2

/*
Escriba un programa que copie un archivo de texto. Utilice argumentos en línea de comandos para indicar el archivo
de entrada y el archivo de salida.
*/

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Argumentos inválidos. Uso: %s <nombre de archivo origen> <nombre de archivo destino>\n", argv[0]);
		return 1;
	}
	FILE *fi = fopen(argv[1], "rt");
	if (fi == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo %s", argv[1]);
		return 1;
	}
	FILE *fo = fopen(argv[2], "wt");
	if (fo == NULL) {
		fclose(fi);
		fprintf(stderr, "No se pudo abrir el archivo %s", argv[2]);
		return 1;
	}
	int c;
	while ((c = fgetc(fi)) != EOF)
		fputc(c, fo);
	fclose(fi);
	fclose(fo);
	return 0;
}

#elif N_EJERCICIO == 3

/*
Escriba un programa que lea un archivo de texto y lo imprima, agregando en número de línea al comienzo:

$ ./numerar texto.txt
1: Ayer te vi que subías
2: por el camino a la fuente
3: dime dónde vas, morena
4: dime dónde vas, salada.
Opcional: agregue un argumento al programa para indicar en qué número debe comenzar a imprimir. Interpretación libre.
*/

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Argumentos inválidos. Uso: %s <nombre de archivo a leer>\n", argv[0]);
		return 1;
	}
	FILE *fi = fopen(argv[1], "rt");
	if (fi == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo\n");
		return 1;
	}
	int i = 1;
	char buff[100];
	while (fgets(buff, 100, fi) != NULL) {
		printf("%d: ", i);
		printf("%s", buff);
		i++;
	}
	fclose(fi);
	return 0;
}

#elif N_EJERCICIO == 4

/*
Escriba un programa que cuente la cantidad de líneas de un archivo, si el programa recibe el argumento -l.
Opcionalmente, agregue al programa la posibilidad de contar palabras si recibe el argumento -w y bytes si recibe
el argumento -c. Si recibe más de un archivo como argumento, imprime los totales, como se muestra a continuación:

$ ./mi_wc -l texto.txt
4 texto.txt
$ ./mi_wc -c texto.txt
98 texto.txt
$ ./mi_wc -w texto.txt
19 texto.txt
$ ./mi_wc -l -c -w texto.txt
 4 19 98 texto.txt
$ ./mi_wc -c -w -l texto.txt
 4 19 98 texto.txt
$ ./mi_wc -w -l -c texto.txt completa.txt
  4  19  98 texto.txt
 16  78 404 completa.txt
 20  97 502 total
*/

int main(int argc, char *argv[]) {    // No hice la parte opcional porque me daba paja. Tengo sueño, me voy a dormir... zzz...
	if (argc != 3 || strcmp(argv[1], "-l")) {
		fprintf(stderr, "Argumentos inválidos. Uso: %s -l <nombre de archivo a leer>\n", argv[0]);
		return 1;
	}
	FILE *fi = fopen(argv[2], "rt");
	if (fi == NULL) {
		fprintf(stderr, "No se pudo abrir el archivo\n");
		return 1;
	}
	int i = 1;
	char buff[100];
	while (fgets(buff, 100, fi) != NULL) {
		i++;
	}
	printf("El archivo %s tiene %d líneas.\n", argv[2], i);
	fclose(fi);
	return 0;
}

#elif N_EJERCICIO == 5

/* Escriba un programa que lea uno o varios archivos de texto e imprima únicamente las líneas
del mismo que contengan una determinada palabra pasada como primer argumento al programa:

$ ./mi_grep morena texto.txt
dime dónde vas, morena
$ ./mi_grep morena texto.txt completa.txt
texto.txt:dime dónde vas, morena
completa.txt:dime dónde vas, morena
completa.txt:Dime dónde vas, morena
completa.txt:dime dónde vas, morena
$ ./mi_grep modelo texto.txt completa.txt
completa.txt:Voy a la cárcel modelo

Opcional: permita que programa reciba un argumento, -n, que indique que se desea imprimir
el número de línea correspondiente.

$ ./mi_grep -n morena texto.txt completa.txt
texto.txt:3:dime dónde vas, morena
completa.txt:3:dime dónde vas, morena
completa.txt:9:Dime dónde vas, morena
completa.txt:11:dime dónde vas, morena

*/

int main(int argc, char **argv) {

	if (argc < 2) {
		fprintf(stderr, "Argumentos inválidos. Uso: ./mi_grep <palabra a buscar> <nombre de archivo/s a leer>\n");
		return 1;
	}

	bool flag_n = false;

	size_t n;
	for (n = 2; n < argc; n++) {
		if (strcmp(argv[n], "-n") == 0) {
			flag_n = true;
			break;
		}
	}

	for (size_t i = 2; i < argc; i++) {

		if (i != n) {

			FILE *fi = fopen(argv[i], "rt");
			if (fi == NULL) {
				fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[i]);
				return 1;
			}

			char buff[100];
			size_t j = 1;
			while (fgets(buff, 100, fi) != NULL) {
				if (strstr(buff, argv[1]) != NULL) {
					if (flag_n)
						printf("%s:%zd:%s", argv[i], j, buff);
					else
						printf("%s:%s", argv[i], buff);
				}
				j++;
			}

			fclose(fi);
			putchar('\n');
		}
	}

	putchar('\n');
	return 0;
}

#elif N_EJERCICIO == 6
/*
Escriba un programa que reciba 2 cadenas, nueva y vieja, y reemplace todas las ocurrencias
de vieja por nueva, en los archivos pasados como argumento.

$ ./mi_sed "vieja frase" "somos progre" archivo.txt archivo.tex

*/

int main(int argc, char **argv) {

	if (argc != 5) {
		fprintf(stderr, "Argumentos inválidos. Uso: ./mi_sed <frase_vieja> <frase_nueva> <archivo/s>\n");
	}

	// argv[1] y argv[2] -> Frase vieja y nueva
	for (size_t i = 3; i < argc; i++) {
		FILE *f = fopen(argv[i], "r+");
		if (f == NULL) {
			fprintf(stderr, "Error al abrir el archivo\n");
			return 1;
		}
	}

	return 0;
}

#endif    // Archivos de texto

/* -------------------------------------------------------------------------- */
/*                              Archivos Binarios                             */
/* -------------------------------------------------------------------------- */

#if N_EJERCICIO == 7

int main(void) {

	return 0;
}

#elif N_EJERCICIO == 8

int main(void) {

	return 0;
}

#elif N_EJERCICIO == 9

int main(void) {

	return 0;
}

#elif N_EJERCICIO == 10

int main(void) {

	return 0;
}

#endif    // Archivos Binarios

/* -------------------------------------------------------------------------- */
/*                                 Aplicacion                                 */
/* -------------------------------------------------------------------------- */

#if N_EJERCICIO == 11

int main(void) {

	return 0;
}

#elif N_EJERCICIO == 12

int main(void) {

	return 0;
}

#endif    // Aplicacion
