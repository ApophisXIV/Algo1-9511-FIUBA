#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define INVERTIR_ENDIANNESS(x)   \
    (((x) >> 24) |               \
    (((x) >> 8)  & 0x0000FF00) | \
    (((x) << 8)  & 0x00FF0000) | \
    ((x) << 24))

bool invertir_endianness(const char *entrada, const char *salida) {

    if (entrada == NULL || salida == NULL)
        return false;

    FILE *f = fopen(entrada, "rb");
    if (f == NULL)
        return false;

    FILE *out = fopen(salida, "wb");
    if (out == NULL) {
        fclose(f);
        return false;
    }

    uint32_t numero;
    while (fread(&numero, sizeof(uint32_t), 1, f) == 1) {
        numero = INVERTIR_ENDIANNESS(numero);
        if(fwrite(&numero, sizeof(uint32_t), 1, out) != 1) {
            fclose(f);
            fclose(out);
            return false;
        }
    }

    return true;
}

int main(void) {
    // numeros.bin contiene 3 numeros de 32 bits (mostrado aqui en hexadecimal):
    //   00 01 02 03  04 05 06 07  08 09 0a 0b
    //
    // invertido.bin debe contener:
    //   03 02 01 00  07 06 05 04  0b 0a 09 08
    //
    assert(invertir_endianness("numeros.bin", "invertido.bin"));

    printf("%s: OK (verificar el contenido de invertido.bin)\n", __FILE__);
    printf("\nNota: para visualizar el contenido en formato hexadecimal:\n");
    printf("  od -t x1 numeros.bin\n");
    printf("  od -t x1 invertido.bin\n");
}

// 22 min