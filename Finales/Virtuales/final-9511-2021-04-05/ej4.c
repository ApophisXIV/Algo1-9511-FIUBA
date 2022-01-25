#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

#define MAX_TITULO 64
#define MAX_AUTOR 64

typedef struct libro {
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    uint16_t anno_publicacion;
} libro_t;

void ordenar_libros(libro_t libros[], size_t n) {
    // HACER: implementar
}

int main(void) {
    libro_t libros[] = {
        {.titulo = "The Sittaford Mystery", .autor = "Agatha Christie", .anno_publicacion = 1931},
        {.titulo = "The Seven Dials Mystery", .autor = "Agatha Christie", .anno_publicacion = 1929},
        {.titulo = "The Murder at the Vicarage", .autor = "Agatha Christie", .anno_publicacion = 1930},
        {.titulo = "The Mystery of the Blue Train", .autor = "Agatha Christie", .anno_publicacion = 1928},
        {.titulo = "The Floating Admiral", .autor = "Agatha Christie", .anno_publicacion = 1931},
        {.titulo = "Giant's Bread", .autor = "Agatha Christie", .anno_publicacion = 1930},
    };

    ordenar_libros(libros, 6);

    libro_t libros_ordenados[] = {
        {.titulo = "The Mystery of the Blue Train", .autor = "Agatha Christie", .anno_publicacion = 1928},
        {.titulo = "The Seven Dials Mystery", .autor = "Agatha Christie", .anno_publicacion = 1929},
        {.titulo = "Giant's Bread", .autor = "Agatha Christie", .anno_publicacion = 1930},
        {.titulo = "The Murder at the Vicarage", .autor = "Agatha Christie", .anno_publicacion = 1930},
        {.titulo = "The Floating Admiral", .autor = "Agatha Christie", .anno_publicacion = 1931},
        {.titulo = "The Sittaford Mystery", .autor = "Agatha Christie", .anno_publicacion = 1931},
    };

    assert(memcmp(libros, libros_ordenados, sizeof(libros)) == 0);

    printf("%s: OK\n", __FILE__);
    return 0;
}

