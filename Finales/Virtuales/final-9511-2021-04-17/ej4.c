#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE 1024

bool uniq(const char *entrada, const char *salida) {
    if(entrada == NULL || salida == NULL)
        return false;
    
    FILE *f_entrada = fopen(entrada, "r");
    if(f_entrada == NULL)
        return false;

    FILE *f_salida = fopen(salida, "w");
    if(f_salida == NULL){
        fclose(f_entrada);
        return false;
    }

    char buffer[MAX_LINE];
    char buffer2[MAX_LINE];

    while(fgets(buffer, MAX_LINE, f_entrada) != NULL){
        if(fgets(buffer2, MAX_LINE, f_entrada) == NULL){
            fclose(f_entrada);
            fclose(f_salida);
            return false;
        }

        if(strcmp(buffer, buffer2) != 0){
            fprintf(f_salida,"%s", buffer);
            fprintf(f_salida,"%s", buffer2);
        }

    }

    fclose(f_entrada);
    fclose(f_salida);
    return true;

}

int main(void) {
    uniq("entrada.txt", "salida.txt");

    // salida.txt deberia contener:
    //
    //    I like to move it, move it
    //    Ya like to move it
    //    I like to move it, move it
    //    Ya like to move it

    printf("%s: OK (verificar el contenido de salida.txt)\n", __FILE__);
    return 0;
}
