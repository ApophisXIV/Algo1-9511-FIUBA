#include <assert.h>
#include <stdint.h>
#include <stdio.h>

uint8_t rotar(uint8_t v, int n) {
    return (uint8_t)(n >= 0 ? (v >> n | v << (8 - n)) : (v << -n | v >> (8 - n)));
}

int main(void) {
    assert(rotar(0x0a, 1) == 0x05);     // 00001010 -> 00000101
    assert(rotar(0x0a, 2) == 0x82);     // 00001010 -> 10000010
    assert(rotar(0x0a, 3) == 0x41);     // 00001010 -> 01000001
    assert(rotar(0x0a, -1) == 0x14);    // 00001010 -> 00010100
    assert(rotar(0x0a, 8) == 0x0a);     // 00001010 -> 00001010
    assert(rotar(0x0a, 0) == 0x0a);     // 00001010 -> 00001010

    // OPCIONAL: escribir pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}
