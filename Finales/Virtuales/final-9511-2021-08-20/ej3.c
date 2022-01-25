#include <stdio.h>
#include <string.h>
#include <assert.h>

void separar_con_guiones(const char *s, char r[]) {
    // HACER: implementar la funcion
}

int main(int argc, char *argv[]) {
    char r[128];

    separar_con_guiones("hola", r);
    assert(!strcmp(r, "hola"));

    separar_con_guiones("abbcdde", r);
    assert(!strcmp(r, "ab-bcd-de"));

    separar_con_guiones("aaaa", r);
    assert(!strcmp(r, "a-a-a-a"));

    // OPCIONAL: Pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}

