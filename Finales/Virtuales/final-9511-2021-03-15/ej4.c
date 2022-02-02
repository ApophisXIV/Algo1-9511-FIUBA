#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// HACER: implementar la funcion
// NO se permite usar funciones de la biblioteca estandar

char hex_to_char(uint8_t hex) {
    if (hex >= 0 && hex <= 9)
        return hex + '0';
    if (hex >= 10 && hex <= 15)
        return hex - 10 + 'a';
    return '\0';
}

size_t n_digitos(uint32_t n, const size_t base) {
    size_t n_digitos = 0;
    while (n > 0) {
        n_digitos++;
        n /= base;
    }
    return n_digitos;
}

void hex_codificar(uint32_t n, char *s) {
    size_t n_dig = n_digitos(n, 16);
    if (n_dig == 0)
        n_dig = 1;
    for (int i = n_dig - 1; i >= 0; i--)
        s[n_dig - i - 1] = hex_to_char((n >> i * 4) & 0xF);
    s[n_dig] = '\0';
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

    hex_codificar(0x0, s);
    assert(!strcmp(s, "0"));

    hex_codificar(0x1, s);
    assert(!strcmp(s, "1"));

    hex_codificar(0xffffffff, s);
    assert(!strcmp(s, "ffffffff"));

    hex_codificar(0x80000000, s);
    assert(!strcmp(s, "80000000"));

    printf("%s: OK\n", __FILE__);
    return 0;
}

// 27 min