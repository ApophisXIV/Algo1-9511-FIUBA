#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tuit.h"

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

// IDs inventados
#define ID_TUIT ((id_tuit_t)42)
#define ID_BARBARA ((id_usuario_t)20)
#define ID_GRACE ((id_usuario_t)30)

#ifdef EJERCICIO1_HABILITADO
static bool ejercicio1(void) {
    char msg[145] = "Hola";

    // Grace publica un tuit
    tuit_t *t = tuit_crear(ID_TUIT, ID_GRACE, msg);
    verificar(t != NULL);

    verificar(tuit_id(t) == ID_TUIT);
    verificar(tuit_id_autor(t) == ID_GRACE);
    verificar(strcmp(tuit_mensaje(t), "Hola") == 0);
    verificar(tuit_cantidad_likes(t) == 0);

    // el tuit tiene una copia de la cadena
    strcpy(msg, "Chau");
    verificar(strcmp(tuit_mensaje(t), "Hola") == 0);

    bool ok;

    // Grace no puede dar like su propio tuit
    ok = tuit_dar_like(t, ID_GRACE);
    verificar(!ok);
    verificar(tuit_cantidad_likes(t) == 0);

    // barbara puede dar like al tuit de Grace
    ok = tuit_dar_like(t, ID_BARBARA);
    verificar(ok);
    verificar(tuit_cantidad_likes(t) == 1);

    verificar(!tuit_fue_likeado_por(t, ID_GRACE));
    verificar(tuit_fue_likeado_por(t, ID_BARBARA));

    // barbara no puede dar like otra vez al mismo tuit
    ok = tuit_dar_like(t, ID_BARBARA);
    verificar(!ok);
    verificar(tuit_cantidad_likes(t) == 1);

    verificar(!tuit_fue_likeado_por(t, ID_GRACE));
    verificar(tuit_fue_likeado_por(t, ID_BARBARA));

    // el tuit es likeado por 1000 usuarios
    for (id_usuario_t id_usuario = ID_GRACE + 1; id_usuario <= ID_GRACE + 1000; id_usuario++) {
        verificar(tuit_dar_like(t, id_usuario));
    }

    // verificamos que el tuit fue likeado por esos usuarios
    for (id_usuario_t id_usuario = ID_GRACE + 1; id_usuario <= ID_GRACE + 1000; id_usuario++) {
        verificar(tuit_fue_likeado_por(t, id_usuario));
    }

    // verificamos que el tuit NO fue likeado por otros usuarios
    for (id_usuario_t id_usuario = ID_GRACE + 20000; id_usuario < ID_GRACE + 21000; id_usuario++) {
        verificar(!tuit_fue_likeado_por(t, id_usuario));
    }

    verificar(tuit_cantidad_likes(t) == 1001);

    tuit_destruir(t);
    return true;
}
#endif

#ifdef EJERCICIO2_HABILITADO
static bool prueba_escribir_leer(const tuit_t *tuit_original) {
    FILE *f = fopen("tuit.bin", "wb");
    verificar(f != NULL);
    bool ok = tuit_escribir(tuit_original, f);
    fclose(f);
    verificar(ok);

    f = fopen("tuit.bin", "rb");
    verificar(f != NULL);
    tuit_t *t_leido = tuit_leer(f);
    fclose(f);
    verificar(t_leido != NULL);

    // verificamos que el tuit leido es exactamente igual al original
    verificar(tuit_id(t_leido) == tuit_id(tuit_original));
    verificar(tuit_id_autor(t_leido) == tuit_id_autor(tuit_original));
    verificar(strcmp(tuit_mensaje(t_leido), tuit_mensaje(tuit_original)) == 0);
    verificar(tuit_cantidad_likes(t_leido) == tuit_cantidad_likes(tuit_original));

    tuit_destruir(t_leido);
    return true;
}

