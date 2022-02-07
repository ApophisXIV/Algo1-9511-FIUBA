#include <stdio.h>
#include <assert.h>
#include <stddef.h>

// Escribir la función int buscar(const char *s, const char *p), que encuentra el
// primer caracter de s que coincide con alguno de los caracteres de p, y devuelve su posición, o
// -1 en caso de no encontrarlo.
int buscar(const char *s, const char *p) {
    if(s == NULL || p == NULL) return -1;
    if(*p == '\0') return -1;
    if(*s == '\0') return -1;

    size_t i = 0;
    const char* pos_inicial = s;

    while (*p != '\0') {
        for (i = 0; s[i] != '\0'; i++)
            if (s[i] == *p)
                return i;
        s = pos_inicial;
        p++;
    }

    return -1;
}

int main(void) {
    assert(buscar("algoritmos", "qrst") == 4);

    // OPCIONAL: escribir pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}
