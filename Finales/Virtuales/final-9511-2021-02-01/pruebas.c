#include <string.h>
#include <stdio.h>

#include "actordb.h"

//#define EJERCICIO1_HABILITADO
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

#ifdef EJERCICIO1_HABILITADO
static bool ejercicio1(void) {
    actor_t *darin = actor_crear("Ricardo Darin", (fecha_t){1957, 1, 16});
    actor_t *pauls = actor_crear("Gaston Pauls", (fecha_t){1972, 1, 17});

    verificar(darin != NULL);
    verificar(pauls != NULL);

    verificar(!strcmp(actor_nombre(darin), "Ricardo Darin"));
    verificar(!strcmp(actor_nombre(pauls), "Gaston Pauls"));

    fecha_t fecha = actor_nacimiento(darin);
    verificar(fecha.anio == 1957 && fecha.mes == 1 && fecha.dia == 16);

    actor_destruir(darin);
    actor_destruir(pauls);
    return true;
}
#endif

#ifdef EJERCICIO2_HABILITADO
static bool ejercicio2(void) {
    actor_t *darin = actor_crear("Ricardo Darin", (fecha_t){1957, 1, 16});

    verificar(actor_escribir(darin, "darin.bin"));

    actor_t *leido = actor_leer("darin.bin");
    verificar(leido != NULL);

    verificar(!strcmp(actor_nombre(leido), "Ricardo Darin"));
    fecha_t fecha = actor_nacimiento(leido);
    verificar(fecha.anio == 1957 && fecha.mes == 1 && fecha.dia == 16);

    actor_destruir(darin);
    actor_destruir(leido);

    return true;
}
#endif

#ifdef EJERCICIO3_HABILITADO
#define N_ACTORES 100
static bool ejercicio3(void) {
    fecha_t fecha1 = (fecha_t){1957, 1, 16};
    fecha_t fecha2 = (fecha_t){1972, 1, 17};
    fecha_t fecha3 = (fecha_t){1972, 8, 26};
    verificar(fecha_comparar(fecha1, fecha1) == 0);
    verificar(fecha_comparar(fecha1, fecha2) < 0);
    verificar(fecha_comparar(fecha2, fecha1) > 0);
    verificar(fecha_comparar(fecha1, fecha3) < 0);
    verificar(fecha_comparar(fecha3, fecha1) > 0);
    verificar(fecha_comparar(fecha2, fecha3) < 0);
    verificar(fecha_comparar(fecha3, fecha2) > 0);

    // creamos 100 actores con una fecha de nacimiento aleatoria
    static actor_t *actores[N_ACTORES];
    for (int i = 0; i < N_ACTORES; i++) {
        char nombre[NOMBRE_MAX + 1];
        sprintf(nombre, "Actor %d", i);
        actores[i] = actor_crear(nombre, (fecha_t) {
            .anio = 1910 + (rand() % 100),
            .mes = 1 + rand() % 12,
            .dia = 1 + rand() % 28,
        });
        verificar(actores[i] != NULL);
    }

    actores_ordenar_por_fecha_nacimiento(actores, N_ACTORES);

    for (int i = 1; i < N_ACTORES; i++) {
        fecha_t fecha1 = actor_nacimiento(actores[i-1]);
        fecha_t fecha2 = actor_nacimiento(actores[i]);
        verificar(fecha_comparar(fecha1, fecha2) <= 0);
    }

    for (int i = 0; i < N_ACTORES; i++) {
        actor_destruir(actores[i]);
    }

    return true;
}
#endif

#ifdef EJERCICIO4_HABILITADO
#define N_ACTORES 100
static bool ejercicio4(void) {
    // creamos 100 actores ordenados por nombre
    static actor_t *actores[N_ACTORES];
    int j = 0;
    for (int i = 0; i < N_ACTORES; i++) {
        char nombre[NOMBRE_MAX + 1];
        j += rand() % 3;
        sprintf(nombre, "Actor %04d", j);
        actores[i] = actor_crear(nombre, (fecha_t){1960, 1, 1});
        verificar(actores[i] != NULL);
    }

    verificar(actores_buscar(actores, N_ACTORES, "No existe") == NULL);

    // elegimos un actor arbitrario a buscar
    actor_t *actor = actores[35];
    const char *nombre = actor_nombre(actor);

    verificar(actores_buscar(actores, N_ACTORES, nombre) == actor);

    for (int i = 0; i < N_ACTORES; i++) {
        actor_destruir(actores[i]);
    }

    return true;
}
#endif

#ifdef EJERCICIO5_HABILITADO
static bool ejercicio5(void) {
    fecha_t fecha = {1972, 8, 26};
    uint32_t fecha_bcd = fecha_a_bcd(fecha);
    verificar(fecha_bcd == 0x0019720826);

    fecha = bcd_a_fecha(0x0019570116);
    verificar(fecha.anio == 1957 && fecha.mes == 1 && fecha.dia == 16);
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
