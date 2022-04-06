#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define ejercicio 3

#define N_Ejercicio 59

#if N_Ejercicio == 1
#elif N_Ejercicio == 2
#elif N_Ejercicio == 3
#endif

#if ejercicio == 1

void subcadena(char destino[], const char origen[], size_t inicio, size_t fin) {

    for (size_t i = inicio >= 0 ? inicio : 0; i < fin && origen[i]; i++) {

        destino[inicio >= 0 ? i - inicio : i] = origen[i];
    }
}

int main(void) {

    char buffer[20];

    subcadena(buffer, "Algoritmos", 2, 6);

    printf("%s\n", buffer);
}

#elif ejercicio == 2

#define N 3
#define M 3

void combinar_filas(float mat[N][M], size_t n, size_t m, float multiplier) {

    for (size_t i = n; i < M; i++)
        mat[n][i] += mat[m][i] * multiplier;
}

int main(void) {

    float mat[N][M] = {

        {0.56, -5.1, 3.2},
        {53.6, 6.1, 1.2},
        {-0.56, 4.7, -9.2}};

    combinar_filas(mat, 1, 0, 2);

    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            printf("%1.2f  ", mat[i][j]);
        }
        printf("\n");
    }
}

#elif ejercicio == 3

// #include <time.h>

bool entradaValida(int datoValido, const char *string) {

    char *errChar = NULL;
    datoValido = strtol(string, &errChar, 10);

    if(datoValido < 1 || datoValido > 6){
        printf("Fuera de rango [1 - 6]\n");
        return false;
    }

    return (errChar == string || *errChar !='\n') ? false : true;
}

bool estanCargados(int cantidadTiros, int repeticiones, int valorEnsayo) {

    const int secuenciaPrueba[] = {1, 1, 2, 6, 5, 5, 5};

    int repCont = 0;

    for (size_t i = 0; i < cantidadTiros; i++) {

        if (valorEnsayo == secuenciaPrueba[i])
            repCont++;

        if (repCont == repeticiones)
            return true;
    }

    return false;
}

int main(void) {

    char buffer[10];

    enum estados {
        CANTIDAD_DE_TIROS,
        CANTIDAD_REPETICIONES,
        VALOR_ENSAYO,
        RESULTADO_ENSAYO
    };

    unsigned int modoEntrada = CANTIDAD_DE_TIROS;

    int d[3] = {0};

    printf("Ingrese la cantidad de tiros a realizar\n");

    while (fgets(buffer, sizeof(buffer), stdin)){

        switch (modoEntrada) {

        case CANTIDAD_DE_TIROS:
            printf("Ingrese la cantidad de tiros a realizar\n");
            if (entradaValida(d[modoEntrada], buffer))
                modoEntrada = CANTIDAD_REPETICIONES;
            else
                printf("Los datos ingresados son invalidos. Vuelva a intentarlo.\n");
            break;

        case CANTIDAD_REPETICIONES:
            printf("Ingrese la cantidad de repeticiones necesarias para considerar que el dado esta cargado\n");
            if (entradaValida(d[modoEntrada], buffer))
                modoEntrada = VALOR_ENSAYO;
            else
                printf("Los datos ingresados son invalidos. Vuelva a intentarlo.\n");
            break;

        case VALOR_ENSAYO:
            printf("Ingrese el valor de ensayo\n");
            if (entradaValida(d[modoEntrada], buffer))
                modoEntrada = RESULTADO_ENSAYO;
            else
                printf("Los datos ingresados son invalidos. Vuelva a intentarlo.\n");
            break;

        case RESULTADO_ENSAYO:
            printf("Resultado: %s\n", estanCargados(d[CANTIDAD_DE_TIROS], d[CANTIDAD_REPETICIONES],d[VALOR_ENSAYO])? "ESTAN CARGADOS":"NO ESTAN CARGADOS");

        default:
            break;
        }
    }

}
#elif ejercicio == 4

int main()
{
	char* end = NULL;
	char buf[255];
	long n = 0;

	printf("Enter an integer:\n");

	while (fgets(buf, sizeof(buf), stdin)) {
		n = strtol(buf, &end, 10);
		if (end == buf || *end !='\n')
			printf("Not recognised as an integer. Please enter an integer:\n");
	    else
            break;
	}

	printf("You entered %ld\n", n);
}
#endif