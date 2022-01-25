#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINEA 128

#define LOG_ERR(fmt, ...)                                      \
	do {                                                       \
		fprintf(stderr, fmt " l:%d\n", __VA_ARGS__, __LINE__); \
	} while (0)

bool invertir_lineas(char *entrada, char *salida) {

	if (entrada == NULL || salida == NULL)
		return false;


	FILE *f = fopen(entrada, "r");
	if(f == NULL) {
		LOG_ERR("Error al abrir el archivo %s", entrada);
		return false;
	}

	FILE *f_out = fopen(salida, "w");
	if(f_out == NULL) {
		LOG_ERR("Error al abrir el archivo %s", salida);
		fclose(f);
		return false;
	}

	char linea[MAX_LINEA];
	while(fgets(linea, MAX_LINEA, f) != NULL) {
		//Invierte la linea

		int i = 0;
		int j = strlen(linea) - 1;
		while(i < j) {
			char aux = linea[i];
			linea[i++] = linea[j];
			linea[j--] = aux;
		}

		//Escribe la linea
		fprintf(f_out, "%s", linea);
	}

	fclose(f);
	fclose(f_out);

	return true;
}

int main(int argc, const char *argv[]) {
	assert(invertir_lineas("texto.txt", "invertido.txt"));

	if (argc != 3) {
		LOG_ERR("%s", "Cantidad de argumentos invalida");
		return 1;
	}

	assert(invertir_lineas((char*) argv[1], (char*) argv[2]));

	// texto.txt contiene:
	//
	// Aqui me pongo a cantar
	// al compas de la viguela,
	// que el hombre que lo desvela
	// una pena estraordinaria,
	// como la ave solitaria
	// con el cantar se consuela.

	// invertido.txt deberia contener:
	//
	// ratnac a ognop em iuqA
	// ,aleugiv al ed sapmoc la
	// alevsed ol euq erbmoh le euq
	// ,airanidroartse anep anu
	// airatilos eva al omoc
	// .aleusnoc es ratnac le noc

	printf("%s: OK (verificar el contenido de invertido.txt)\n", __FILE__);
	return 0;
}
