#include <stdio.h>
#include <assert.h>
#include <string.h>

void merge(const int a[], size_t na, const int b[], size_t nb, int r[]) {
    // HACER: implementar la funcion en forma RECURSIVA
}


int main(void) {
    const int a[] = {1, 3, 5, 6, 8};
    const size_t na = 5;

    const int b[] = {2, 3, 5, 7, 8, 9};
    const size_t nb = 6;

    int r[na + nb];

    merge(a, na, b, nb, r);

    // resultado esperado
    const int r_esperado[] = {1, 2, 3, 3, 5, 5, 6, 7, 8, 8, 9};
    assert(memcmp(r, r_esperado, (na + nb) * sizeof(int)) == 0);

    // OPCIONAL: escribir pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}

