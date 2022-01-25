#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

// HACER: declarar el tipo de dato (y cualquier otro tipo de dato necesario)
typedef ??? examen_t;

// HACER: implementar las funciones
bool guardar_examenes(examen_t examenes[], size_t cantidad, const char *nombre_archivo) {
}

examen_t *cargar_examenes(const char *nombre_archivo, size_t *cantidad) {
}

int main(void) {
    examen_t examenes[] = {
        // HACER: inicializar el arreglo con 3 examenes
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
