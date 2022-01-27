#include <assert.h>
#include <stdio.h>
#include <string.h>

void separar_con_guiones(const char *s, char r[]) {

    if (s[0] == '\0') {
        r[0] = '\0';
        return;    // Se llego al final de la cadena
    }

    if (s[0] == s[1]) {
        r[0] = s[0];
        r[1] = '-';
        separar_con_guiones(s + 1, r + 2);
    }

    else {
        r[0] = s[0];
        separar_con_guiones(s + 1, r + 1);
    }
}

int main(int argc, char *argv[]) {
    char r[128];

    separar_con_guiones("hola", r);
    fprintf(stderr, "%s\n", r);
    assert(!strcmp(r, "hola"));

    separar_con_guiones("abbcdde", r);
    fprintf(stderr, "%s\n", r);
    assert(!strcmp(r, "ab-bcd-de"));

    separar_con_guiones("aaaa", r);
    fprintf(stderr, "%s\n", r);
    assert(!strcmp(r, "a-a-a-a"));

    // OPCIONAL: Pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}

// 22 min