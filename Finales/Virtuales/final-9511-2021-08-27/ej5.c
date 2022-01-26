#include <assert.h>
#include <stdint.h>
#include <stdio.h>

size_t cant_bits(const uint32_t a[], size_t n) {

    size_t bits_set = 0;

    for (size_t i = 0; i < n; i++)
        for (size_t bits = 0; bits < 32; bits++)
            bits_set += ((a[i] >> bits) & 0x01);

    return bits_set;
}

int main(void) {
    //              1, 10, 11, 100   :  5 bits encencidos
    uint32_t a[] = {1, 2, 3, 4};

    size_t n = cant_bits(a, 4);
    assert(n == 5);

    printf("%s: OK\n", __FILE__);
    return 0;
}

// 8 min