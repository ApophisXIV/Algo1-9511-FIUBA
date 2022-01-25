#include <stdio.h>
#include <assert.h>
#include <stdint.h>

size_t cant_bits(const uint32_t a[], size_t n) {
    // HACER: implementar la funcion
}

int main(void) {
    //              1, 10, 11, 100   :  5 bits encencidos
    uint32_t a[] = {1,  2,  3,   4};

    size_t n = cant_bits(a, 4);
    assert(n == 5);

    printf("%s: OK\n", __FILE__);
    return 0;
}

