#include <stdio.h>
#include <assert.h>
#include <string.h>

void unir(char destino[], char delimitador, char *cadenas[], size_t n) {
    // HACER: implementar
}

int main(void) {
    char *cadenas[] = { "2021", "04", "05" };
    char s[16];
    unir(s, '-', cadenas, 3);
    assert(!strcmp(s, "2021-04-05"));

    // OPCIONAL: pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}
