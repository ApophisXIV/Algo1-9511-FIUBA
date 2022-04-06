#include <stdio.h>
#include <stdlib.h>

#define MAX_STR 100
#define MAX_VECTOR 100

int main(void){
    char aux[MAX_STR];
    float v[MAX_VECTOR];
    size_t n=0;
    
    //Se lo suele llamar descriptor de archivo.
    FILE *fi = fopen("numeros.txt", "r"); //Abrimos el archivo en modo lectura. En los parametros recibe el nombre de la ruta donde vive el archivo.
    //---------Los principales---------
    //r: read
    //w: write
    //t: text   | En linux el manejo de archivos es diferente. En windows es texto. En linux es binario. Es lo mismo que poner r directamente.
    //b: binary | En linux el manejo de archivos es diferente. En windows es texto. En linux es binario. Es lo mismo que poner r directamente.
    //a: append 
    //---------Los secundarios---------
    //r+: read and write
    //w+: write and read
    //a+: append and read
    //---------------------------------
    //Si no se puede abrir el archivo, se devuelve NULL.
    if(fi == NULL){
        fprintf(stderr,"No se pudo abrir el archivo.\n");
        return 1;
    }
  
    while (fgets(aux, MAX_STR, fi) != NULL){
        v[n++] = atof(aux);
    }  
    
    //Una buena practica es liberar el uso del archivo lo mas rapido posible despues de usarlo.
    fclose(fi);


    /* ---------------- Redirigir los datos de un archivo a otro. --------------- */
    FILE *fo = fopen("salida.txt","wt"); //!OJO! Si el archivo ya existe, se sobreescribe. (Borra todo lo que hay en el archivo)
    if(fo == NULL){
        //Aca seria interesante liberar el otro archivo que se abrio. fclose(fi);
        fprintf(stderr,"No se pudo abrir el archivo de salida.\n");
        return 1;
    }

    //Redirigir los datos de un archivo a otro.


    
    for (size_t i = 0; i < n; i++)
        // printf("%f\n", v[i]);
        // fprintf(stdout,"%f\n", v[i]); //Equivalente a printf
        // fprintf(stderr,"%f\n", v[i]);
        fprintf(fo,"%f\n", v[i]);

    fclose(fo);

    return 0;
}

/* ------------------------------ Introduccion ------------------------------ */
//En C se diferencian 2 tipos de archivos principales. Archivos de lectura y archivos de escritura.
//Otra forma de categorizar los archivos es por el tipo de dato que se almacenan (Texto) (Binarios). 
//Para leer un archivo de texto se utiliza la funcion fgets() y para escribir un archivo de texto se utiliza la funcion fprintf(), fputs(), fputc(). !OJO fputs tiene una diferencia con puts!

/* -------------------------- Apertura de archivos -------------------------- */
//Para abrir un archivo se utiliza la funcion fopen().
//La funcion fopen() recibe como parametros el nombre del archivo y el modo de apertura.

/* ------------------------------ Fin de linea ------------------------------ */
//La funcion putchar('\n') imprime un salto de linea sin importar el sistema operativo.