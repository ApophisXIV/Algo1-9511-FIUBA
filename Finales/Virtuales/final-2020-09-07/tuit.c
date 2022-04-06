#include "tuit.h"

#include <stdlib.h>
#include <string.h>

typedef struct {
	id_tuit_t *likes_ptr;	 // Si n == 0, likes = NULL
	size_t n;
} likes_t;

struct tuit {
	id_tuit_t id_tuit;
	id_tuit_t id_user;
	char msg[TUIT_MAX_LARGO];
	likes_t likes;
	id_tuit_t is_reply;
	id_tuit_t respuestas[TUIT_MAX_RESPUESTAS];
    size_t n_respuestas;
};

// ---- Ejercicio 1 (1h 20 min) ----

tuit_t *tuit_crear(id_tuit_t id_tuit, id_usuario_t id_autor, const char *mensaje) {
	if (mensaje == NULL || *mensaje == '\0' || strlen(mensaje) > TUIT_MAX_LARGO)
		return NULL;	// Mensaje vacio

	tuit_t *tuit = malloc(sizeof(tuit_t));
	if (tuit == NULL)
		return NULL;

	tuit->id_tuit = id_tuit;
	tuit->id_user = id_autor;

	strcpy(tuit->msg, mensaje);

	tuit->likes.likes_ptr = NULL;
	tuit->likes.n = 0;	  // Todavia no recibio ningun like

	tuit->is_reply = -1;

	return tuit;
}

void tuit_destruir(tuit_t *tuit) {
	if (tuit == NULL)
		return;

	free(tuit->likes.likes_ptr);
	free(tuit);
}

id_tuit_t tuit_id(const tuit_t *tuit) {
	return tuit->id_tuit;
}

id_usuario_t tuit_id_autor(const tuit_t *tuit) {
	return tuit->id_user;
}

const char *tuit_mensaje(const tuit_t *tuit) {
	return tuit->msg;
}

size_t tuit_cantidad_likes(const tuit_t *tuit) {
	return tuit->likes.n;
}

int id_usuario_cmp(const void *a, const void *b) {
	return *(id_usuario_t *)a - *(id_usuario_t *)b;
}

bool tuit_dar_like(tuit_t *tuit, id_usuario_t id_usuario) {
	if (tuit == NULL || id_usuario == tuit->id_user)
		return false;

	id_tuit_t *id_exist = bsearch(&id_usuario, tuit->likes.likes_ptr, tuit->likes.n, sizeof(id_tuit_t), id_usuario_cmp);
	if (id_exist != NULL)
		return false;

	id_tuit_t *id_array = realloc(tuit->likes.likes_ptr, (tuit->likes.n + 1) * sizeof(id_tuit_t));
	if (id_array == NULL) {
		free(tuit);
		return 1;
	}

	tuit->likes.likes_ptr = id_array;
	tuit->likes.likes_ptr[tuit->likes.n++] = id_usuario;

	if (tuit->likes.n > 1 && tuit->likes.likes_ptr[tuit->likes.n - 1] < tuit->likes.likes_ptr[tuit->likes.n - 2])
		qsort(tuit->likes.likes_ptr, tuit->likes.n, sizeof(id_tuit_t), id_usuario_cmp);

	return true;
}

bool tuit_fue_likeado_por(const tuit_t *tuit, id_usuario_t id_usuario) {
	if (tuit == NULL)
		return false;

	id_usuario_t *id_usuario_ptr = bsearch(&id_usuario, tuit->likes.likes_ptr, tuit->likes.n, sizeof(id_usuario_t *), id_usuario_cmp);

	if (id_usuario_ptr == NULL)	   // No le dio like
		return false;

	return true;
}

// ---- Ejercicio 2 (10 min) ----

