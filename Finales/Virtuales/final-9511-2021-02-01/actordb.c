#include "actordb.h"
#include <stdio.h>
#include <string.h>

struct actor {
    char nombre[NOMBRE_MAX];
    fecha_t nacimiento;
};

// ejercicio 1 (12 min)
actor_t *actor_crear(const char *nombre, fecha_t nacimiento) {
    if (nombre == NULL)
        return NULL;

    actor_t *actor = malloc(sizeof(actor_t));
    if (actor == NULL)
        return NULL;

    strcpy(actor->nombre, nombre);
    actor->nacimiento = nacimiento;
    return actor;
}

void actor_destruir(actor_t *actor) {
    if (actor == NULL)
        return;
    free(actor);
}

const char *actor_nombre(const actor_t *actor) {
    if (actor == NULL)
        return NULL;
    return actor->nombre;
}

fecha_t actor_nacimiento(const actor_t *actor) {
    if (actor == NULL)
        return (fecha_t){0, 0, 0};
    return actor->nacimiento;
}

// ejercicio 2 (10 min)
bool actor_escribir(const actor_t *actor, const char *nombre_archivo) {
    if (actor == NULL || nombre_archivo == NULL)
        return false;

    FILE *f = fopen(nombre_archivo, "wb");
    if (f == NULL)
        return false;

    if (fwrite(actor, sizeof(actor_t), 1, f) != 1) {
        fclose(f);
        return false;
    }

    fclose(f);
    return true;
}

actor_t *actor_leer(const char *nombre_archivo) {
    if (nombre_archivo == NULL)
        return NULL;

    FILE *f = fopen(nombre_archivo, "rb");
    if (f == NULL)
        return NULL;

    actor_t *actor = malloc(sizeof(actor_t));
    if (actor == NULL) {
        fclose(f);
        return NULL;
    }

    if (fread(actor, sizeof(actor_t), 1, f) != 1) {
        fclose(f);
        free(actor);
        return NULL;
    }

    fclose(f);
    return actor;
}

// ejercicio 3 (43 min)
int fecha_comparar(fecha_t a, fecha_t b) {
    if (a.dia == b.dia && a.mes == b.mes && a.anio == b.anio)
        return 0;
    if (a.dia < b.dia || a.mes < b.mes || a.anio < b.anio)
        return -1;
    return 1;
}

int wrapper_fecha_comparar(const void *a, const void *b) {
    return fecha_comparar((*(actor_t **)a)->nacimiento, (*(actor_t **)b)->nacimiento);
}

void actores_ordenar_por_fecha_nacimiento(actor_t *actores[], size_t n) {
    if (actores == NULL)
        return;
    qsort(actores, n, sizeof(actor_t *), wrapper_fecha_comparar);
}

// ejercicio 4 (45 min)
int wrapper_nombre_cmp(const void *a, const void *b) {
    return strcmp((*(actor_t **)a)->nombre, (*(actor_t **)b)->nombre);
}

actor_t *actores_buscar_bsearch(actor_t *actores[], size_t n, const char *nombre) {
    if (actores == NULL || n == 0 || nombre == NULL)
        return NULL;
    return (actor_t *)bsearch(nombre, actores, n, sizeof(actor_t *), wrapper_nombre_cmp);
}

actor_t *actores_buscar(actor_t *actores[], size_t n, const char *nombre) {
    if (actores == NULL || n == 0 || nombre == NULL)
        return NULL;

    // TODO: Revisar binary search hecho a mano en este ejercicio produjo fallos
    // hasta que agregue la comparacion de la cabeza y cola.
    // (34 min resolviendo el problema que no deberia haber ocurrido)

    int inicio = 0;
    int fin = n - 1;
    int medio;

    while (inicio < fin) {

        if (strcmp(actores[inicio]->nombre, nombre) == 0)
            return actores[inicio];
        if (strcmp(actores[fin]->nombre, nombre) == 0)
            return actores[fin];

        medio = (inicio + fin) / 2;
        int res = strcmp(actores[medio]->nombre, nombre);

        if (res == 0)
            return actores[medio];
        if (res < 0)
            inicio = medio + 1;
        else
            fin = medio - 1;
    }

    return NULL;
}

// ejercicio 5 (28 min)
uint8_t bcd_2_digitos(const uint8_t n) {
    return ((n / 10) << 4) | (n % 10);
}

uint32_t fecha_a_bcd(fecha_t fecha) {
    uint32_t res = 0;
    res |= bcd_2_digitos(fecha.dia);
    res |= bcd_2_digitos(fecha.mes) << 8;
    res |= bcd_2_digitos(fecha.anio % 100) << 16;
    res |= bcd_2_digitos(fecha.anio / 100) << 24;
    return res;
}

fecha_t bcd_a_fecha(uint32_t bcd) {
    fecha_t f_res = {0};
    for (int i = 0, j = 1; i < 32; i += 4) {
        if (i < 8)
            f_res.dia += ((bcd >> i) & 0xF) * (!i ? 1 : 10);
        if (i >= 8 && i < 16)
            f_res.mes += ((bcd >> i) & 0xF) * (!(i - 8) ? 1 : 10);
        if (i >= 16){
            f_res.anio += ((bcd >> i) & 0xF) * (!(i - 16) ? 1 : j);
            j *= 10;
        }
    }
    return f_res;
}