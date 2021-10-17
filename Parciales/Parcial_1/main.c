/**
 * @file main.c
 * @author Rodriguez Guido Ezequiel (guerodriguez@fi.uba.ar)
 * @Note Padron 108723
 * @version 0.1
 * @date 2021-10-15
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define N_Ejercicio 3

#if N_Ejercicio == 1

bool tiene_extension(const char archivo[], const char extension[]) {

    size_t le = 0, la = 0;

    for (le = 0; extension[le]; le++)
        ;
    for (la = 0; archivo[la]; la++)
        ;

    if (la < le) {
        return false;
    }

    for (size_t i = 0; i < le; i++)
        if (archivo[i + la - le] != extension[i])
            return false;

    return true;
}

int main(void) {

    printf("%s\n", tiene_extension("txt.txts", ".txt") ? "Tiene la extension" : "No tiene la extension");
    printf("%s\n", tiene_extension("paquete.zip", ".rar") ? "Tiene la extension" : "No tiene la extension");
    printf("%s\n", tiene_extension("main.c", ".c") ? "Tiene la extension" : "No tiene la extension");
    printf("%s\n", tiene_extension("main.h", ".c") ? "Tiene la extension" : "No tiene la extension");
}

#elif N_Ejercicio == 2

#define N 3
#define M 2

bool es_nonegativa(float mat[N][M], size_t n, size_t m) {

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++)
            if (mat[i][j] < 0)
                return false;

    return true;
}

int main(void) {

    float matriz_1[N][M] = {
        {0, 8},
        {9, 1},
        {2, 1}};

    float matriz_2[N][M] = {
        {0, 8},
        {-9, 1},
        {2, 1}};

    printf("La matriz_1 es %s\n", es_nonegativa(matriz_1, N, M) ? "POSITIVA" : "NEGATIVA");
    printf("La matriz_2 es %s\n", es_nonegativa(matriz_2, N, M) ? "POSITIVA" : "NEGATIVA");
}

#elif N_Ejercicio == 3

#define BUFFER_SIZE 10
#define GRADOS_MAX 360
#define GRADOS_MIN 0
#define MIN_SEG_MAX 60
#define MIN_SEG_MIN 0

bool entradaValida(const char *mensajeInput, int max, int min) {

    char *errPtr = NULL;
    float aux = strtol(mensajeInput, &errPtr, 10);

    if (errPtr == mensajeInput || *errPtr != '\n')
        return false;

    return aux > max || aux < min ? false : true;
}

float gradosDecimales(int grados[3]) {

    return grados[0] + grados[1] / 60.0 + grados[2] / 3600.0;
}

int main(void) {

    char buffer[BUFFER_SIZE];

    enum mensajeIngresos {
        GRADOS,
        MINUTOS,
        SEGUNDOS,
        CALCULAR
    };

    unsigned int mensajeConsola = GRADOS;

    int datos[3] = {0};

    printf("A continuacion se le solicitaran Grados, Minutos y Segundos.\n");

    printf("Ingrese los GRADOS\n");

    while ((fgets(buffer, sizeof(buffer), stdin) != NULL) && (mensajeConsola != MINUTOS)) {

        if (entradaValida(buffer, GRADOS_MAX, GRADOS_MIN)) {
            datos[0] = atoi(buffer);
            mensajeConsola = MINUTOS;
            break;
        } else {
            printf("Entrada invalida. Intenta de nuevo.\n");
        }
    }

    printf("Ingrese los MINUTOS\n");

    while ((fgets(buffer, sizeof(buffer), stdin) != NULL) && mensajeConsola != SEGUNDOS) {

        if (entradaValida(buffer, MIN_SEG_MAX, MIN_SEG_MIN)) {
            datos[1] = atoi(buffer);
            mensajeConsola = SEGUNDOS;
            break;
        } else {
            printf("Entrada invalida. Intenta de nuevo.\n");
        }
    }

    printf("Ingrese los SEGUNDOS\n");

    while ((fgets(buffer, sizeof(buffer), stdin) != NULL) && mensajeConsola != CALCULAR) {

        if (entradaValida(buffer, MIN_SEG_MAX, MIN_SEG_MIN)) {
            datos[2] = atoi(buffer);
            mensajeConsola = CALCULAR;
            break;

        } else {
            printf("Entrada invalida. Intenta de nuevo.\n");
        }
    }

    printf("Grados: %f\n", gradosDecimales(datos));
}

#endif
