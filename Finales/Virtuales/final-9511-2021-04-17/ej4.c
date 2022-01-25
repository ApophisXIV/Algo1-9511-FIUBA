#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

bool uniq(const char *entrada, const char *salida) {
    // HACER: implementar la funcion
}

int main(void) {
    uniq("entrada.txt", "salida.txt");

    // salida.txt deberia contener:
    //
    //    I like to move it, move it
    //    Ya like to move it
    //    I like to move it, move it
    //    Ya like to move it

    printf("%s: OK (verificar el contenido de salida.txt)\n", __FILE__);
    return 0;
}