bool tuit_escribir(const tuit_t *tuit, FILE *f) {

	if (tuit == NULL || f == NULL)
		return false;

	if (fwrite(&tuit->id_tuit, sizeof(id_tuit_t), 1, f) != 1)
		return false;

	if (fwrite(&tuit->id_user, sizeof(id_usuario_t), 1, f) != 1)
		return false;

	if (fwrite(tuit->msg, sizeof(char), TUIT_MAX_LARGO, f) != TUIT_MAX_LARGO)
		return false;

	if (fwrite(&tuit->likes.n, sizeof(size_t), 1, f) != 1)
		return false;

	if (tuit->likes.n > 0)
		if (fwrite(tuit->likes.likes_ptr, sizeof(id_tuit_t), tuit->likes.n, f) != tuit->likes.n)
			return false;

	if (fwrite(&tuit->is_reply, sizeof(id_tuit_t), 1, f) != 1)
		return false;

	if (fwrite(tuit->respuestas, sizeof(id_tuit_t), TUIT_MAX_RESPUESTAS, f) != TUIT_MAX_RESPUESTAS)
		return false;

	return true;
}

tuit_t *tuit_leer(FILE *f) {

	if (f == NULL)
		return NULL;

	tuit_t *tuit = malloc(sizeof(tuit_t));
	if (tuit == NULL)
		return NULL;

	if (fread(&tuit->id_tuit, sizeof(id_tuit_t), 1, f) != 1) {
		free(tuit);
		return NULL;
	}

	if (fread(&tuit->id_user, sizeof(id_usuario_t), 1, f) != 1) {
		free(tuit);
		return NULL;
	}

	if (fread(tuit->msg, sizeof(char), TUIT_MAX_LARGO, f) != TUIT_MAX_LARGO) {
		free(tuit);
		return NULL;
	}

	if (fread(&tuit->likes.n, sizeof(size_t), 1, f) != 1) {
		free(tuit);
		return NULL;
	}

	if (tuit->likes.n > 0) {
		tuit->likes.likes_ptr = malloc(tuit->likes.n * sizeof(id_tuit_t));
		if (tuit->likes.likes_ptr == NULL) {
			free(tuit);
			return NULL;
		}

		if (fread(tuit->likes.likes_ptr, sizeof(id_tuit_t), tuit->likes.n, f) != tuit->likes.n) {
			free(tuit->likes.likes_ptr);
			free(tuit);
			return NULL;
		}
	}

	if (fread(&tuit->is_reply, sizeof(id_tuit_t), 1, f) != 1) {
		free(tuit);
		return NULL;
	}

	if (fread(tuit->respuestas, sizeof(id_tuit_t), TUIT_MAX_RESPUESTAS, f) != TUIT_MAX_RESPUESTAS) {
		free(tuit);
		return NULL;
	}

	return tuit;
}

// ---- Ejercicio 3 (12 min) ----

int cmp_likes(const void *a, const void *b) {

    const tuit_t *tuit_a = *(tuit_t **)a;
    const tuit_t *tuit_b = *(tuit_t **)b;

    //Lo implemento mediante ifs ya que el n es de tipo size_t
    if (tuit_a->likes.n > tuit_b->likes.n)
        return -1;
    else if (tuit_a->likes.n < tuit_b->likes.n)
        return 1;
    else
        return 0;
}

void tuits_ordenar_por_cantidad_de_likes(tuit_t *tuits[], size_t n) {

	if (tuits == NULL || n == 0)
		return;

	qsort(tuits, n, sizeof(tuit_t *), cmp_likes);
}

// ---- Ejercicio 4 (1 min) ----
// Prueba realizada

// ---- Ejercicio 5 ( min) ----

tuit_t *tuit_responder(tuit_t *tuit, id_tuit_t id_tuit_respuesta, id_usuario_t id_autor, const char *mensaje) {

    if (tuit == NULL || mensaje == NULL)
        return NULL;

    if (tuit->is_reply != 0)
        return NULL;

    // TODO Complete this function
}

id_tuit_t tuit_en_respuesta_de(const tuit_t *tuit) {
        if(tuit == NULL) return -1;
        return tuit->is_reply;
}

void tuit_respuestas(const tuit_t *tuit, id_tuit_t id_respuestas[], size_t *cant_respuestas) {
    if(tuit == NULL || id_respuestas == NULL || cant_respuestas == NULL) return;

    // TODO Complete this function
}
