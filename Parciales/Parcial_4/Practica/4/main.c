#include <assert.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_EJERCICIO 1

#if N_EJERCICIO == 1
/* 1. Se quiere implementar un sistema de turnos diario para un médico. Los turnos se dan cada 15 minutos y
se representan por la concatenación de hora y minutos, por ejemplo 1815 representa las 18:15.
Declarar la estructura que encapsula el TDA. Explicar qué representa cada miembro y documentar
claramente el invariante de representación.
Implementar la primitiva char *turno_consultar(const turnos_t *t, int horario); que devuelva el paciente que tiene turno
en ese horario o NULL si el turno no estuviera ocupado. Implementar la primitiva bool turno_asignar(turnos_t *t, int
horario, const char *paciente); que asigne el turno de ese horario al paciente, sólo si el mismo no estuviera ya
ocupado, si estuviera ocupado sería un error*/

// TODO: implementar

// typedef struct

// char *turno_consultar(const turnos_t *t, int horario) {
// }
// bool turno_asignar(turnos_t *t, int horario, const char *paciente) {
// }

#elif N_EJERCICIO == 2

/* 2.

a. Implementar una función
bool matriz_escribir(FILE *f, float **matriz, size_t n, size_t m);
que escriba una matriz de R n×m elementos en el archivo binario f.

b. Implementar una función
float matriz_leer_suma(FILE *f); que devuelva la suma de todos los elementos de una matriz volcada en el archivo f. En caso de falla
devolver FLT_MAX de <float.h>.

El formato queda a diseño del alumno. Ambas funciones deben validar la lectura/escritura.*/

bool matriz_escribir(FILE *f, float **matriz, size_t n, size_t m) {

    //Imprimir por consola la matriz
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            printf("%f ", matriz[i][j]);
        }
        printf("\n");
    }

	if (f == NULL) {
		return false;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fwrite(&matriz[i][j], sizeof(float), 1, f);
		}
	}

	return true;
}

float matriz_leer_suma(FILE *f) {

    if (f == NULL) {
		return FLT_MAX;
	}

	float suma = 0;
	float num;

	while (fread(&num, sizeof(float), 1, f) == 1) {
		suma += num;
	}

	return suma;
}

float **crear_matriz_en_heap(size_t n, size_t m) {
    float **matriz = malloc(n * sizeof(float *));
    if (matriz == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        matriz[i] = malloc(m * sizeof(float));
        if (matriz[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(matriz[j]);
            }
            free(matriz);
            return NULL;
        }
    }

    return matriz;
}

int main() {

	float matriz[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    float **matriz_heap = crear_matriz_en_heap(3, 3);
    if (matriz_heap == NULL)
        printf("Error al crear la matriz en heap\n");

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matriz_heap[i][j] = matriz[i][j];
        }
    }

	FILE *f = fopen("matriz.bin", "wb");
	if (f == NULL) {
		printf("Error al abrir el archivo\n");
		return 1;
	}

    matriz_escribir(f, matriz_heap, 3, 3);

	fclose(f);

	f = fopen("matriz.bin", "rb");

	float suma = matriz_leer_suma(f);

	fclose(f);

	// Suma esperada: 45

	printf("La suma de los elementos de la matriz es %f\n", suma);

	return 0;
}

#elif N_EJERCICIO == 3

/*3. Escribir un programa que se ejecute como:
$ ./cut --bytes=[n]-[m] [archivo]
que imprima por pantalla el contenido del archivo que esté entre la posición n y la m para cada una de
sus líneas.
Por ejemplo
$ ./cut --bytes=5-20 archivo.txt
imprimirá para cada línea 15 caracteres desde la posición 5*/

void imprimir_linea_rango(FILE *f, int n, int m) {
	int c;
	int i = 0;
	while ((c = fgetc(f)) != EOF) {
		if (c == '\n') {
			printf("\n");
			i = 0;
		}
		if (i >= n && i <= m) {
			printf("%c", c);
		}
		i++;
	}

	fclose(f);
}

int main(int argc, char **argv) {

	if (argc != 3) {
		printf("Error en los argumentos\n");
		return 1;
	}

	char *arg = argv[1];

	arg += strlen("--bytes=");

	char *n = strtok(arg, "-");
	char *m = strtok(NULL, "-");

	int num_n = atoi(n);
	int num_m = atoi(m);

	// Abrimos el archivo
	FILE *f = fopen(argv[2], "r");
	if (f == NULL) {
		printf("Error al abrir el archivo\n");
		return 1;
	}

	imprimir_linea_rango(f, num_n, num_m);

	return 0;
}

#endif