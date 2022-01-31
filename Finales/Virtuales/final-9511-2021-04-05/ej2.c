#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// HACER: declarar el tipo de dato
typedef struct {
    uint8_t *chunks;
    size_t n_bytes;
} reg_t;

// HACER: implementar las funciones

void reg_print(reg_t *reg) {
    for (size_t i = 0; i < reg->n_bytes; i++) {
        for (int j = 7; j >= 0; j--) {
            printf("%d", (reg->chunks[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

reg_t *reg_crear(size_t n) {
    if (n == 0)
        return NULL;

    reg_t *r = malloc(sizeof(reg_t));
    if (r == NULL)
        return NULL;

    r->chunks = calloc(n, sizeof(uint8_t));
    if (r->chunks == NULL) {
        free(r);
        return NULL;
    }

    r->n_bytes = n % 8 == 0 ? n / 8 : n / 8 + 1;

    return r;
}

bool reg_rshift(reg_t *r, bool v) {
    if (r == NULL)
        return false;

    const bool LSB = r->chunks[0] & 0x01;

    for (int i = 0; i < r->n_bytes; i++) {
        r->chunks[i] >>= 1;
        if (i + 1 < r->n_bytes)
            r->chunks[i] |= (r->chunks[i + 1] & 1) << 7;
        else
            r->chunks[i] |= v << 7;
    }

    return LSB;
}

bool reg_lshift(reg_t *r, bool v) {
    if (r == NULL)
        return false;

    const bool MSB = r->chunks[r->n_bytes-1] & 0x80;

    for (int i = r->n_bytes - 1; i >= 0; i--) {
        r->chunks[i] <<= 1;
        if (i - 1 > 0)
            r->chunks[i] |= (r->chunks[i - 1] & 0x80) >> 7;
        else
            r->chunks[i] |= v;
    }

    return MSB;
}

void reg_destruir(reg_t *r) {
    if (r == NULL)
        return;
    free(r->chunks);
    free(r);
}

int main(void) {
    reg_t *r = reg_crear(8);    // 00000000

    reg_print(r);
    assert(reg_rshift(r, 0) == 0);    // 00000000 -> 0
    reg_print(r);
    assert(reg_rshift(r, 1) == 0);    // 10000000 -> 0
    reg_print(r);
    assert(reg_rshift(r, 0) == 0);    // 01000000 -> 0
    reg_print(r);
    assert(reg_rshift(r, 0) == 0);    // 00100000 -> 0
    reg_print(r);
    assert(reg_rshift(r, 0) == 0);    // 00010000 -> 0
    reg_print(r);
    assert(reg_rshift(r, 0) == 0);    // 00001000 -> 0
    reg_print(r);
    assert(reg_rshift(r, 0) == 0);    // 00000100 -> 0
    reg_print(r);
    assert(reg_rshift(r, 0) == 0);    // 00000010 -> 0
    reg_print(r);
    assert(reg_rshift(r, 0) == 0);    // 00000001 -> 0
    reg_print(r);
    assert(reg_rshift(r, 0) == 1);    // 00000000 -> 1
    reg_print(r);
    assert(reg_rshift(r, 0) == 0);    // 00000000 -> 0
    reg_print(r);

    printf("\n");

    // OPCIONAL: pruebas adicionales (ej: probar reg_lshift)
    assert(reg_lshift(r, 0) == 0);    // 00000000 -> 0
    reg_print(r);
    assert(reg_lshift(r, 1) == 0);    // 00000001 -> 0
    reg_print(r);
    assert(reg_lshift(r, 0) == 0);    // 00000010 -> 0
    reg_print(r);
    assert(reg_lshift(r, 0) == 0);    // 00000100 -> 0
    reg_print(r);
    assert(reg_lshift(r, 0) == 0);    // 00001000 -> 0
    reg_print(r);
    assert(reg_lshift(r, 0) == 0);    // 00010000 -> 0
    reg_print(r);
    assert(reg_lshift(r, 0) == 0);    // 00100000 -> 0
    reg_print(r);
    assert(reg_lshift(r, 0) == 0);    // 01000000 -> 0
    reg_print(r);
    assert(reg_lshift(r, 0) == 0);    // 10000000 -> 0
    reg_print(r);
    assert(reg_lshift(r, 0) == 1);    // 00000000 -> 1
    reg_print(r);

    reg_destruir(r);

    printf("%s: OK\n", __FILE__);
    return 0;
}

// 23 min