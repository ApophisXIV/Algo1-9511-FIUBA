#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "img.h"

// #define EJERCICIO1_HABILITADO
// #define EJERCICIO2_HABILITADO
// #define EJERCICIO3_HABILITADO
// #define EJERCICIO4_HABILITADO
// #define EJERCICIO5_HABILITADO

#define verificar(condicion) do { \
        if (!(condicion)) { \
            printf("Prueba fallida en %s:%d: %s\n", __FILE__, __LINE__, #condicion); \
            return false; \
        } \
    } while (0)

#ifdef EJERCICIO1_HABILITADO
static bool ejercicio1(void) {
    // pruebas del TDA rgba_t
    rgba_t c = rgba(0x12, 0x34, 0x56, 0x78);
    verificar(rgba_r(c) == 0x12);
    verificar(rgba_g(c) == 0x34);
    verificar(rgba_b(c) == 0x56);
    verificar(rgba_a(c) == 0x78);

    // creamos una imagen
    img_t *img = img_crear(60, 40);
    verificar(img != NULL);
    verificar(img_ancho(img) == 60);
    verificar(img_alto(img) == 40);

    // pintamos cada pixel con un color aleatorio
    for (uint32_t x = 0; x < img_ancho(img); x++) {
        for (uint32_t y = 0; y < img_alto(img); y++) {
            c = rgba(rand(), rand(), rand(), rand());
            img_set_pixel(img, x, y, c);
            verificar(img_get_pixel(img, x, y) == c);
        }
    }

    // clonamos la imagen
    img_t *img_clon = img_clonar(img);
    verificar(img_clon != NULL);
    verificar(img_clon != img);

    // verificamos que la imagen clonada es exactamente igual a la original
    verificar(img_ancho(img_clon) == img_ancho(img));
    verificar(img_alto(img_clon) == img_alto(img));
    int suma = 0;
    for (uint32_t x = 0; x < img_ancho(img); x++) {
        for (uint32_t y = 0; y < img_alto(img); y++) {
            verificar(img_get_pixel(img_clon, x, y) == img_get_pixel(img, x, y));
            suma += img_get_pixel(img_clon, x, y);
        }
    }

    // modificamos la imagen original
    for (uint32_t x = 0; x < img_ancho(img); x++) {
        for (uint32_t y = 0; y < img_alto(img); y++) {
            c = rgba(rand(), rand(), rand(), rand());
            img_set_pixel(img, x, y, c);
            verificar(img_get_pixel(img, x, y) == c);
        }
    }
    // verificamos que el clon no fue modificado
    int suma2 = 0;
    for (uint32_t x = 0; x < img_ancho(img); x++) {
        for (uint32_t y = 0; y < img_alto(img); y++) {
            suma2 += img_get_pixel(img_clon, x, y);
        }
    }
    verificar(suma == suma2);

    img_destruir(img);
    img_destruir(img_clon);

    return true;
}
#endif

#ifdef EJERCICIO2_HABILITADO
static bool ejercicio2(void) {
    // creamos una imagen aleatoria
    img_t *img_original = img_crear(60, 40);
    verificar(img_original != NULL);
    for (uint32_t x = 0; x < img_ancho(img_original); x++) {
        for (uint32_t y = 0; y < img_alto(img_original); y++) {
            rgba_t c = rgba(rand(), rand(), rand(), rand());
            img_set_pixel(img_original, x, y, c);
        }
    }

    FILE *f = fopen("imagen.bin", "wb");
    verificar(f != NULL);
    bool ok = img_escribir(img_original, f);
    fclose(f);
    verificar(ok);

    f = fopen("imagen.bin", "rb");
    verificar(f != NULL);
    img_t *img_leida = img_leer(f);
    fclose(f);
    verificar(img_leida != NULL);

    // verificamos que la imagen leida es exactamente igual a la original
    verificar(img_ancho(img_leida) == img_ancho(img_original));
    verificar(img_alto(img_leida) == img_alto(img_original));
    for (uint32_t x = 0; x < img_ancho(img_original); x++) {
        for (uint32_t y = 0; y < img_alto(img_original); y++) {
            verificar(img_get_pixel(img_leida, x, y) == img_get_pixel(img_original, x, y));
        }
    }

    img_destruir(img_original);
    img_destruir(img_leida);

    return true;
}
#endif

#ifdef EJERCICIO3_HABILITADO
static bool ejercicio3(void) {
    // creamos varias imagenes de tamagnos aleatorios
    img_t *imagenes[30] = {0};
    for (int i = 0; i < 30; i++) {
        img_t *img = img_crear(rand() % 100 + 1, rand() % 100 + 1);
        verificar(img != NULL);
        imagenes[i] = img;
    }

    img_ordenar_por_tamagno(imagenes, 30);

    // verificamos el resultado
    for (int i = 0; i < 29; i++) {
        int t1 = img_alto(imagenes[i]) * img_ancho(imagenes[i]);
        int t2 = img_alto(imagenes[i + 1]) * img_ancho(imagenes[i + 1]);
        verificar(t1 <= t2);
    }

    for (int i = 0; i < 30; i++) {
        img_destruir(imagenes[i]);
    }

    return true;
}
#endif

