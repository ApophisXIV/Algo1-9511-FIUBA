#include <stdio.h>

int main(int argc, char *argv[]){

    int c; //Es int ya que getchar devuelve un caracter o un EOF. EOF no es un caracter.

    if(argc != 2){
        fprintf(stderr,"Uso: %s [origen] [destino]\n", argv[0]);
        return 1;
    }

    //Antes de abrir el archivo de escritura hay que abrir el archivo de lectura para evitar que por error se borre el archivo de destino.
    FILE *fi = fopen(argv[1], "rt");
    if(fi == NULL){
        fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }

    FILE *fo = fopen(argv[2], "wt");
    if (fo == NULL){
        fclose(fi);
        fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[2]);
        return 1;
    }

    while((c = getchar()) != EOF){
        fputc(c, fo);
    }

    fclose(fi);
    fclose(fo);

    return 0;
}



int main(int argc, char *argv[]){

    int c; //Es int ya que getchar devuelve un caracter o un EOF. EOF no es un caracter.

    if(argc != 2){
        fprintf(stderr,"Uso: %s [origen] [destino]\n", argv[0]);
        return 1;
    }

    //Antes de abrir el archivo de escritura hay que abrir el archivo de lectura para evitar que por error se borre el archivo de destino.
    FILE *fi = fopen(argv[1], "rt");
    if(fi == NULL){
        fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[1]);
        return 1;
    }

    FILE *fo = fopen(argv[2], "wt");
    if (fo == NULL){
        fclose(fi);
        fprintf(stderr, "No se pudo abrir el archivo %s\n", argv[2]);
        return 1;
    }

    while((c = getchar()) != EOF){
        fputc(c, fo);
    }

    fclose(fi);
    fclose(fo);

    return 0;
}

// No 

//Dato de color: El int que devuelve printf tira la cantidad de caracteres que se imprimieron.
