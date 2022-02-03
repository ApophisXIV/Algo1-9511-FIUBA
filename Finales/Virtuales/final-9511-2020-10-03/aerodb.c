#include "aerodb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CENTINELA 1
#define MAX_STR 63 + CENTINELA

typedef struct {
    char designacion[3 + CENTINELA];
    char nombre[MAX_STR];
    char ciudad[MAX_STR];
    char pais[MAX_STR];
    double lat, lon;
} aeropuerto_t;

struct aerodb {
    aeropuerto_t **aeropuertos;
    size_t n;
};

/* -------------------------------------------------------------------------- */
// Invariante de representacion:
/* -------------------------------------------------------------------------- */
// - Si n == 0, entonces aeropuertos == NULL
// - Si n > 0, entonces aeropuertos != NULL
// - El tamaño del arreglo dinamico de aeropuerto_t es el mismo que expresa n
// - Todos los punteros apuntan a memoria valida
/* -------------------------------------------------------------------------- */

// ---- Ejercicio 1 ---- (18 min)
aerodb_t *aerodb_crear() {
    aerodb_t *a = malloc(sizeof(aerodb_t));
    if (a == NULL)
        return NULL;
    a->aeropuertos = NULL;
    a->n = 0;
    return a;
}

int cmp_designacion(const void *a, const void *b) {
    aeropuerto_t *pa = *(aeropuerto_t **)a;
    aeropuerto_t *pb = *(aeropuerto_t **)b;
    return strcmp(pa->designacion, pb->designacion);
}

bool aerodb_agregar(aerodb_t *a, const char *designacion, const char *nombre, const char *ciudad, const char *pais, double lat, double lon) {
    if (a == NULL || designacion == NULL || nombre == NULL || ciudad == NULL || pais == NULL)
        return false;

    aeropuerto_t *aer = malloc(sizeof(aeropuerto_t));
    if (aer == NULL)
        return false;

    strcpy(aer->designacion, designacion);
    strcpy(aer->nombre, nombre);
    strcpy(aer->ciudad, ciudad);
    strcpy(aer->pais, pais);
    aer->lat = lat;
    aer->lon = lon;

    a->aeropuertos = realloc(a->aeropuertos, (a->n + 1) * sizeof(aeropuerto_t *));
    if (a->aeropuertos == NULL) {
        free(aer);
        return false;
    }

    a->aeropuertos[a->n++] = aer;

    // Ordenar por denominacion si el nuevo elemento es menor que el ultimo
    if (a->n > 1 && cmp_designacion(&a->aeropuertos[a->n - 2], &a->aeropuertos[a->n - 1]) > 0)
        qsort(a->aeropuertos, a->n, sizeof(aeropuerto_t *), cmp_designacion);

    return true;
}

size_t aerodb_cantidad(const aerodb_t *a) {
    if (a == NULL)
        return 0;
    return a->n;
}

// O(log n)
// Bsearch devuelve un puntero a un elemento del arreglo, los cuales a su vez son punteros a estructuras por lo que se requiere un doble puntero para poder acceder a los datos de la estructura
const char *aerodb_nombre(const aerodb_t *a, const char *designacion) {
    if (a == NULL || designacion == NULL)
        return NULL;

    aeropuerto_t **p = bsearch(&designacion, a->aeropuertos, a->n, sizeof(aeropuerto_t *), cmp_designacion);
    if (p == NULL)
        return NULL;
    return (*p)->nombre;
}

const char *aerodb_ciudad(const aerodb_t *a, const char *designacion) {
    if (a == NULL || designacion == NULL)
        return NULL;

    aeropuerto_t **p = bsearch(&designacion, a->aeropuertos, a->n, sizeof(aeropuerto_t *), cmp_designacion);
    if (p == NULL)
        return NULL;
    return (*p)->ciudad;
}

const char *aerodb_pais(const aerodb_t *a, const char *designacion) {
    if (a == NULL || designacion == NULL)
        return NULL;

    aeropuerto_t **p = bsearch(&designacion, a->aeropuertos, a->n, sizeof(aeropuerto_t *), cmp_designacion);
    if (p == NULL)
        return NULL;
    return (*p)->pais;
}

double aerodb_lat(const aerodb_t *a, const char *designacion) {
    if (a == NULL || designacion == NULL)
        return 0;

    aeropuerto_t **p = bsearch(&designacion, a->aeropuertos, a->n, sizeof(aeropuerto_t *), cmp_designacion);
    if (p == NULL)
        return 0;
    return (*p)->lat;
}

double aerodb_lon(const aerodb_t *a, const char *designacion) {
    if (a == NULL || designacion == NULL)
        return 0;

    aeropuerto_t **p = bsearch(&designacion, a->aeropuertos, a->n, sizeof(aeropuerto_t *), cmp_designacion);
    if (p == NULL)
        return 0;
    return (*p)->lon;
}

