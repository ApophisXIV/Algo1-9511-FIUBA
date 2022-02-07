#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    PARCIAL,
    FINAL
} tipo_examen_t;

typedef struct {
    uint8_t dia;
    uint8_t mes;
    uint16_t anio;
} fecha_t;

// HACER: declarar el tipo de dato (y cualquier otro tipo de dato necesario)
typedef struct {
    fecha_t fecha;
    uint32_t padron;
    tipo_examen_t tipo;
    uint8_t calificacion;
} examen_t;

// HACER: implementar las funciones
bool guardar_examenes(examen_t examenes[], size_t cantidad, const char *nombre_archivo) {
    if (nombre_archivo == NULL || cantidad == 0)
        return false;

    FILE *f = fopen(nombre_archivo, "wb");
    if (f == NULL)
        return false;

    for (size_t i = 0; i < cantidad; i++)
        if (fwrite(&examenes[i], sizeof(examen_t), 1, f) != 1) {
            fclose(f);
            return false;
        }

    fclose(f);

    return true;
}

examen_t *cargar_examenes(const char *nombre_archivo, size_t *cantidad) {
    if (nombre_archivo == NULL || cantidad == NULL)
        return NULL;

    FILE *f = fopen(nombre_archivo, "rb");
    if (f == NULL)
        return NULL;

    examen_t *examenes = malloc(sizeof(examen_t));
    if (examenes == NULL) {
        fclose(f);
        return NULL;
    }

    size_t i = 0;
    while (fread(&examenes[i], sizeof(examen_t), 1, f) == 1) {
        i++;
        examen_t *examenes_aux = realloc(examenes, (i + 1) * sizeof(examen_t));
        if (examenes_aux == NULL) {
            free(examenes);
            fclose(f);
            return NULL;
        }
        examenes = examenes_aux;
    }

    fclose(f);

    *cantidad = i;
    return examenes;
}

int main(void) {
    examen_t examenes[3] = {
        {
            .fecha = {
                .dia = 1,
                .mes = 1,
                .anio = 2020
            },
            .padron = 1234567,
            .tipo = PARCIAL,
            .calificacion = 4
        },
        {
            .fecha = {
                .dia = 2,
                .mes = 2,
                .anio = 2020
            },
            .padron = 1234568,
            .tipo = FINAL,
            .calificacion = 10
        },
        {
            .fecha = {
                .dia = 3,
                .mes = 3,
                .anio = 2021
            },
            .padron = 1234569,
            .tipo = FINAL,
            .calificacion = 6
        }
    };

    bool ok = guardar_examenes(examenes, 3, "examenes.bin");
    assert(ok);

    size_t cantidad;
    examen_t *examenes2 = cargar_examenes("examenes.bin", &cantidad);
    assert(examenes2 != NULL);
    assert(cantidad == sizeof(examenes) / sizeof(examen_t));
    free(examenes2);

    // OPCIONAL: agregar pruebas adicionales para verificar que los datos leidos sean iguales

    printf("%s: OK\n", __FILE__);
    return 0;
}

// 17 min