#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void contar_caracteres(const char *s, size_t cantidades[256]) {
    while (*s)
        cantidades[(unsigned char) *s++]++;
}

bool nota_rescate_posible(const char *nota, const char *revista) {

    size_t c_letras_disponibles[256] = {0};
    contar_caracteres(revista,c_letras_disponibles);

    size_t c_letras_necesarias[256] = {0};
    contar_caracteres(nota,c_letras_necesarias);

    for (int i = 0; i < 256; i++)
        if(c_letras_necesarias[i] > c_letras_disponibles[i])
            return false;
    return true;
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

//16 min