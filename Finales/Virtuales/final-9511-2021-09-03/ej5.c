#include <stdio.h>
#include <assert.h>
#include <string.h>

void intercalar(char a[], char b[], char r[]) {
    // HACER: implementar la funcion en forma RECURSIVA
}

int main(void) {
    char r[32];

    intercalar("hola", "mundo!", r);

    assert(!strcmp(r, "hmoulnado!"));

    // OPCIONAL: Pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}

