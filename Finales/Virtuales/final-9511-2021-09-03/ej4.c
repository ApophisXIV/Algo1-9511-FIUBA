#include <stdio.h>
#include <assert.h>
#include <stdint.h>

uint16_t empaquetar_fecha(unsigned int dia, unsigned int mes, unsigned int anio) {
    // HACER: implementar la funcion
}

void desempaquetar_fecha(uint16_t reg, unsigned int *dia, unsigned int *mes, unsigned int *anio) {
    // HACER: implementar la funcion
}

int main(void) {
    //  0 1 0 0|0 0 0 1 0|0 0 0 0 0 0 1
    //     4   |    2    |     2001

    assert(empaquetar_fecha(2, 4, 2001) == 0x4101);

    unsigned int dia, mes, anio;
    desempaquetar_fecha(0x4101, &dia, &mes, &anio);
    assert(dia == 2);
    assert(mes == 4);
    assert(anio == 2001);

    // OPCIONAL: Pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}
