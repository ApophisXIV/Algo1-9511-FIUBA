#include <assert.h>
#include <stdio.h>

void interseccion(const int a[], size_t na, const int b[], size_t nb, int r[], size_t *nr) {
    // HACER: implementar la funcion
    // Asumir que r tiene espacio suficiente.
    *nr = 0;
    for (size_t i = 0, j = 0; i < na && j < nb;) {

        if (a[i] == b[j]) {
            r[(*nr)++] = a[i++];
            j++;
        }

        else if (a[i] < b[j])
            i++;

        else
            j++;
    }
}

int main(void) {
    int a[] = {2, 5, 7, 9, 10, 10, 13, 15, 18};
    int b[] = {0, 1, 2, 2, 7, 10, 12, 15};

    int r[10];
    size_t nr;
    interseccion(a, 9, b, 8, r, &nr);

    int r_esperado[] = {2, 7, 10, 15};
    assert(nr == 4);
    for (int i = 0; i < nr; i++)
        assert(r[i] == r_esperado[i]);

    // OPCIONAL: escribir pruebas adicionales
    int a2[] = {2, 5, 7, 9};
    int b2[] = {0, 1, 2, 2, 7, 9, 10, 12, 12, 15};

    int r2[10];
    size_t nr2;
    interseccion(a2, 4, b2, 10, r2, &nr2);

    int r_esperado2[] = {2, 7, 9};
    assert(nr2 == 3);
    for (int i = 0; i < nr2; i++)
        assert(r2[i] == r_esperado2[i]);

    printf("%s: OK\n", __FILE__);
    return 0;
}
