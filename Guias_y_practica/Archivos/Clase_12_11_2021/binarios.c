#include <stdio.h>
#include <assert.h>

/* ---------------------------- Archivos binarios --------------------------- */
//12 -> BIN   -> 1100 -> !OJO! Ver si es little o big endian.
//12 -> TEXTO -> '1' '2'

//Ejmplos de aplicacion de archivos binarios:
//1. Persistencia de datos. (Volcar memoria). Depende fuertemente de la implementacion de la memoria.
//2. Archivos de intercambio de datos. (Ej: Fotos, videos, etc.). Esto hace que sea independiente del sistema operativo y el hardware.

//Funciones para operar con archivos binarios:
//fwrite(void *ptr, size_t size, size_t nmemb, FILE *stream); //Devuelve la cantidad de elementos escritos.
//fread(void *ptr, size_t size, size_t nmemb, FILE *stream); //Devuelve la cantidad de elementos leidos.

//En linux: Podemos ver lo que tiene el archivo con hd <archivo>. Ej: hd /home/usuario/archivo.bin
//Alternativamente podemos verlo con hexdump -C <archivo>. Ej: hexdump -C /home/usuario/archivo.bin

int main(void) {

    FILE *f = fopen("salida.bin", "wb"); //wb = write binary.
    if (f == NULL) return 1;

    int v[5] = {7, 10, 1, 67, 34};

    //v: Direccion de memoria del arreglo v.
    //sizeof(int): Tamaño de los elementos de v.
    //5: Cantidad de elementos a escribir.
    //f: Puntero al archivo de salida.
    
    // fwrite(v, sizeof(int), 5, f); //Devuelve la cantidad de elementos escritos.

    assert(fwrite(v, sizeof(int), 5, f)); //Posible validacion

    for (int i = 0; i < 5; i++)
        printf("%d\n", v[i]);


    fclose(f);

    return 0;
}