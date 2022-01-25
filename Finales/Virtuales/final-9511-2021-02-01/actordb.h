#ifndef ACTORDB_H
#define ACTORDB_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define NOMBRE_MAX 30

typedef struct fecha {
    uint16_t anio;
    uint8_t mes;
    uint8_t dia;
} fecha_t;

typedef struct actor actor_t;

// ejercicio 1
actor_t *actor_crear(const char *nombre, fecha_t nacimiento);
void actor_destruir(actor_t *actor);
const char *actor_nombre(const actor_t *actor);
fecha_t actor_nacimiento(const actor_t *actor);

// ejercicio 2
bool actor_escribir(const actor_t *actor, const char *nombre_archivo);
actor_t *actor_leer(const char *nombre_archivo);

// ejercicio 3
int fecha_comparar(fecha_t a, fecha_t b);
void actores_ordenar_por_fecha_nacimiento(actor_t *actores[], size_t n);

// ejercicio 4
actor_t *actores_buscar(actor_t *actores[], size_t n, const char *nombre);

// ejercicio 5
uint32_t fecha_a_bcd(fecha_t fecha);
fecha_t bcd_a_fecha(uint32_t bcd);

#endif