static bool ejercicio2(void) {
    tuit_t *t = tuit_crear(ID_TUIT, ID_GRACE, "Hola");
    verificar(t != NULL);

    // probamos escribir y leer un tuit con 0 likes
    if (!prueba_escribir_leer(t)) {
        return false;
    }

    // misma prueba con un tuit con 1000 likes
    for (id_usuario_t id_usuario = ID_GRACE + 1; id_usuario <= ID_GRACE + 1000; id_usuario++) {
        verificar(tuit_dar_like(t, id_usuario));
    }
    if (!prueba_escribir_leer(t)) {
        return false;
    }


    tuit_destruir(t);
    return true;
}
#endif

#ifdef EJERCICIO3_HABILITADO
#define N_TUITS 100
static bool ejercicio3(void) {
    static tuit_t *tuits[N_TUITS];

    // creamos 100 tuits con una cantidad aleatoria (entre 0 y 200) de likes
    for (int i = 0; i < N_TUITS; i++) {
        tuits[i] = tuit_crear(i, ID_GRACE, "Hola");
        int cant_likes = rand() % 200;
        for (int j = 0; j < cant_likes; j++) {
            bool ok = tuit_dar_like(tuits[i], ID_GRACE + j + 1);
            verificar(ok);
        }
    }

    tuits_ordenar_por_cantidad_de_likes(tuits, N_TUITS);

    for (int i = 1; i < N_TUITS; i++) {
        verificar(tuit_cantidad_likes(tuits[i-1]) >= tuit_cantidad_likes(tuits[i]));
    }

    for (int i = 0; i < N_TUITS; i++) {
        tuit_destruir(tuits[i]);
    }

    return true;
}
#undef N_TUITS
#endif

#ifdef EJERCICIO4_HABILITADO
static bool ejercicio4(void) {
    tuit_t *t = tuit_crear(ID_TUIT, ID_GRACE, "Hola");
    verificar(t != NULL);

    // el tuit es likeado por 10000 usuarios
    for (id_usuario_t id_usuario = ID_GRACE + 1; id_usuario <= ID_GRACE + 10000; id_usuario++) {
        verificar(tuit_dar_like(t, id_usuario));
    }

    // verificamos que el tuit fue likeado por un usuario aleatorio, muchas veces.
    for (int i = 0; i < 1000000; i++) {
        id_usuario_t id_usuario = ID_GRACE + (rand() % 20000) + 1;
        tuit_fue_likeado_por(t, id_usuario);
    }

    tuit_destruir(t);
    return true;
}
#endif

#ifdef EJERCICIO5_HABILITADO
static bool ejercicio5(void) {
    tuit_t *t = tuit_crear(ID_TUIT, ID_GRACE, "Hola");
    verificar(t != NULL);

    tuit_t *respuestas[TUIT_MAX_RESPUESTAS];

    // el tuit no es en respuesta de ningún otro tuit
    verificar(tuit_en_respuesta_de(t) == -1);

    id_tuit_t id_respuestas[TUIT_MAX_RESPUESTAS];
    size_t cant_respuestas;

    // el tuit no tiene respuestas
    tuit_respuestas(t, id_respuestas, &cant_respuestas);
    verificar(cant_respuestas == 0);

    // creamos muchas respuestas
    for (int i = 0; i < TUIT_MAX_RESPUESTAS; i++) {
        id_tuit_t id_tuit_respuesta = ID_TUIT + i;
        respuestas[i] = tuit_responder(t, id_tuit_respuesta, ID_BARBARA, "Respuesta");

        verificar(respuestas[i] != NULL);

        // el tuit creado es en respuesta de t
        verificar(tuit_en_respuesta_de(respuestas[i]) == ID_TUIT);

        // el tuit t tiene i + 1 respuestas
        tuit_respuestas(t, id_respuestas, &cant_respuestas);
        verificar(cant_respuestas == i + 1);
        for (int j = 0; j < cant_respuestas; j++) {
            verificar(id_respuestas[j] == ID_TUIT + j);
        }
    }

    // ya no podemos crear más respuestas
    tuit_t *nope = tuit_responder(t, ID_TUIT + 100, ID_BARBARA, "Respuesta");
    verificar(nope == NULL);

    tuit_destruir(t);
    for (int i = 0; i < TUIT_MAX_RESPUESTAS; i++) {
        tuit_destruir(respuestas[i]);
    }

    return true;
}
#undef N_HILO
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