#ifdef EJERCICIO4_HABILITADO
static bool ejercicio4(void) {
    // creamos una imagen a utilizar de sello
    img_t *img_sello = img_crear(60, 40);
    verificar(img_sello != NULL);
    for (uint32_t x = 0; x < img_ancho(img_sello); x++) {
        for (uint32_t y = 0; y < img_alto(img_sello); y++) {
            const componente_t r = x % 256;
            const componente_t g = y % 256;
            const componente_t b = (x + y) % 256;
            const componente_t a = y % 2 ? 0x00 : 0xff;

            rgba_t c = rgba(r, g, b, a);
            img_set_pixel(img_sello, x, y, c);
        }
    }

    // creamos la imagen para utilizar de fondo
    img_t *img_fondo = img_crear(120, 40);
    verificar(img_fondo != NULL);

    // pintamos toda la imagen con un color
    img_pintar(img_fondo, rgba(0xff, 0xff, 0xff, 0xff));
    for (uint32_t x = 0; x < img_ancho(img_fondo); x++) {
        for (uint32_t y = 0; y < img_alto(img_fondo); y++) {
            verificar(img_get_pixel(img_fondo, x, y) == rgba(0xff, 0xff, 0xff, 0xff));
        }
    }

    // sellamos img_sello sobre img_fondo:
    //
    //    0       30                      120
    //  0 +-------------------------------+
    //    |F                              |
    //    |                               |
    // 30 |        +======+               |
    // 40 +--------|S=====|---------------+
    //             |======|
    //             |======|
    //             +======+

    img_sellar(img_fondo, img_sello, 30, 30);

    // verificamos que la imagen fue sellada correctamente:
    //
    //    0       30                      120
    //  0 +-------------------------------+
    //    |F                              |
    //    |                               |
    // 30 |        ========               |
    // 40 +--------========---------------+

    // los pixels en (29,30) y (30,29) quedan sin modificar porque el sello comienza en (30,30)
    verificar(img_get_pixel(img_fondo, 29, 30) == rgba(0xff, 0xff, 0xff, 0xff));
    verificar(img_get_pixel(img_fondo, 30, 29) == rgba(0xff, 0xff, 0xff, 0xff));
    // el pixel en 30,30 queda igual al pixel 0,0 del sello
    verificar(img_get_pixel(img_fondo, 30, 30) == img_get_pixel(img_sello, 0, 0));
    // el pixel en 30,31 queda sin modificar porque el pixel 0,1 del sello tiene alpha=0
    verificar(img_get_pixel(img_fondo, 30, 31) == rgba(0xff, 0xff, 0xff, 0xff));
    // el pixel en 31,30 queda igual al pixel 1,0 del sello
    verificar(img_get_pixel(img_fondo, 31, 30) == img_get_pixel(img_sello, 1, 0));

    // La coordenada origen no tienen por que ser positiva:
    //
    // +======+
    // |S=====|                           120
    // |======|---------------------------+
    // |======|                           |
    // +======+                           |
    //    |                               |
    // 40 +-------------------------------+
    img_pintar(img_fondo, rgba(0xff, 0xff, 0xff, 0xff));
    img_sellar(img_fondo, img_sello, -10, -20);

    // verificamos que la imagen fue sellada correctamente:
    //
    //    0                               120
    //  0 +====---------------------------+
    //    =====                           |
    //    =====                           |
    //    |                               |
    // 40 +-------------------------------+
    verificar(img_get_pixel(img_fondo, 0, 0) == img_get_pixel(img_sello, 10, 20));

    img_destruir(img_fondo);
    img_destruir(img_sello);
    return true;
}
#endif

#ifdef EJERCICIO5_HABILITADO
static bool verificar_caracter(const img_t *img, uint32_t x0, uint32_t y0, uint8_t v[8], rgba_t color_fondo, rgba_t color_texto) {
    uint8_t b[8] = {0};
    for (uint32_t y = 0; y < 8; y++) {
        b[y] = 0;
        for (uint32_t x = 0; x < 8; x++) {
            rgba_t p = img_get_pixel(img, x0 + x, y0 + y);
            verificar(p == color_fondo || p == color_texto);
            if (p == color_texto) {
                b[y] |= 1 << x;
            }
        }
    }
    for (int y = 0; y < 8; y++) {
        // verificamos que la fila y del caracter fue generada correctamente
        verificar(b[y] == v[y]);
    }
    return true;
}

static bool ejercicio5(void) {
    rgba_t color_fondo = rgba(0, 0, 0, 0xff);
    rgba_t color_texto = rgba(0xff, 0xff, 0xff, 0xff);

    img_t *img = img_crear_texto("Hola mundo!", color_fondo, color_texto);
    verificar(img != NULL);

    verificar(img_ancho(img) == 88);
    verificar(img_alto(img) == 8);

    // en la coordenada 0, 0 deberia estar el caracter 'H'
    if (!verificar_caracter(img, 0, 0, (uint8_t[8]){0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00}, color_fondo, color_texto)) {
        return false;
    }
    // en la coordenada 80, 0 deberia estar el caracter '!'
    if (!verificar_caracter(img, 80, 0, (uint8_t[8]){0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00}, color_fondo, color_texto)) {
        return false;
    }

    img_destruir(img);
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
