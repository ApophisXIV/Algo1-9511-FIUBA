#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

void contar_caracteres(const char *s, size_t cantidades[256]) {
    // HACER: implementar la funcion
}

bool nota_rescate_posible(const char *nota, const char *revista) {
    // HACER: implementar la funcion
}

int main(void) {
    const char *revista = "El viejo Senor Gomez pedia queso, kiwi y habas, pero le ha tocado un saxofon";

    assert(nota_rescate_posible("hola que tal", revista));

    // la revista tiene solo una 't' y necesitamos 2
    assert(!nota_rescate_posible("hola que tal como estas", revista));

    // OPCIONAL: Pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}

