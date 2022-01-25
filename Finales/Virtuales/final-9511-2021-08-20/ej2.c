#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

bool invertir_endianness(const char *entrada, const char *salida) {
    // HACER: implementar la funcion
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

