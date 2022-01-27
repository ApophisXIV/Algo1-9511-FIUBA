#include <assert.h>
#include <stdio.h>
#include <string.h>

void merge(const int a[], size_t na, const int b[], size_t nb, int r[]) {

    //Caso base
    if(na == 0){ //Si la lista a esta vacia
        for(int i = 0; i < nb; i++) //Agrego todo lo restante de la lista b
            r[i] = b[i];
        return;
    }
    if(nb == 0){ //Si la lista b esta vacia
        for(int i = 0; i < na; i++) //Agrego todo lo restante de la lista a
            r[i] = a[i];
        return;
    }

    if (*a == *b) {
        *r = *a;
        *(r + 1) = *b;
        merge(a + 1, na - 1, b + 1, nb - 1, r + 2);
    }

    else if (*a < *b) {
        *r = *a;
        merge(a + 1, na - 1, b, nb, r + 1);
    }

    else {
        *r = *b;
        merge(a, na, b + 1, nb - 1, r + 1);
    }
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
