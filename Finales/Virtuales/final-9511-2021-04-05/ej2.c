#include <stdio.h>
#include <assert.h>

// HACER: declarar el tipo de dato
typedef ??? reg_t;

// HACER: implementar las funciones

reg_t *reg_crear(size_t n) {
}

bool reg_rshift(reg_t *r, bool v) {
}

bool reg_lshift(reg_t *r, bool v) {
}

void reg_destruir(reg_t *r) {
}

int main(void) {
    reg_t *r = reg_crear(8);       // 00000000

    assert(reg_rshift(r, 0) == 0); // 00000000 -> 0
    assert(reg_rshift(r, 1) == 0); // 10000000 -> 0
    assert(reg_rshift(r, 0) == 0); // 01000000 -> 0
    assert(reg_rshift(r, 0) == 0); // 00100000 -> 0
    assert(reg_rshift(r, 0) == 0); // 00010000 -> 0
    assert(reg_rshift(r, 0) == 0); // 00001000 -> 0
    assert(reg_rshift(r, 0) == 0); // 00000100 -> 0
    assert(reg_rshift(r, 0) == 0); // 00000010 -> 0
    assert(reg_rshift(r, 0) == 0); // 00000001 -> 0
    assert(reg_rshift(r, 0) == 1); // 00000000 -> 1
    assert(reg_rshift(r, 0) == 0); // 00000000 -> 0

    // OPCIONAL: pruebas adicionales (ej: probar reg_lshift)

    reg_destruir(r);

    printf("%s: OK\n", __FILE__);
    return 0;
}