void aerodb_destruir(aerodb_t *a) {
    if (a == NULL)
        return;
    for (size_t i = 0; i < a->n; i++)
        free(a->aeropuertos[i]);
    free(a);
}

// ---- Ejercicio 2 ---- (11 min)
bool aerodb_escribir(const aerodb_t *a, const char *ruta) {
    if (a == NULL || ruta == NULL)
        return false;
    FILE *f = fopen(ruta, "wb");
    if (f == NULL)
        return false;

    fwrite(&a->n, sizeof(size_t), 1, f);    // Cantidad de elementos
    for (size_t i = 0; i < a->n; i++)
        if (fwrite(a->aeropuertos[i], sizeof(aeropuerto_t), 1, f) != 1) {
            fclose(f);
            return false;
        }

    fclose(f);
    return true;
}

aerodb_t *aerodb_leer(const char *ruta) {
    if (ruta == NULL)
        return NULL;

    FILE *f = fopen(ruta, "rb");
    if (f == NULL)
        return NULL;

    aerodb_t *a = aerodb_crear();
    if (a == NULL) {
        fclose(f);
        return NULL;
    }

    size_t n;
    if (fread(&n, sizeof(size_t), 1, f) != 1) {
        aerodb_destruir(a);
        fclose(f);
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        aeropuerto_t *aer = malloc(sizeof(aeropuerto_t));
        if (aer == NULL) {
            aerodb_destruir(a);
            fclose(f);
            return NULL;
        }

        if (fread(aer, sizeof(aeropuerto_t), 1, f) != 1) {
            aerodb_destruir(a);
            fclose(f);
            return NULL;
        }

        if (!aerodb_agregar(a, aer->designacion, aer->nombre, aer->ciudad, aer->pais, aer->lat, aer->lon)) {
            aerodb_destruir(a);
            fclose(f);
            return NULL;
        }
    }

    fclose(f);
    return a;
}

// ---- Ejercicio 3 ---- (3 min)
bool aerodb_buscar(aerodb_t *a, const char *designacion, char **nombre, char **ciudad, char **pais, double *lat, double *lon) {
    if (a == NULL || designacion == NULL || nombre == NULL || ciudad == NULL || pais == NULL || lat == NULL || lon == NULL)
        return false;

    aeropuerto_t **p = bsearch(&designacion, a->aeropuertos, a->n, sizeof(aeropuerto_t *), cmp_designacion);
    if (p == NULL)
        return false;

    *nombre = (*p)->nombre;
    *ciudad = (*p)->ciudad;
    *pais = (*p)->pais;
    *lat = (*p)->lat;
    *lon = (*p)->lon;

    return true;
}

// ---- Ejercicio 4 ---- (28 min)
double distancia(const double lat1, const double lon1, const double lat2, const double lon2) {
    return (lat1 - lat2) * (lat1 - lat2) + (lon1 - lon2) * (lon1 - lon2);
}

bool aerodb_mas_cercano(aerodb_t *a, double xlat, double xlon, char **nombre, char **ciudad, char **pais, double *lat, double *lon) {
    if (a == NULL || nombre == NULL || ciudad == NULL || pais == NULL || lat == NULL || lon == NULL)
        return false;

    double min = 0;
    aeropuerto_t *p = NULL;
    for (size_t i = 0; i < a->n; i++) {
        double d = distancia(xlat, xlon, a->aeropuertos[i]->lat, a->aeropuertos[i]->lon);
        if (i == 0 || d < min) {
            min = d;
            p = a->aeropuertos[i];
        }
    }

    if (p == NULL)
        return false;

    *nombre = p->nombre;
    *ciudad = p->ciudad;
    *pais = p->pais;
    *lat = p->lat;
    *lon = p->lon;

    return true;
}

// ---- Ejercicio 5 ---- (7 min)
#define MASK_SEG        0x3F 
#define MASK_MIN        0x3F
#define SHIFT_MIN       6
#define MASK_GRD        0xFF
#define SHIFT_GRD       12
#define MASK_SIGN_FLAG  0x01
#define SHIFT_SIGN_FLAG 20

void decodificar_angulo(uint32_t angulo_sexagesimal, bool *negativo, uint8_t *grados, uint8_t *minutos, uint8_t *segundos) {
    if (negativo == NULL || grados == NULL || minutos == NULL || segundos == NULL)
        return;

    *negativo = (angulo_sexagesimal >> SHIFT_SIGN_FLAG) & MASK_SIGN_FLAG;
    *grados = (angulo_sexagesimal >> SHIFT_GRD) & MASK_GRD;
    *minutos = (angulo_sexagesimal >> SHIFT_MIN) & MASK_MIN;
    *segundos = angulo_sexagesimal & MASK_SEG;
}
