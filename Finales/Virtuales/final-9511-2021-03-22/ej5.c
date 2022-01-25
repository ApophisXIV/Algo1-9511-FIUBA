#include <stdio.h>

// HACER: implementar la funcion.
// Recomendacion: pensarla en forma recursiva.
// Puede que sea necesario crear funciones auxiliares.

void combinaciones(char caracteres[], size_t n, size_t k) {
}

int main(void) {
    char caracteres[] = {'a', 'b', 'c', 'd'};
    size_t n = 4;
    size_t k = 2;
    combinaciones(caracteres, n, k);

    // debe imprimir:
    //
    //  ab
    //  ac
    //  ad
    //  bc
    //  bd
    //  cd

    return 0;
}
