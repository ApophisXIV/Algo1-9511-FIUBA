#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// HACER: declarar el tipo de dato e implementar las funciones pedidas

// Sea el TDA Conjunto, que permite almacenar un conjunto de números enteros entre
// 0 y k - 1 (inclusive). En un conjunto, un número cualquiera puede pertenecer o no, pero no
// puede estar incluido más de una vez.

typedef struct {
    bool *num;
    size_t capacidad;
} conjunto_t;

conjunto_t *conjunto_crear(size_t k) {
    if (k == 0)
        return NULL;

    conjunto_t *conjunto = malloc(sizeof(conjunto_t));
    if (conjunto == NULL)
        return NULL;

    conjunto->num = calloc(k, sizeof(bool));
    if (conjunto->num == NULL) {
        free(conjunto);
        return NULL;
    }

    conjunto->capacidad = k > 1 ? k - 1 : 1;

    return conjunto;
}

bool conjunto_valido(const conjunto_t *c, int n) {
    return !(c == NULL || n < 0 || n > c->capacidad);
}

bool conjunto_pertenece(const conjunto_t *c, int n) {
    if (conjunto_valido(c, n))
        return c->num[n];
    return false;
}

void conjunto_agregar(conjunto_t *c, int n) {
    if (conjunto_valido(c, n) && c->num[n] == false)
        c->num[n] = true;
}
void conjunto_quitar(conjunto_t *c, int n) {
    if (conjunto_valido(c, n) && c->num[n] == true)
        c->num[n] = false;
}

void conjunto_eliminar(conjunto_t *c) {
    if (c == NULL)
        return;
    free(c->num);
    free(c);
}

void conjunto_imprimir(const conjunto_t *c) {
    if (c == NULL)
        return;
    for (size_t i = 0; i < c->capacidad + 1; i++) {
        if (c->num[i] == true)
            printf("%lu ", i);
        else
            printf("- ");
    }
    printf("\n");
    for (size_t i = 0; i < c->capacidad + 1; i++)
        printf("%d ", c->num[i]);
    printf("\n\n");
}

int main(void) {
    conjunto_t *c = conjunto_crear(10);    // los numeros deben ser entre 0 y 9
    assert(c != NULL);

    conjunto_imprimir(c);

    assert(!conjunto_pertenece(c, 5));
    conjunto_agregar(c, 5);
    conjunto_imprimir(c);
    assert(conjunto_pertenece(c, 5));
    conjunto_quitar(c, 5);
    conjunto_imprimir(c);
    assert(!conjunto_pertenece(c, 5));
    conjunto_imprimir(c);

    conjunto_eliminar(c);

    // OPCIONAL: Pruebas adicionales. Sugerencias:
    // - agregar mas numeros
    // - agregar un numero que ya pertenece
    // - quitar un numero que no pertenece

    conjunto_t *c2 = conjunto_crear(8);
    assert(c2 != NULL);
    conjunto_agregar(c2, 5);
    conjunto_agregar(c2, 5);
    conjunto_agregar(c2, 6);
    conjunto_agregar(c2, 9);

    assert(conjunto_pertenece(c2, 5));
    assert(conjunto_pertenece(c2, 6));
    assert(!conjunto_pertenece(c2, 9));

    conjunto_eliminar(c2);

    printf("%s: OK\n", __FILE__);
    return 0;
}

// 8 min
