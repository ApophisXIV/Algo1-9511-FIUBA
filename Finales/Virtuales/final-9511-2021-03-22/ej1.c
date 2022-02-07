#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// HACER: Implementar la funcion. NO se permite usar ninguna funcion de la biblioteca estandar.
bool octal_decodificar(const char s[], uint32_t *n) {
    
    if(s == NULL || n == NULL)
        return false;

    size_t i = 0;
    uint32_t num = 0;

    while (s[i]) {
        if (s[i] >= '0' && s[i] <= '7'){
            num = num * 8 + (s[i] - '0');
            i++;
        }
        else
            return false;
    }

    *n = num;
    return true;
}

int main(void) {
    uint32_t n;
    assert(octal_decodificar("1234567", &n));
    assert(n == 01234567);    // C interpreta un literal que comienza con 0 como notacion octal

    // OPCIONAL: agregar pruebas.  Sugerencias:
    // - Numeros de 1 digito
    // - Casos de error (numero muy grande, cadena vacia, caractees invalidos)

    printf("%s: OK\n", __FILE__);
    return 0;
}

//25 min