#include <stdio.h>

#define n 3

#include <stdbool.h>
#include <math.h>

#if n == 1

int mi_atoi(const char s[]) {

    int resultado = 0;

    for (size_t i = 0; s[i]; i++) {

        resultado = (resultado * 10 + (s[i] - '0'));
    }

    return resultado;
}

int main(void) {

    const char *numero = "75029511";

    printf("\n%d\n", mi_atoi(numero));
}

#elif n == 2

#define FILAS 3
#define COLUMNAS 4

bool tiene_paridad(int m[FILAS][COLUMNAS], size_t filas, size_t columnas) {

    for (size_t i = 0; i < filas; i++) {
        for (size_t j = 0; j < columnas; j++) {
            
            if(((i + j) % 2) != (m[i][j] % 2))
                return false;
        }
    }

    return true;
}

int main(void) {

    int matriz[FILAS][COLUMNAS] = {
        {4, 9, 6, 7},
        {5, 8, 1, 8},
        {0, 2, 3, 1},
    };

    printf("Tiene paridad? %s\n",tiene_paridad(matriz, FILAS, COLUMNAS) ? "SI" : "NO");
}

#elif n == 3

#include <stdlib.h>

float pH (float H30){
    return log10(1 / H30);
}

int main(void) {

    printf("Ingrese un valor de concentracion de H3O+. Recuerde que este debe ser mayor a 0 y menor o igual a 1\n");

    char buffer[10];
    char *errPtr = NULL;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL){

        float H3O = strtof(buffer,&errPtr);

        if((*errPtr != '\0' || *errPtr != '\n') && (H3O > 1 || H3O <= 0 ))
            printf("Vuelva a intentarlo. El valor ingresado es invalido.\n");
        else
            printf("El pH calculado es %1.2f\n",pH(H3O));
    }

}
#endif