#include <stdio.h>
#include <assert.h>
#include <string.h>

void ordenar_burbujeo(int a[], size_t n) {
    // HACER: implementar la funcion
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
