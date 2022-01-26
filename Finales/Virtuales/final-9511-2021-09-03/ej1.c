#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// HACER: declarar el tipo persona_t
typedef struct {
    int dni;
    char *nombre;
    char *direccion;
} persona_t;

/* -------------------------------------------------------------------------- */
// Invariante de representacion:
/* -------------------------------------------------------------------------- */
// 


persona_t *persona_crear(int dni, const char *nombre, const char *direccion) {
    persona_t *p = malloc(sizeof(persona_t));
    if(p == NULL) return NULL;

    p->dni = dni;    
    
    p->nombre = malloc(strlen(nombre) + 1);
    if(p->nombre == NULL) {
        free(p);
        return NULL;
    }

    strcpy(p->nombre, nombre);

    p->direccion = malloc(strlen(direccion) + 1);
    if(p->direccion == NULL) {
        free(p->nombre);
        free(p);
        return NULL;
    }

    strcpy(p->direccion, direccion);

    return p;
}

void persona_destruir(persona_t *p) {

    if(p == NULL) return;

    free(p->nombre);
    free(p->direccion);
    free(p);
}


// O(log n)
persona_t *persona_buscar(int dni, persona_t *personas[], size_t n) {

    if(personas == NULL || n == 0) return NULL;

    int inicio = 0;
    int fin = n;
    int medio;

    while(inicio <= fin) {

        medio = (inicio + fin) / 2; // El medio es el elemento central

        if(personas[medio]->dni == dni) { // Si el elemento central es el que buscamos
            return personas[medio]; // Retornamos el elemento central
        }

        // Buscamos en el intervalo [inicio, medio]
        if(personas[medio]->dni < dni) { // Si el elemento central es menor que el que buscamos
            inicio = medio + 1; // El nuevo inicio es el elemento central + 1
        } 

        // Buscamos en el intervalo [medio, fin]
        else {
            fin = medio - 1; // El nuevo fin es el elemento central - 1
        }
    }

    return NULL;
}

int main(void) {

    persona_t *personas[] = {
        persona_crear(11111, "persona 1", "direccion 1"),
        persona_crear(22222, "persona 2", "direccion 2"),
        persona_crear(33333, "persona 3", "direccion 3"),
        persona_crear(44444, "persona 4", "direccion 4"),
    };

    persona_t *p = persona_buscar(33333, personas, 4);
    assert(p == personas[2]);

    // OPCIONAL: pruebas adicionales

    for (int i = 0; i < 4; i++) {
        persona_destruir(personas[i]);
    }

    printf("%s: OK\n", __FILE__);
    return 0;
}

