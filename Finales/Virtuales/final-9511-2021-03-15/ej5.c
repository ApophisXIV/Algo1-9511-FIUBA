#include <assert.h>
#include <stdio.h>

// HACER: implementar la funcion

void merge(const int a[], size_t na, const int b[], size_t nb, int r[]) {

    size_t i = 0, j = 0, k = 0;

    while (i < na && j < nb) {
        if (a[i] < b[j])
            r[k++] = a[i++];
        else
            r[k++] = b[j++];
    }

    while (i < na)
        r[k++] = a[i++];

    while (j < nb)
        r[k++] = b[j++];
}

void merge3(const int a[], const size_t na, const int b[], const size_t nb, const int c[], const size_t nc, int r[]) {
    int aux[na + nb]; //TODO: Investigar como evitar el VLA
    merge(a, na, b, nb, aux);
    merge(aux, na + nb, c, nc, r);    
}

void merge3_alt(const int a[], const size_t na, const int b[], const size_t nb, const int c[], const size_t nc, int r[]) {

    size_t i = 0, j = 0, k = 0, l = 0;

    while (i < na && j < nb && k < nc) {
        if (a[i] < b[j]) {
            if (a[i] < c[k])
                r[l++] = a[i++];
            else
                r[l++] = c[k++];
        } else {
            if (b[j] < c[k])
                r[l++] = b[j++];
            else
                r[l++] = c[k++];
        }
    }

    while (i < na)
        r[l++] = a[i++];

    while (j < nb)
        r[l++] = b[j++];

    while (k < nc)  
        r[l++] = c[k++];

}

int main(void) {
    int a[] = {1, 4, 7};
    int b[] = {2, 5, 8};
    int c[] = {3, 6, 9};
    int r[9];

    merge3(a, 3, b, 3, c, 3, r);

    int esperado[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; i++)
        assert(r[i] == esperado[i]);

    // OPCIONAL: Pruebas adicionales. Sugerencias:
    // - Listas con numeros repetidos
    // - Una lista con todos sus numeros menores a las otras dos
    // - Una lista con todos sus numeros mayores a las otras dos

    int a2[] = {1, 1, 8};
    int b2[] = {1, 1, 8};
    int c2[] = {1, 1, 8};
    int r2[9];

    merge3(a2, 3, b2, 3, c2, 3, r2);

    int esperado2[] = {1, 1, 1, 1, 1, 1, 8, 8, 8};

    for (int i = 0; i < 9; i++)
        assert(r2[i] == esperado2[i]);

    int a3[] = {5, 6, 7};
    int b3[] = {1, 2, 3};
    int c3[] = {8, 9, 10};
    int r3[9];

    merge3(a3, 3, b3, 3, c3, 3, r3);

    int esperado3[] = {1, 2, 3, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 9; i++)
        assert(r3[i] == esperado3[i]);

    int a4[] = {1, 2, 3};
    int b4[] = {5, 6, 7};
    int c4[] = {8, 9, 10};
    int r4[9];

    merge3(a4, 3, b4, 3, c4, 3, r4);

    int esperado4[] = {1, 2, 3, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 9; i++)
        assert(r4[i] == esperado4[i]);

    printf("%s: OK\n", __FILE__);
    return 0;
}

//39 min