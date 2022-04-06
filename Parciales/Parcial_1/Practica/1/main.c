#include <stdio.h>

void extraer_prefijo(char destino[], const char origen[], char car) {

    size_t j = 0, i = 0;

    for (i=0; origen[i]; i++) {

        if(origen[i] == car)
            j=i;
    }

    for (i=0; i < j; i++) {

        destino[i] = origen[i];
    }
}

int main(void) {

    char msg [] = "archivo.tar.gz";
    char cpyBuffer[sizeof(msg)-1];

    extraer_prefijo(cpyBuffer,msg,'.');

    printf("%s\n",cpyBuffer);

    return 0;
}

