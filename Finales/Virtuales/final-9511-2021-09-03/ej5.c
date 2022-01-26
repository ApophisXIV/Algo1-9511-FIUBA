#include <assert.h>
#include <stdio.h>
#include <string.h>

void intercalar(char a[], char b[], char r[]) {

    if (a[0] == '\0' && b[0] != '\0') {
        strcpy(r, b);    // copia lo que resta de b en r
        return;
    }

    if (b[0] == '\0' && a[0] != '\0') {
        strcpy(r, a);    // copia lo que resta de a en r
        return;
    }

    r[0] = a[0];
    r[1] = b[0];

    // printf("a: %c b: %c r: %s\n", a[0], b[0], r);

    intercalar(a + 1, b + 1, r + 2);
}

int main(void) {
    char r[32];

    intercalar("hola", "mundo!", r);

    printf("%s\n", r);

    assert(!strcmp(r, "hmoulnado!"));

    // OPCIONAL: Pruebas adicionales

    intercalar("mundo", "hola!", r);

    printf("%s\n", r);

    assert(!strcmp(r, "mhuonldao!"));

    printf("%s: OK\n", __FILE__);

    return 0;
}
