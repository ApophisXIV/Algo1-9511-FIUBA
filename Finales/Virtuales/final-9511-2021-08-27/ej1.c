#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

// HACER: declarar el tipo sucursal_t

void sucursal_destruir(sucursal_t *s) {
    // HACER: implementar la funcion
}

bool leer_sucursales(const char *nombre_archivo, sucursal_t *sucursales[], size_t *cantidad) {
    // HACER: implementar la funcion
}

int main(void) {
    sucursal_t *sucursales[10];
    size_t n;

    bool ok = leer_sucursales("sucursales.bin", sucursales, &n);
    assert(ok);
    assert(n == 3);

    // OPCIONAL: verificar con assert los datos de las sucursales.
    // Deberían ser:
    // - lat: -34.0  long: -58.0  nombre: "Sucursal A"
    // - lat: -35.0  long: -56.0  nombre: "Sucursal B"
    // - lat: -33.0  long: -57.0  nombre: "Sucursal C"

    for (int i = 0; i < n; i++) {
        sucursal_destruir(sucursales[i]);
    }

    printf("%s: OK\n", __FILE__);
    return 0;
}

