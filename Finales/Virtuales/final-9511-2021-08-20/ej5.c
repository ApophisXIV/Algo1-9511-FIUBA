#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CADENA 128

// HACER: declarar el tipo album_t
typedef struct {
    char *autor;
    char *titulo;
    char **temas;
    size_t n_temas;
} album_t;



/* -------------------------------------------------------------------------- */
// Invariante de representacion:
/* -------------------------------------------------------------------------- */
// - Si n_temas == 0, entonces temas == NULL
// - Si n_temas > 0, entonces temas != NULL
// - El tamaño del arreglo dinamico de char es el mismo que expresa "n_temas"
// - Todos los punteros apuntan a memoria valida
/* -------------------------------------------------------------------------- */

album_t *album_crear(const char *autor, const char *titulo) {

    if (autor == NULL || titulo == NULL)
        return NULL;

    album_t *album = malloc(sizeof(album_t));
    if (album == NULL)
        return NULL;

    char* autor_h = malloc(sizeof(char) * (strlen(autor) + 1));
    if (autor_h == NULL) {
        free(album);
        return NULL;
    }

    char* titulo_h = malloc(sizeof(char) * (strlen(titulo) + 1));
    if (titulo_h == NULL) {
        free(album);
        free(autor_h);
        return NULL;
    }

    strcpy(autor_h, autor);
    strcpy(titulo_h, titulo);

    album->autor = autor_h;
    album->titulo = titulo_h;

    album->temas = NULL;
    album->n_temas = 0;

    return album;
}

bool album_agregar_tema(album_t *a, const char *titulo_tema) {
    if (a == NULL || titulo_tema == NULL)
        return false;

    char **tema_arr_aux = realloc(a->temas, sizeof(char*) * (a->n_temas + 1));
    if (tema_arr_aux == NULL)
        return false;

    char *tema = malloc(sizeof(char) * (strlen(titulo_tema) + 1));
    if (tema == NULL) {
        free(tema_arr_aux);
        return false;
    }

    a->temas = tema_arr_aux;
    a->temas[a->n_temas++] = tema;

    strcpy(tema, titulo_tema);

    return true;
}



size_t album_cantidad_temas(album_t *a) {
    if (a == NULL)
        return 0;
    return a->n_temas;
}

const char *album_titulo(album_t *a) {
    if (a == NULL)
        return NULL;
    return a->titulo;
}

const char *album_autor(album_t *a) {
    if (a == NULL)
        return NULL;
    return a->autor;
}

const char *album_titulo_tema(album_t *a, int i) {
    if (a == NULL || i < 0 || i >= a->n_temas)
        return NULL;
    return a->temas[i];
}

void album_destruir(album_t *a) {
    if (a == NULL)
        return;

    free(a->autor);
    free(a->titulo);

    for (size_t i = 0; i < a->n_temas; i++)
        free(a->temas[i]);

    free(a->temas);
    free(a);
}

int main(void) {
    album_t *a = album_crear("Metallica", "Metallica");
    assert(a != NULL);

    assert(!strcmp(album_titulo(a), "Metallica"));
    assert(!strcmp(album_autor(a), "Metallica"));

    assert(album_agregar_tema(a, "Enter Sandman"));
    assert(album_agregar_tema(a, "Sad but True"));
    char tema3[] = "Holier than Thou";
    assert(album_agregar_tema(a, tema3));
    assert(album_agregar_tema(a, "The Unforgiven"));
    assert(album_agregar_tema(a, "Wherever I May Roam"));
    assert(album_agregar_tema(a, "Don't Tread on Me"));
    assert(album_agregar_tema(a, "Through the Never"));
    assert(album_agregar_tema(a, "Nothing Else Matters"));
    assert(album_agregar_tema(a, "Of Wolf and Man"));
    assert(album_agregar_tema(a, "The God That Failed"));
    assert(album_agregar_tema(a, "My Friend of Misery"));
    assert(album_agregar_tema(a, "The Struggle Within"));

    assert(album_cantidad_temas(a) == 12);

    assert(!strcmp(album_titulo_tema(a, 2), "Holier than Thou"));
    // verificamos que el TDA guarda su propia copia de la cadena, en lugar de
    // simplemente guardar el puntero
    assert(album_titulo_tema(a, 2) != tema3);

    album_destruir(a);

    printf("%s: OK\n", __FILE__);
    return 0;
}

// 24 min