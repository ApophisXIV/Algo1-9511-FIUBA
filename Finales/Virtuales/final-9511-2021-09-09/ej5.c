#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------------------------------- */
// Invariante de representacion:
/* -------------------------------------------------------------------------- */
// - Si size == 0, entonces data == NULL
// - Si size > 0, entonces data != NULL
// - El tamaño del arreglo dinamico es el mismo que expresa "size"
// - Todos los punteros apuntan a memoria valida
/* -------------------------------------------------------------------------- */

typedef struct vecf_t {
    float *data;    // Puntero a un array de floats
    size_t size;    // Tamaño del array
} vecf_t;

vecf_t *vecf_crear() {
    vecf_t *v = malloc(sizeof(vecf_t));
    if (v == NULL)
        return NULL;

    v->data = NULL;
    v->size = 0;
    return v;
}

void vecf_destruir(vecf_t *v) {
    if (v == NULL)
        return;
    free(v->data);
    free(v);
}

size_t vecf_cantidad(const vecf_t *v) {
    if (v == NULL)
        return 0;
    return v->size;
}

bool vecf_agregar(vecf_t *v, float f) {

    if (v == NULL)
        return false;

    float *aux_vecf = realloc(v->data, sizeof(float *) * v->size + 1);
    if (aux_vecf == NULL)
        return false;

    v->data = aux_vecf;
    v->data[v->size++] = f;

    return true;
}

float vecf_suma(const vecf_t *v) {
    float suma = 0.0f;
    for (size_t i = 0; i < v->size; suma += v->data[i++])
        ;
    return suma;
}

int main(void) {
    vecf_t *v = vecf_crear();
    assert(v != NULL);
    assert(vecf_cantidad(v) == 0);

    vecf_agregar(v, 4.0f);
    assert(vecf_cantidad(v) == 1);

    vecf_agregar(v, 10.5f);
    assert(vecf_cantidad(v) == 2);

    assert(vecf_suma(v) == 14.5f);

    vecf_destruir(v);

    // OPCIONAL: Pruebas adicionales

    printf("%s: OK\n", __FILE__);
    return 0;
}
