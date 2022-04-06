
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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