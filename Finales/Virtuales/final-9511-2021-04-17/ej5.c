#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// HACER: implementar los tipos de datos necesarios y las funciones

typedef struct ??? cuenta_t;

cuenta_t *cuenta_crear(const char *nombre) {
}

const char *cuenta_nombre(const cuenta_t *c) {
}

uint64_t cuenta_saldo(const cuenta_t *c) {
}

bool cuenta_acreditar(cuenta_t *c, uint64_t cantidad, const char *descripcion) {
}

bool cuenta_extraer(cuenta_t *c, uint64_t cantidad, const char *descripcion) {
}

void cuenta_movimientos(cuenta_t *c, void f(int64_t cantidad, const char *descripcion)) {
}

void cuenta_destruir(cuenta_t *c) {
}

// esto se utiliza en las pruebas
static uint64_t saldo_verificado = 0;
void sumar_movimiento(int64_t cantidad, const char *descripcion) {
    saldo_verificado += cantidad;
}

int main(void) {
    cuenta_t *c = cuenta_crear("Perez");
    assert(!strcmp(cuenta_nombre(c), "Perez"));
    assert(cuenta_saldo(c) == 0);
    cuenta_acreditar(c, 100, "Sueldo");
    assert(cuenta_saldo(c) == 100);
    assert(cuenta_extraer(c, 60, "Shopping") == true);
    assert(cuenta_saldo(c) == 40);
    assert(cuenta_extraer(c, 100, "Deudas") == false);
    assert(cuenta_saldo(c) == 40);

    cuenta_movimientos(c, sumar_movimiento);
    assert(saldo_verificado == 40);

    cuenta_destruir(c);

    printf("%s: OK\n", __FILE__);
    return 0;
}
