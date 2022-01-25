#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// HACER: definir el tipo vecf_t

vecf_t *vecf_crear() {
    // HACER: implementar la funcion
}

void vecf_destruir(vecf_t *v) {
    // HACER: implementar la funcion
}

size_t vecf_cantidad(const vecf_t *v) {
    // HACER: implementar la funcion
}

bool vecf_agregar(vecf_t *v, float f) {
    // HACER: implementar la funcion
}

float vecf_suma(const vecf_t *v) {
    // HACER: implementar la funcion
}


int main(void) {
    vecf_t *v = vecf_crear();
    assert(v != NULL);
    assert(vecf_cantidad(v) == 0);

    vecf_agregar(v, 4.0f);
    assert(vecf_cantidad(v) == 1);

    vecf_agregar(v, 10.5f);
    assert(vecf_cantidad(v) == 2);

    assert(vecf_suma(v) == 14.5f);

    vecf_destruir(v);

    // OPCIONAL: Pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}

