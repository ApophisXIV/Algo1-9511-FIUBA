#include <stdio.h>
#include <assert.h>

void interseccion(const int a[], size_t na, const int b[], size_t nb, int r[], size_t *nr) {
    // HACER: implementar la funcion
    // Asumir que r tiene espacio suficiente.
}

int main(void) {
    int a[] = {      2,    5, 7, 9, 10, 10,     13, 15, 18};
    int b[] = {0, 1, 2, 2,    7,    10,     12,     15};

    int r[10];
    size_t nr;
    interseccion(a, 9, b, 8, r, &nr);

    int r_esperado[] = {2, 7, 10, 15};
    assert(nr == 4);
    for (int i = 0; i < nr; i++) assert(r[i] == r_esperado[i]);

    // OPCIONAL: escribir pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}
