/**
 * @file parser.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/parser.h"

/**
 * @brief   Imprime por consola una breve ayuda sobre como usar el programa.
 * @retval None
 */
static void __print_usage_help() {

	printf("\n=============================== Ayuda ==============================\n");
	putchar('\n');
	printf("Uso: ./main <ancho> <alto> <nombre_archivo>\n");
	putchar('\n');
	printf("\t<ancho>\t\t\tAncho de la imagen\n");
	printf("\t<alto>\t\t\tAlto de la imagen\n");
	printf("\t<nombre_archivo>\tNombre del archivo a generar\n");
	putchar('\n');
	printf("Las extensiones de archivo validas son:\n");
	printf("\t.ppm\n");
	printf("\t.bmp\n");
	putchar('\n');
	printf("Ejemplo:\n");
	printf("\t./main 640  480 imagen.ppm\n");
	printf("\t./main 640  480 imagen.bmp\n");
	printf("\n====================================================================\n");
}

/**
 * @brief   Verifica que la extension del archivo sea valida.
 * @param  *raw_data: Puntero a un arreglo de caracteres que contiene el nombre del archivo.
 * @param  *ppm_bmp: Puntero a un entero donde se almacenara el tipo de archivo.
 * @retval bool: True si la extension es valida, False en caso contrario.
 */
static bool __is_a_valid_extension(const char *raw_data, int *ppm_bmp) {

	if (raw_data[0] == '.') {
		__print_usage_help();
		fprintf(stderr, "\nError: El nombre de archivo no puede iniciar con un punto\n");
		return 0;
	}

	size_t dot_pos = 0;
	size_t dot_cnt = 0;
	for (size_t i = 0; raw_data[i] && dot_cnt < 2; i++) {

		if (raw_data[i] == '.') {
			dot_cnt++;
			dot_pos = i;
		}

		if (!isalnum(raw_data[i]) && raw_data[i] != '.') {
			__print_usage_help();
			fprintf(stderr, "\nError: El nombre de archivo no puede contener caracteres especiales\n");
			return 0;
		}
	}

	if (dot_cnt != 1) {
		__print_usage_help();
		fprintf(stderr, "\nError: El nombre de archivo debe contener un unico punto\n");
		return 0;
	}

	char ext_aux[4];

	for (size_t i = dot_pos + 1; raw_data[i]; i++) {    // dot_pos + 1 -> Siguiente caracter al .
		if (i - dot_pos > 3) {
			__print_usage_help();
			fprintf(stderr, "\nError: La extension es demasiado larga. Solo se admite .ppm o .bmp\n");
			return 0;
		}
		ext_aux[i - dot_pos - 1] = raw_data[i];
	}
	ext_aux[3] = '\0';

	if (strcmp(ext_aux, "ppm") == 0) {
		*ppm_bmp = FT_PPM;
		return 1;
	}

	if (strcmp(ext_aux, "bmp") == 0) {
		*ppm_bmp = FT_BMP;
		return 1;
	}

	__print_usage_help();
	fprintf(stderr, "\nError: La extension es invalida. Solo se admite .ppm o .bmp\n");
	return 0;
}

bool is_a_valid_input(int argc, char *argv[], int *ancho, int *alto, int *extension) {

	if (argc != 4) {
		__print_usage_help();
		fprintf(stderr, "\nError: Cantidad de argumentos incorrecta\n");
		return 0;
	}

	char *errPtr;

	// Ancho
	*ancho = strtol(argv[1], &errPtr, 10);
	if (*errPtr != '\0') {
		__print_usage_help();
		fprintf(stderr, "\nError: El ancho de la imagen no es un numero\n");
		return 0;
	}

	// Alto
	*alto = strtol(argv[2], &errPtr, 10);
	if (*errPtr != '\0') {
		__print_usage_help();
		fprintf(stderr, "\nError: El alto de la imagen no es un numero\n");
		return 0;
	}

	if (*ancho <= 0 || *alto <= 0) {
		__print_usage_help();
		fprintf(stderr, "\nError: Las dimensiones de la imagen deben ser un numero positivo\n");
		return 0;
	}

	// Extension
	if (__is_a_valid_extension(argv[3], extension)) return 1;

	return 0;
}
