#include <assert.h>
#include <stdio.h>
#include <string.h>

// nota: el guion bajo es porque "union" es una palabra reservada del lenguaje
size_t union_(const int a[], size_t na, const int b[], size_t nb, int r[]) {

    if (na == 0 || nb == 0)
        return 0;

    if (a[0] == b[0]) {
        r[0] = a[0];
        return 1 + union_(a + 1, na - 1, b + 1, nb - 1, r + 1);
    } else if (a[0] < b[0]) {
        r[0] = a[0];
        return 1 + union_(a + 1, na - 1, b, nb, r + 1);
    } else {
        r[0] = b[0];
        return 1 + union_(a, na, b + 1, nb - 1, r + 1);
    }
}

int main(void) {
    int a[] = {1, 3, 5, 7};
    int b[] = {2, 3, 6, 7};

    int r[8];
    size_t nr = union_(a, 4, b, 4, r);

    assert(nr == 6);
    int r_esperado[] = {1, 2, 3, 5, 6, 7};
    assert(memcmp(r, r_esperado, 6 * sizeof(int)) == 0);

    printf("%s: OK\n", __FILE__);
    return 0;
}

// 17 min