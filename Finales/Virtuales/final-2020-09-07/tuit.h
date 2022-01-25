#ifndef TUIT_H
#define TUIT_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "usuario.h"

// El mensaje de un tuit puede tener hasta 144 caracteres (sin contar el '\0')
#define TUIT_MAX_LARGO 144

// id_usuario_t representa un número identificatorio único para un usuario.
typedef int64_t id_tuit_t;

// tuit_t representa el TDA tuit
typedef struct tuit tuit_t;

// tuit_crear crea un tuit
// Devuelve el tuit creado, o NULL en caso de error.
tuit_t *tuit_crear(id_tuit_t id_tuit, id_usuario_t id_autor, const char *mensaje);

// tuit_destruir destruye el tuit
void tuit_destruir(tuit_t *tuit);

// tuit_id devuelve el ID del tuit
id_tuit_t tuit_id(const tuit_t *tuit);

// tuit-id_autor devuelve el ID del autor del tuit
id_usuario_t tuit_id_autor(const tuit_t *tuit);

// tuit_mensaje devuelve el mensaje del tuit
//
// Nota: devuelve un puntero a la cadena guardada internamente en el tuit (es decir, no hace
// una copia de la cadena).
const char *tuit_mensaje(const tuit_t *tuit);

// tuit_cantidad_likes devuelve la cantidad de likes recibidos
size_t tuit_cantidad_likes(const tuit_t *tuit);

// tuit_dar_like marca que el usuario `id_usuario` dio like a este tuit.
//
// Devuelve false en caso de error, que puede ser:
// * no se pudo reservar memoria
// * el usuario intenta dar like a su propio tuit
// * el usuario ya dio like al tuit
bool tuit_dar_like(tuit_t *tuit, id_usuario_t id_usuario);

// tuit_fue_likeado_por devuelve si el usuario `id_usuario` le dio like
bool tuit_fue_likeado_por(const tuit_t *tuit, id_usuario_t id_usuario);

// tuit_escribir escribe el tuit en el archivo `f` (abierto previamente en modo binario).
//
// Devuelve false en caso de error.
bool tuit_escribir(const tuit_t *tuit, FILE *f);

// tuit_leer lee del archivo `f` (abierto previamente en modo binario) un tuit previamente
// escrito mediante tuit_escribir.
//
// Devuelve un nuevo tuit con la información leida, o NULL en caso de error, que puede ser por:
// * no se pudo reservar memoria
// * error al leer el archivo
tuit_t* tuit_leer(FILE *f);

// tuits_ordenar_por_cantidad_de_likes ordena el arreglo de tuits por cantidad de likes (los
// mas likeados primero).
void tuits_ordenar_por_cantidad_de_likes(tuit_t *tuits[], size_t n);

// Un tuit puede tener a lo sumo TUIT_MAX_RESPUESTAS respuestas
#define TUIT_MAX_RESPUESTAS 10

// tuit_responder crea un tuit en respuesta de otro tuit
// Devuelve el tuit creado (con id = id_tuit_respuesta), o NULL en caso de error.
tuit_t *tuit_responder(tuit_t *tuit, id_tuit_t id_tuit_respuesta, id_usuario_t id_autor, const char *mensaje);

// tuit_en_respuesta_de devuelve el ID del tuit respondido, o -1 si no es una respuesta de ningun tuit
id_tuit_t tuit_en_respuesta_de(const tuit_t *tuit);

// tuit_respuestas guarda en id_respuestas los IDs de los tuits que son respuestas, y en
// cant_respuestas la cantidad de respuestas
void tuit_respuestas(const tuit_t *tuit, id_tuit_t id_respuestas[], size_t *cant_respuestas);

#endif
