#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "aerodb.h"

#define EJERCICIO1_HABILITADO
//#define EJERCICIO2_HABILITADO
//#define EJERCICIO3_HABILITADO
//#define EJERCICIO4_HABILITADO
//#define EJERCICIO5_HABILITADO

#define verificar(condicion) do { \
        if (!(condicion)) { \
            printf("Prueba fallida en %s:%d: %s\n", __FILE__, __LINE__, #condicion); \
            return false; \
        } \
    } while (0)

bool cargar_aeropuertos(aerodb_t *a);

#ifdef EJERCICIO1_HABILITADO
static bool ejercicio1(void) {
    aerodb_t *a = aerodb_crear();
    verificar(a != NULL);
    verificar(aerodb_cantidad(a) == 0);
    verificar(aerodb_nombre(a, "EZE") == NULL);

    bool ok;

    ok = aerodb_agregar(a, "EZE", "Ministro Pistarini International Airport", "Buenos Aires", "Argentina", -34.8222, -58.5358);
    verificar(ok);

    verificar(aerodb_cantidad(a) == 1);

    ok = aerodb_agregar(a, "BRC", "San Carlos De Bariloche Airport", "San Carlos De Bariloche", "Argentina", -41.151199, -71.157501);
    verificar(ok);

    verificar(aerodb_cantidad(a) == 2);

    verificar(!strcmp(aerodb_nombre(a, "EZE"), "Ministro Pistarini International Airport"));
    verificar(!strcmp(aerodb_ciudad(a, "EZE"), "Buenos Aires"));
    verificar(!strcmp(aerodb_pais(a, "EZE"), "Argentina"));
    verificar(aerodb_lat(a, "EZE") == -34.8222);
    verificar(aerodb_lon(a, "EZE") == -58.5358);

    verificar(!strcmp(aerodb_nombre(a, "BRC"), "San Carlos De Bariloche Airport"));
    verificar(!strcmp(aerodb_ciudad(a, "BRC"), "San Carlos De Bariloche"));
    verificar(!strcmp(aerodb_pais(a, "BRC"), "Argentina"));
    verificar(aerodb_lat(a, "BRC") == -41.151199);
    verificar(aerodb_lon(a, "BRC") == -71.157501);

    verificar(aerodb_nombre(a, "DUB") == NULL);

    aerodb_destruir(a);

    return true;
}
#endif

#ifdef EJERCICIO2_HABILITADO
static bool ejercicio2(void) {
    aerodb_t *a = aerodb_crear();
    verificar(a != NULL);
    aerodb_agregar(a, "EZE", "Ministro Pistarini International Airport", "Buenos Aires", "Argentina", -34.8222, -58.5358);
    aerodb_agregar(a, "BRC", "San Carlos De Bariloche Airport", "San Carlos De Bariloche", "Argentina", -41.151199, -71.157501);
    aerodb_agregar(a, "DUB", "Dublin Airport", "Dublin", "Ireland", 53.421299, -6.27007);

    verificar(aerodb_cantidad(a) == 3);

    bool ok = aerodb_escribir(a, "aerodb.bin");
    verificar(ok);

    aerodb_t *b = aerodb_leer("aerodb.bin");
    verificar(b != NULL);
    verificar(aerodb_cantidad(b) == 3);

    verificar(!strcmp(aerodb_nombre(b, "EZE"), "Ministro Pistarini International Airport"));
    verificar(!strcmp(aerodb_ciudad(b, "EZE"), "Buenos Aires"));
    verificar(!strcmp(aerodb_pais(b, "EZE"), "Argentina"));
    verificar(aerodb_lat(b, "EZE") == -34.8222);
    verificar(aerodb_lon(b, "EZE") == -58.5358);

    verificar(!strcmp(aerodb_nombre(b, "BRC"), "San Carlos De Bariloche Airport"));
    verificar(!strcmp(aerodb_ciudad(b, "BRC"), "San Carlos De Bariloche"));
    verificar(!strcmp(aerodb_pais(b, "BRC"), "Argentina"));
    verificar(aerodb_lat(b, "BRC") == -41.151199);
    verificar(aerodb_lon(b, "BRC") == -71.157501);

    verificar(!strcmp(aerodb_nombre(b, "DUB"), "Dublin Airport"));
    verificar(!strcmp(aerodb_ciudad(b, "DUB"), "Dublin"));
    verificar(!strcmp(aerodb_pais(b, "DUB"), "Ireland"));
    verificar(aerodb_lat(b, "DUB") == 53.421299);
    verificar(aerodb_lon(b, "DUB") == -6.27007);

    aerodb_destruir(a);
    aerodb_destruir(b);

    return true;
}
#endif

