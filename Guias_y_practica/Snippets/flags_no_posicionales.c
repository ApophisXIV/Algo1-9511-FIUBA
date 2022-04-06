/*
Escriba un programa que cuente la cantidad de líneas de un archivo, si el programa recibe el argumento -l.
Opcionalmente, agregue al programa la posibilidad de contar palabras si recibe el argumento -w y bytes si recibe
el argumento -c. Si recibe más de un archivo como argumento, imprime los totales, como se muestra a continuación:

$ ./mi_wc -l texto.txt
4 texto.txt
$ ./mi_wc -c texto.txt
98 texto.txt
$ ./mi_wc -w texto.txt
19 texto.txt
$ ./mi_wc -l -c -w texto.txt
 4 19 98 texto.txt
$ ./mi_wc -c -w -l texto.txt
 4 19 98 texto.txt
$ ./mi_wc -w -l -c texto.txt completa.txt
  4  19  98 texto.txt
 16  78 404 completa.txt
 20  97 502 total
*/

#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv) {

    if (argc < 3) {
        fprintf(stderr, "Argumentos inválidos\n");
        return 1;
    }

    //!--------------------------------------------------------------------------------------------------
    //! SNIPPET_START: flags_no_posicionales ------------------------------------------------------------
    //!--------------------------------------------------------------------------------------------------

    bool flag_l = false;
    bool flag_w = false;
    bool flag_b = false;

    // Invariante de ciclo
    int i = 1;
    // Arreglo que contiene las posiciones de los flags
    int flags[3] = {0};

    for (; i < argc; ++i) {

        if (strcmp(argv[i], "-l") == 0) {
            flag_l = true;
            flags[0] = i;
        } else if (strcmp(argv[i], "-w") == 0) {
            flag_w = true;
            flags[1] = i;
        } else if (strcmp(argv[i], "-c") == 0) {
            flag_b = true;
            flags[2] = i;
        } else if (strlen(argv[i]) < 3) {    // Si el argumento es menor a 3 no es un flag valido ni un archivo
            fprintf(stderr, "Argumento inválido.\n");
            return 1;
        }
    }

    // Si no se recibio al menos uno de los flags -l, -w, -c, se imprime error
    if (!flag_l && !flag_w && !flag_b) {
        fprintf(stderr, "Argumentos inválidos. No se detectan flags\n");
        return 1;
    }

    printf("Flags: %s%s%s\n", flag_l ? "l" : "", flag_w ? "w" : "", flag_b ? "c" : "");

    //!--------------------------------------------------------------------------------------------------
    //! SNIPPET_END: flags_no_posicionales --------------------------------------------------------------
    //!--------------------------------------------------------------------------------------------------

    size_t total_lineas = 0;
    size_t total_palabras = 0;
    size_t total_bytes = 0;

    size_t cant_archivos = 0;

    int j = 1;
    for (; j < argc; ++j) {

        //! SNIPPET_USAGE: flags_no_posicionales_archivos ------------------------------------------------
        // Me aseguro de que el argumento que le paso a fopen despues no sea un flag
        if (j == flags[0] || j == flags[1] || j == flags[2])
            continue;
        //!------------------------------------------------------------------------------------------------

        size_t cant_lineas = 0;
        size_t cant_palabras = 0;
        size_t cant_bytes = 0;

        cant_archivos++;

        FILE *f = fopen(argv[j], "r");
        if (f == NULL) {
            fprintf(stderr, "No se pudo abrir el archivo <%s>\n", argv[j]);
            return 1;
        }

        int c;
        while ((c = fgetc(f)) != EOF) {

            if (c == '\n') {
                ++cant_lineas;
                ++cant_palabras;
            }

            if (c == ' ' || c == '\t')
                ++cant_palabras;

            ++cant_bytes;
        }

        fclose(f);

        total_lineas += cant_lineas;
        total_palabras += cant_palabras;
        total_bytes += cant_bytes;

        //! SNIPPET_USAGE: flags_no_posicionales_archivos ------------------------------------------------
        // Dependiendo de los flags que se hayan pasado, se imprimen los resultados
        if (flag_l)
            printf("%zu ", cant_lineas);
        if (flag_w)
            printf("%zu ", cant_palabras);
        if (flag_b)
            printf("%zu ", cant_bytes);
        //!------------------------------------------------------------------------------------------------

        printf("%s\n", argv[j]);
    }

    // Si se recibio mas de un archivo, se imprime el total
    if (cant_archivos > 1) {

        //! SNIPPET_USAGE: flags_no_posicionales_archivos ------------------------------------------------
        // Dependiendo de los flags que se hayan pasado, se imprimen los resultados
        if (flag_l)
            printf("%zu ", total_lineas);
        if (flag_w)
            printf("%zu ", total_palabras);
        if (flag_b)
            printf("%zu ", total_bytes);
        //!------------------------------------------------------------------------------------------------

        printf("total\n");
    }

    return 0;
}