#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA 128

// HACER: implementar el programa
//
// Probarlo con: ./ej3 texto.txt
// Deberia imprimir:
//
// con el cantar se consuela.
// como la ave solitaria
// una pena estraordinaria,
// que el hombre que lo desvela
// al compas de la viguela,
// Aqui me pongo a cantar

void free_text(char **ss, size_t n) {
    for (size_t i = 0; i < n; i++)
        free(ss[i]);
    free(ss);
}

char **dump_text(size_t *n, const char *file) {

    FILE *f = fopen(file, "r");
    if (f == NULL) {
        perror("No se pudo abrir el archivo\n");
        return NULL;
    }

    *n = 0;
    char buffer[MAX_LINEA];
    char **ss = NULL;

    while (fgets(buffer, MAX_LINEA, f) != NULL) {

        char **aux = realloc(ss, (*n + 1) * sizeof(char *));
        if (aux == NULL) {
            fclose(f);
            free_text(ss, *n);
            return NULL;
        }

        ss = aux;

        char *s_texto = malloc((strlen(buffer) + 1) * sizeof(char));
        if (s_texto == NULL) {
            fclose(f);
            free_text(ss, *n);
            return NULL;
        }

        strcpy(s_texto, buffer);
        ss[(*n)++] = s_texto;
    }

    fclose(f);
    return ss;
}

int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "Error. Uso: ./ej3 <nombre_archivo>\n");
        return 1;
    }

    size_t n;
    char **texto = dump_text(&n, argv[1]);
    if (texto == NULL) {
        fprintf(stderr, "Error. Ocurrio un error en la lectura\n");
        return 1;
    }

    printf("Tiene %zu lineas\n", n);

    for (int i = n - 1; i >= 0; --i) {
        printf("%s", texto[i]);
    }

    free_text(texto, n);

    return 0;
}