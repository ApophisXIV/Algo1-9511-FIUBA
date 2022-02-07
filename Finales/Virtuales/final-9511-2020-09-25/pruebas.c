#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "unicode.h"

#define EJERCICIO1_HABILITADO
#define EJERCICIO2_HABILITADO
#define EJERCICIO3_HABILITADO
#define EJERCICIO4_HABILITADO
#define EJERCICIO5_HABILITADO

#define verificar(condicion) do { \
        if (!(condicion)) { \
            printf("Prueba fallida en %s:%d: %s\n", __FILE__, __LINE__, #condicion); \
            return false; \
        } \
    } while (0)

#ifdef EJERCICIO1_HABILITADO
static bool ejercicio1(void) {
    {
        uchar_t s[] = {'\0'};
        verificar(unicode_longitud(s) == 0);
    }
    {
        uchar_t s[] = {'h', 'o', 'l', 'a', '\0'};
        verificar(unicode_longitud(s) == 4);
    }
    {
        uchar_t hola[]  = {'h', 'o', 'l', 'a', '\0'};
        uchar_t hola2[] = {'h', 'o', 'l', 'a', '!', '\0'};
        uchar_t mando[] = {'m', 'a', 'n', 'd', 'o', '\0'};
        uchar_t mundo[] = {'m', 'u', 'n', 'd', 'o', '\0'};
        uchar_t z[]     = {'z', '\0'};

        verificar(unicode_comparar(hola, hola) == 0);
        verificar(unicode_comparar(hola, hola2) < 0);
        verificar(unicode_comparar(hola2, hola) > 0);
        verificar(unicode_comparar(hola2, mando) < 0);
        verificar(unicode_comparar(mando, hola2) > 0);
        verificar(unicode_comparar(mando, mundo) < 0);
        verificar(unicode_comparar(mundo, mando) > 0);
        verificar(unicode_comparar(hola2, mundo) < 0);
        verificar(unicode_comparar(mundo, hola2) > 0);
        verificar(unicode_comparar(hola, mundo) < 0);
        verificar(unicode_comparar(mundo, hola) > 0);
        verificar(unicode_comparar(mundo, z) < 0);
        verificar(unicode_comparar(z, mundo) > 0);
    }

    return true;
}
#endif

#ifdef EJERCICIO2_HABILITADO
static bool ejercicio2(void) {
    {
        uchar_t s[15] = {0};

        uchar_t hola[]  = {'h', 'o', 'l', 'a', '\0'};
        uchar_t mundo[] = {' ', 'm', 'u', 'n', 'd', 'o', '!', '\0'};

        unicode_concatenar(s, hola);
        verificar(unicode_longitud(s) == 4);
        verificar(unicode_comparar(s, (uchar_t[]){'h', 'o', 'l', 'a', '\0'}) == 0);

        unicode_concatenar(s, mundo);
        verificar(unicode_longitud(s) == 11);
        verificar(unicode_comparar(s, (uchar_t[]){'h', 'o', 'l', 'a', ' ', 'm', 'u', 'n', 'd', 'o', '!', '\0'}) == 0);
    }
    {
        //                      0    1    2    3    4    5
        uchar_t s[15]       = {'h', 'o', 'l', 'a', '!', '\0'};
        uchar_t mundo[]     = {' ', 'm', 'u', 'n', 'd', 'o', '\0'};

        unicode_insertar(s, 4, mundo);

        //                      0    1    2    3    4    5    6    7    8    9    10    11
        //                                         [---------------------------]
        uchar_t resultado[] = {'h', 'o', 'l', 'a', ' ', 'm', 'u', 'n', 'd', 'o', '!', '\0'};

        verificar(unicode_longitud(s) == 11);
        verificar(unicode_comparar(s, resultado) == 0);
    }
    return true;
}
#endif

