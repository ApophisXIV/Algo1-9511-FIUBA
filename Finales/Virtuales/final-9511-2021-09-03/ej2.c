#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool file_cpy(const char *file_src, const char *file_dst) {

	FILE *f_src = fopen(file_src, "rb");
	if (f_src == NULL)
		return false;

	FILE *f_dst = fopen(file_dst, "wb");
	if (f_dst == NULL) {
		fclose(f_src);
		return false;
	}

	char buffer[1024];    // Lectura en chunks de 1kB
	size_t bytes_leidos = 0;

	while ((bytes_leidos = fread(buffer, sizeof(buffer), 1, f_src)) != 0)
		if (fwrite(buffer, sizeof(buffer), bytes_leidos, f_dst) != bytes_leidos) {
			fclose(f_src);
			fclose(f_dst);
			return false;
		}

	fclose(f_src);
	fclose(f_dst);
	return true;
}

int main(int argc, char *argv[]) {
	// HACER: implementar el programa.

	// Probarlo con: ./ej2 foto.jpg copia.jpg

	if (argc != 3) {
		fprintf(stderr, "Uso: ./ej1 foto.jpg copia.jpg\n");
		return 1;
	}

	assert(file_cpy(argv[1], argv[2]));

	return 0;
}
