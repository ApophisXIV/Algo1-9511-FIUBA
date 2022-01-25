#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

// HACER: implementar las funciones

bool matriz_guardar(const char *nombre, size_t n, size_t m, float matriz[n][m]) {
}

float *matriz_cargar(const char *nombre, size_t *n, size_t *m) {
}


int main(void) {
    float matriz[2][3] = {
        {1, 2, 3},
        {4, 5, 6},
    };

    assert(matriz_guardar("matriz.bin", 2, 3, matriz));

    size_t n, m;
    float *p = matriz_cargar("matriz.bin", &n, &m);
    assert(p != NULL);
    assert(n == 2);
    assert(m == 3);

    // hacemos el casteo al tipo de matriz
    float (*matriz_leida)[m] = (float (*)[m])p;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            assert(matriz_leida[i][j] == matriz[i][j]);
        }
    }

    free(p);

    printf("%s: OK\n", __FILE__);
    return 0;
}

