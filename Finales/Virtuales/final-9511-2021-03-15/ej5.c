#include <stdio.h>
#include <assert.h>

// HACER: implementar la funcion

void merge3(const int a[], size_t na, const int b[], size_t nb, const int c[], size_t nc, int r[]) {
}

int main(void) {
    int a[] = {1, 4, 7};
    int b[] = {2, 5, 8};
    int c[] = {3, 6, 9};
    int r[9];

    merge3(a, 3, b, 3, c, 3, r);

    int esperado[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; i++) {
        assert(r[i] == esperado[i]);
    }

    // OPCIONAL: Pruebas adicionales. Sugerencias:
    // - Listas con numeros repetidos
    // - Una lista con todos sus numeros menores a las otras dos
    // - Una lista con todos sus numeros mayores a las otras dos

    printf("%s: OK\n", __FILE__);
    return 0;
}
