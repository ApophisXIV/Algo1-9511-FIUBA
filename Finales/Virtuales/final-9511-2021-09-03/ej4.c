#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#define YEAR_MASK 0x7F
#define MONTH_MASK 0xFF
#define DAY_MASK 0x1F

#define DAY_SHIFT 7
#define MONTH_SHIFT 12

#define MIN_DATE 0x1001
#define YEAR_OFFSET 0x7D0

uint16_t empaquetar_fecha(unsigned int dia, unsigned int mes, unsigned int anio) {

    //! IMPORTANT: No se valida la coherencia de las fechas (E.g.: Año bisiesto, Meses con 30 o 31 dias)

    if (anio < 2000 || anio > 2127)
        return 0;
    if (mes < 1 || mes > 12)
        return 0;
    if (dia < 1 || dia > 31)
        return 0;

    return (mes & MONTH_MASK) << MONTH_SHIFT | (dia & DAY_MASK) << DAY_SHIFT | ((anio & ~YEAR_OFFSET) & YEAR_MASK);
}

void desempaquetar_fecha(uint16_t reg, unsigned int *dia, unsigned int *mes, unsigned int *anio) {

    if (reg < MIN_DATE)
        return;

    *dia = (reg >> DAY_SHIFT) & DAY_MASK;
    *mes = (reg >> MONTH_SHIFT) & MONTH_MASK;
    *anio = (reg & YEAR_MASK) | YEAR_OFFSET;
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