#ifdef EJERCICIO3_HABILITADO
static bool ejercicio3(void) {
    aerodb_t *a = aerodb_crear();
    verificar(a != NULL);

    bool ok = cargar_aeropuertos(a);
    verificar(ok);
    verificar(aerodb_cantidad(a) == 6072);

    for (int i = 0; i < 10000; i++) {
        char *nombre = NULL;
        char *ciudad = NULL;
        char *pais = NULL;
        double lat = 0;
        double lon = 0;

        ok = aerodb_buscar(a, "XYZ", &nombre, &ciudad, &pais, &lat, &lon);
        verificar(!ok);

        ok = aerodb_buscar(a, "AKL", &nombre, &ciudad, &pais, &lat, &lon);
        verificar(ok);
        verificar(!strcmp(nombre, "Auckland International Airport"));
        verificar(!strcmp(ciudad, "Auckland"));
        verificar(!strcmp(pais, "New Zealand"));
        verificar(lat == -37.008098602299995);
        verificar(lon == 174.792007446);

        ok = aerodb_buscar(a, "YGJ", &nombre, &ciudad, &pais, &lat, &lon);
        verificar(ok);
        verificar(!strcmp(nombre, "Miho Yonago Airport"));
        verificar(!strcmp(ciudad, "Miho"));
        verificar(!strcmp(pais, "Japan"));
        verificar(lat == 35.4921989440918);
        verificar(lon == 133.23599243164062);
    }

    aerodb_destruir(a);
    return true;
}
#endif

#ifdef EJERCICIO4_HABILITADO
static bool ejercicio4(void) {
    aerodb_t *a = aerodb_crear();
    verificar(a != NULL);

    char *nombre = NULL;
    char *ciudad = NULL;
    char *pais = NULL;
    double lat = 0;
    double lon = 0;

    bool ok;

    ok = aerodb_mas_cercano(a, -37.0080986, 174.79200, &nombre, &ciudad, &pais, &lat, &lon);
    verificar(!ok);

    ok = cargar_aeropuertos(a);
    verificar(ok);
    verificar(aerodb_cantidad(a) == 6072);

    ok = aerodb_mas_cercano(a, -37.0080986, 174.79200, &nombre, &ciudad, &pais, &lat, &lon);
    verificar(ok);
    verificar(!strcmp(nombre, "Auckland International Airport"));
    verificar(!strcmp(ciudad, "Auckland"));
    verificar(!strcmp(pais, "New Zealand"));
    verificar(lat == -37.008098602299995);
    verificar(lon == 174.792007446);

    aerodb_destruir(a);
    return true;
}
#endif

#ifdef EJERCICIO5_HABILITADO
static bool ejercicio5(void) {
    uint32_t angulo_sexagesimal = 0x122c54;

    bool negativo;
    uint8_t grados;
    uint8_t minutos;
    uint8_t segundos;
    decodificar_angulo(angulo_sexagesimal, &negativo, &grados, &minutos, &segundos);

    verificar(negativo == true);
    verificar(grados == 34);
    verificar(minutos == 49);
    verificar(segundos == 20);
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