#ifdef EJERCICIO3_HABILITADO
static bool ejercicio3(void) {
    uint8_t cadena_utf8[] = {
        0x24, // U+0024
        0xC2, 0xA2, // U+00A2
        0xE0, 0xA4, 0xB9, // U+0939
        0xED, 0x95, 0x9C, // U+D55C
        0xF0, 0x90, 0x8D, 0x88, // U+10348
        0, // NUL
    };

    uchar_t s[15] = {0};
    unicode_decodificar_utf8(s, cadena_utf8);

    uchar_t esperado[] = {
        0x00000024,
        0x000000A2,
        0x00000939,
        0x0000D55C,
        0x00010348,
        0,
    };
    for (int i = 0; i < 6; i++) {
        // printf("i=%d: s[i]=0x%x -- esperado[i]=0x%x\n", i, s[i], esperado[i]);
        verificar(s[i] == esperado[i]);
    }

    return true;
}
#endif

#ifdef EJERCICIO4_HABILITADO
static bool ejercicio4(void) {
    uchar_t s[] = {
        0x00000024,
        0x000000A2,
        0x00000939,
        0x0000D55C,
        0x00010348,
        0,
    };
    uint8_t cadena_utf8[20] = {0};
    unicode_codificar_utf8(s, cadena_utf8);

    uint8_t cadena_utf8_esperada[] = {
        0x24, // U+0024
        0xC2, 0xA2, // U+00A2
        0xE0, 0xA4, 0xB9, // U+0939
        0xED, 0x95, 0x9C, // U+D55C
        0xF0, 0x90, 0x8D, 0x88, // U+10348
        0, // NUL
    };
    for (int i = 0; i < 14; i++) {
        // printf("i=%d: cadena_utf8[i]=0x%x -- cadena_utf8_esperada[i]=0x%x\n", i, cadena_utf8[i], cadena_utf8_esperada[i]);
        verificar(cadena_utf8[i] == cadena_utf8_esperada[i]);
    }
    return true;
}
#endif

#ifdef EJERCICIO5_HABILITADO
static long tamagno_archivo(const char *nombre_archivo) {
    FILE *f = fopen(nombre_archivo, "rb");
    long tamagno = 0;
    if (fseek(f, 0, SEEK_END) == 0)
        tamagno = ftell(f);
    fclose(f);
    return tamagno;
}

static bool ejercicio5(void) {
    uchar_t *s = unicode_leer_archivo_utf8("utf8.txt");
    verificar(s != NULL);

    verificar(unicode_longitud(s) == 7167);

    bool ok = unicode_escribir_archivo_utf8(s, "utf8-2.txt");
    verificar(ok);

    verificar(tamagno_archivo("utf8.txt") == tamagno_archivo("utf8-2.txt"));

    free(s);

    return true;
}
#endif

int main(void) {
    bool ok;
    int ejercicios_ok = 0;

    #ifdef EJERCICIO1_HABILITADO
        srand(0);
        ok = ejercicio1();
        printf("ejercicio 1: %s\n", ok ? "OK" : "FAIL");
        if (ok) ejercicios_ok++;
    #endif

    #ifdef EJERCICIO2_HABILITADO
        srand(0);
        ok = ejercicio2();
        printf("ejercicio 2: %s\n", ok ? "OK" : "FAIL");
        if (ok) ejercicios_ok++;
    #endif

    #ifdef EJERCICIO3_HABILITADO
        srand(0);
        ok = ejercicio3();
        printf("ejercicio 3: %s\n", ok ? "OK" : "FAIL");
        if (ok) ejercicios_ok++;
    #endif

    #ifdef EJERCICIO4_HABILITADO
        srand(0);
        ok = ejercicio4();
        printf("ejercicio 4: %s\n", ok ? "OK" : "FAIL");
        if (ok) ejercicios_ok++;
    #endif

    #ifdef EJERCICIO5_HABILITADO
        srand(0);
        ok = ejercicio5();
        printf("ejercicio 5: %s\n", ok ? "OK" : "FAIL");
        if (ok) ejercicios_ok++;
    #endif

    printf("Cantidad de ejercicios OK: %d\n", ejercicios_ok);
    return 0;
}
