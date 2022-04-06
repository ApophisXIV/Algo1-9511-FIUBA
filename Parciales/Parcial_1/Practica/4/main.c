#include <stdio.h>

#include <stdbool.h>
#include <stdlib.h>

#define N_Ejercicio_1 1

#ifdef N_Ejercicio_1

#define BUFF_SIZE 10

int posCaracter(const char *s, char delim) {

    for (size_t i = 0; s[i]; i++) {

        if (s[i] == delim)
            return i;
    }

    return -1;    // No se encontro el delimitador
}

bool extraer_par(int par[2], const char s[]) {

    char aux[2][BUFF_SIZE];

    const int delimPos = posCaracter(s, ',');

    if (delimPos == -1 || ((s[delimPos + 1] != '-' || s[delimPos + 1] == '+') && (s[delimPos + 1] < '0' || s[delimPos + 1] > '9'))) {
        return false;
    }

    for (size_t nBuff = 0; nBuff < 2; nBuff++) {

        for (size_t i = 0; nBuff == 0 ? : s[i]; i++) {

            // aux[i]
            //TODO: Complete this function
        }
    }
}

int main(void) {

    int par[2] = {0};

    const char *s = "25,-8\n";

    extraer_par(par, s);

    printf("p1: %d p2: %d\n", par[0], par[1]);
}

#elif defined N_Ejercicio_2
#elif defined N_Ejercicio_3
#endif
