#include <assert.h>
#include <stdio.h>
#include <string.h>


// Complejidad temporal: O(n^2) 
// Complejidad espacial: O(n)
void ordenar_burbujeo(int a[], size_t n) {
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 1; j <= n - 1; j++) {
            if (a[j - 1] > a[j]) {
                int aux = a[j - 1];
                a[j - 1] = a[j];
                a[j] = aux;
            }
        }
    }
}

int main(void) {
    int a[] = {3, 7, 2, 9, 5, 6, 2, 3, 1};

    ordenar_burbujeo(a, 9);

    int resultado_esperado[] = {1, 2, 2, 3, 3, 5, 6, 7, 9};
    assert(memcmp(a, resultado_esperado, 9 * sizeof(int)) == 0);

    // OPCIONAL: escribir pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}
