#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

// HACER: declarar el tipo de dato e implementar las funciones pedidas
typedef ??? conjunto_t;

conjunto_t *conjunto_crear(size_t k) {
}

void conjunto_agregar(conjunto_t *c, int n) {
}

void conjunto_quitar(conjunto_t *c, int n) {
}

bool conjunto_pertenece(const conjunto_t *c, int n) {
}

void conjunto_eliminar(conjunto_t *c) {
}

int main(void) {
    conjunto_t *c = conjunto_crear(10); // los numeros deben ser entre 0 y 9
    assert(c != NULL);

    assert(!conjunto_pertenece(c, 5));
    conjunto_agregar(c, 5);
    assert(conjunto_pertenece(c, 5));
    conjunto_quitar(c, 5);
    assert(!conjunto_pertenece(c, 5));

    conjunto_eliminar(c);

    // OPCIONAL: Pruebas adicionales. Sugerencias:
    // - agregar mas numeros
    // - agregar un numero que ya pertenece
    // - quitar un numero que no pertenece

    printf("%s: OK\n", __FILE__);
    return 0;
}
