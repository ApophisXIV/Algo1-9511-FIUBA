#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// HACER: implementar las funciones

bool matriz_guardar(const char *nombre, size_t n, size_t m, float matriz[n][m]) {
    
    if (nombre == NULL || matriz == NULL)
        return false;

    FILE *f = fopen(nombre, "wb");
    if (f == NULL)
        return false;

    if(fwrite(&n, sizeof(size_t), 1, f) != 1){
        fclose(f);
        return false;
    }

    if(fwrite(&m, sizeof(size_t), 1, f) != 1){
        fclose(f);
        return false;
    }

    if(fwrite(matriz, sizeof(float), n * m, f) != n * m){
        fclose(f);
        return false;
    }

    fclose(f);
    return true;
}

float *matriz_cargar(const char *nombre, size_t *n, size_t *m) {
    if(nombre == NULL || n == NULL || m == NULL)
        return NULL;
    
    FILE *f = fopen(nombre, "rb");
    if (f == NULL)
        return NULL;

    if(fread(n, sizeof(size_t), 1, f) != 1){
        fclose(f);
        return NULL;
    }

    if(fread(m, sizeof(size_t), 1, f) != 1){
        fclose(f);
        return NULL;
    }

    float *matriz = malloc(*n * *m * sizeof(float));
    if (matriz == NULL) {
        fclose(f);
        return NULL;
    }

    if(fread(matriz, sizeof(float), *n * *m, f) != *n * *m){
        fclose(f);
        free(matriz);
        return NULL;
    }

    fclose(f);
    return matriz;
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
    float(*matriz_leida)[m] = (float(*)[m])p;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            assert(matriz_leida[i][j] == matriz[i][j]);
        }
    }

    free(p);

    printf("%s: OK\n", __FILE__);
    return 0;
}

//4 min