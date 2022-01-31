#include <assert.h>
#include <stdio.h>
#include <string.h>

void unir(char destino[], char delimitador, char *cadenas[], size_t n) {
    if (cadenas == NULL || n == 0)
        return;

    for (size_t i = 0; i < n - 1; i++) {
        strcat(destino, cadenas[i]);
        strcat(destino, &delimitador);
    }
    strcat(destino, cadenas[n - 1]);
}

int main(void) {
    char *cadenas[] = {"2021", "04", "05"};
    char s[16];
    unir(s, '-', cadenas, 3);
    assert(!strcmp(s, "2021-04-05"));

    // OPCIONAL: pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}

//2 min