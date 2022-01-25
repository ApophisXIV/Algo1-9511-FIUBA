#include <stdio.h>
#include <assert.h>

// HACER: declarar el tipo persona_t

persona_t *persona_crear(int dni, const char *nombre, const char *direccion) {
    // HACER: implementar la funcion
}

void persona_destruir(persona_t *p) {
    // HACER: implementar la funcion
}

persona_t *persona_buscar(int dni, persona_t *personas[], size_t n) {
    // HACER: implementar la funcion
}

int main(void) {
    persona_t *personas[] = {
        persona_crear(11111, "persona 1", "direccion 1"),
        persona_crear(22222, "persona 2", "direccion 2"),
        persona_crear(33333, "persona 3", "direccion 3"),
        persona_crear(44444, "persona 4", "direccion 4"),
    };

    persona_t *p = persona_buscar(33333, personas, 4);
    assert(p == personas[2]);

    // OPCIONAL: pruebas adicionales

    for (int i = 0; i < 4; i++) {
        persona_destruir(personas[i]);
    }

    printf("%s: OK\n", __FILE__);
    return 0;
}

