#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

/* HACER:

Escribir una funcion que recibe un archivo previamente abierto y los datos de una sucursal,
y escribe en el archivo los datos con el formato descripto.

Escribir una funcion que recibe un archivo previamente abierto, lee los datos de una sucursal
y los devuelve (ya sea por el valor de retorno o mediante los parametros).

*/

bool escribir_sucursal(FILE *fp, const char* nombre, const float lat, const float lon){
    if(fp == NULL || nombre == NULL)
        return false;
    
    const uint8_t len = strlen(nombre);

    if(fwrite(&len, sizeof(uint8_t), 1, fp) != 1)
        return false;

    if(fwrite(nombre, sizeof(char), len, fp) != len) 
        return false;
    
    if(fwrite(&lat, sizeof(float), 1, fp) != 1)
        return false;

    if(fwrite(&lon, sizeof(float), 1, fp) != 1)
        return false;

    return true;
}

bool leer_sucursal(FILE *fp, char* nombre, float* lat, float* lon){
    if(fp == NULL || nombre == NULL || lat == NULL || lon == NULL)
        return false;

    uint8_t len;
    if(fread(&len, sizeof(uint8_t), 1, fp) != 1)
        return false;

    if(fread(nombre, sizeof(char), len, fp) != len)
        return false;

    nombre[len] = '\0';

    if(fread(lat, sizeof(float), 1, fp) != 1)
        return false;

    if(fread(lon, sizeof(float), 1, fp) != 1)
        return false;

    return true;
}

int main(void) {
    char *nombre = "Caballito 1";
    float lat = -34.6145096f, lon = -58.4431307f;

    char *nombre_archivo = "sucursal.bin";

    // PRUEBA:
    // - abrir el archivo en modo escritura y escribir en el mismo los datos de la sucursal
    // - abrir el archivo en modo lectura y leer del mismo los datos previamente escritos
    // - verificar con assert() que los datos leidos son correctos

    FILE *fp = fopen(nombre_archivo, "wb");
    assert(fp != NULL);
    assert(escribir_sucursal(fp, nombre, lat, lon));
    fclose(fp);

    fp = fopen(nombre_archivo, "rb");

    char nombre_leido[32];
    float lat_leido, lon_leido;

    assert(leer_sucursal(fp, nombre_leido, &lat_leido, &lon_leido));
    assert(strcmp(nombre, nombre_leido) == 0);
    assert(lat == lat_leido);
    assert(lon == lon_leido);
    fclose(fp);

    printf("%s: OK\n", __FILE__);
    return 0;
}

// 6 min