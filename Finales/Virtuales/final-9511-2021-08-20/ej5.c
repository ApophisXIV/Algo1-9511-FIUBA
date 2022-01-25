#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define MAX_CADENA 128

// HACER: declarar el tipo album_t

album_t *album_crear(const char *autor, const char *titulo) {
    // HACER: implementar
}

bool album_agregar_tema(album_t *a, const char *titulo_tema) {
    // HACER: implementar
}

size_t album_cantidad_temas(album_t *a) {
    // HACER: implementar
}

const char *album_titulo(album_t *a) {
    // HACER: implementar
}

const char *album_autor(album_t *a) {
    // HACER: implementar
}

const char *album_titulo_tema(album_t *a, int i) {
    // HACER: implementar
}

void album_destruir(album_t *a) {
    // HACER: implementar
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


