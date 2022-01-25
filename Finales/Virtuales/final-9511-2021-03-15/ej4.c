#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

// HACER: implementar la funcion
// NO se permite usar funciones de la biblioteca estandar

void hex_codificar(uint32_t n, char *s) {
}

int main(void) {
    char s[10];
    hex_codificar(0x3f4, s);
    assert(!strcmp(s, "3f4"));

    // OPCIONAL: Pruebas adicionales. Sugerencias:
    // - 0x0
    // - 0x1
    // - 0xffffffff
    // - 0x80000000

    printf("%s: OK\n", __FILE__);
    return 0;
}
