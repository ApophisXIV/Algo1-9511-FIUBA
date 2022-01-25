#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

// Valor Caracter  Valor Caracter  Valor Caracter  Valor Caracter
//     0 A             9 J            18 S            27 3
//     1 B            10 K            19 T            28 4
//     2 C            11 L            20 U            29 5
//     3 D            12 M            21 V            30 6
//     4 E            13 N            22 W            31 7
//     5 F            14 O            23 X
//     6 G            15 P            24 Y
//     7 H            16 Q            25 Z
//     8 I            17 R            26 2

void base32_codificar(uint8_t bytes[], size_t n, char s[]) {
    // HACER: implementar la funcion
    // Asumir que n es multiplo de 5, y que s tiene espacio suficiente
}


int main(void) {
    uint8_t bytes[] = {'A', 'B', 'C', 'D', 'E'};
    char s[16];
    base32_codificar(bytes, 5, s);

    /*
     *        A         B         C        D        E
     * 01000001  01000010  01000011 01000100 01000101
     * \      |    \      |     |    \     \
     * 01000 00101 00001 00100 00110 10001 00010 00101
     *     I     F     B     E     G     R     C     F
     */

    printf("%s\n", s);
    assert(!strcmp(s, "IFBEGRCF"));

    printf("%s: OK\n", __FILE__);
    return 0;
}
