#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

bool son_archivos_iguales_bin(FILE *f1, FILE *f2) {

    if(f1 == NULL || f2 == NULL)
        return false;

    fseek(f1, 0, SEEK_END);
    size_t f1_size = ftell(f1);
    fseek(f1, 0, SEEK_SET);

    fseek(f2, 0, SEEK_END);
    size_t f2_size = ftell(f2);
    fseek(f2, 0, SEEK_SET);

    uint8_t *buffer1 = malloc(f1_size);
    if(buffer1 == NULL)
        return false;

    uint8_t *buffer2 = malloc(f2_size);
    if(buffer2 == NULL) {
        free(buffer1);
        return false;
    }

    if(fread(buffer1, f1_size, 1, f1) != 1) {
        free(buffer1);
        free(buffer2);
        return false;
    }

    if(fread(buffer2, f2_size, 1, f2) != 1) {
        free(buffer1);
        free(buffer2);
        return false;
    }

    size_t i = 0;
    while(i < f1_size && i < f2_size && buffer1[i] == buffer2[i])
        i++;

    if(i == f1_size && i == f2_size) {
        free(buffer1);
        free(buffer2);
        return true;
    }

    fprintf(stderr, "Diferencia encontrada en el byte %zd\n", i);

    free(buffer1);
    free(buffer2);

    return false;
}


int main(int argc, char **argv) {
    // HACER: implementar el programa
    //
    // Se puede probar con los archivos provistos a.bin, b.bin, c.bin:
    //
    //   $ ./ej5 a.bin b.bin
    //   2
    //   $ ./ej5 a.bin c.bin
    //   4
    //   $ ./ej5 a.bin a.bin
    //   (no imprime nada porque son iguales)

    if(argc < 3) {
        fprintf(stderr,"Uso: %s <archivo1> <archivo2>\n", argv[0]);
        return 1;
    }

    FILE *f1 = fopen(argv[1], "rb");
    if(f1 == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }
    FILE *f2 = fopen(argv[2], "rb");
    if(f2 == NULL) {
        fclose(f1);
        fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[2]);
        return 1;
    }

    bool son_iguales = son_archivos_iguales_bin(f1, f2);

    fclose(f1);
    fclose(f2);

    if(son_iguales)
        printf("Son iguales\n");
    else
        printf("No son iguales\n");

    return 0;
}

