#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITULO 64
#define MAX_AUTOR 64

typedef struct libro {
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    uint16_t anno_publicacion;
} libro_t;

int libros_anno_cmp(const void *a, const void *b) {
    libro_t *libro_a = (libro_t *)a;
    libro_t *libro_b = (libro_t *)b;
    return libro_a->anno_publicacion - libro_b->anno_publicacion;
}

int libros_str_cmp(const void *a, const void *b) {
    libro_t *libro_a = (libro_t *)a;
    libro_t *libro_b = (libro_t *)b;
    return strcmp(libro_a->titulo, libro_b->titulo);
}

void ordenar_libros(libro_t libros[], size_t n) {
    if (n <= 1)
        return;

    //------------------------------------------------------
    // O (n^2)
    // for (size_t i = 0; i < n - 1; i++) {
    //     for (size_t j = i + 1; j < n; j++) {
    //         if (libros[i].anno_publicacion > libros[j].anno_publicacion) {
    //             libro_t aux = libros[i];
    //             libros[i] = libros[j];
    //             libros[j] = aux;
    //         } else if (libros[i].anno_publicacion == libros[j].anno_publicacion) {
    //             if (strcmp(libros[i].titulo, libros[j].titulo) > 0) {
    //                 libro_t aux = libros[i];
    //                 libros[i] = libros[j];
    //                 libros[j] = aux;
    //             }
    //         }
    //     }
    // }
    //------------------------------------------------------
    // O(n log n)
    qsort(libros, n, sizeof(libro_t), libros_anno_cmp);

    // O(n)
    for (size_t i = 0; i + 1 < n; i++)
        if (libros[i].anno_publicacion == libros[i + 1].anno_publicacion) {
            libro_t aux = libros[i];
            libros[i] = libros[i + 1];
            libros[i + 1] = aux;
        }
    //------------------------------------------------------
    // O(n log n)
    // qsort(libros, n, sizeof(libro_t), libros_anno_cmp);

    // O(n log n) + O(n)
    // for (size_t i = 0; i + 1 < n; i++)
    //     if (libros[i].anno_publicacion == libros[i + 1].anno_publicacion)
    //         qsort(libros + i, 2, sizeof(libro_t), libros_str_cmp);
    //------------------------------------------------------
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

// 30 min