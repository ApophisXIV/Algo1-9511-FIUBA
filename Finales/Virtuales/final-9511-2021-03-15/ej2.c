#include <stdio.h>
#include <assert.h>

/* HACER:

Escribir una funcion que recibe un archivo previamente abierto y los datos de una sucursal,
y escribe en el archivo los datos con el formato descripto.

Escribir una funcion que recibe un archivo previamente abierto, lee los datos de una sucursal
y los devuelve (ya sea por el valor de retorno o mediante los parametros).

*/

int main(void) {
    char *nombre = "Caballito 1";
    float lat, lon = -34.6145096f, -58.4431307f;

    char *nombre_archivo = "sucursal.bin";

    // PRUEBA:
    // - abrir el archivo en modo escritura y escribir en el mismo los datos de la sucursal
    // - abrir el archivo en modo lectura y leer del mismo los datos previamente escritos
    // - verificar con assert() que los datos leidos son correctos

    printf("%s: OK\n", __FILE__);
    return 0;
}
