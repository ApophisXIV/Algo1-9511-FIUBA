/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief Arreglos - Guia 2
 * @version 0.1
 * @date 2021-10-22
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>
#define N_EJERCICIO 1

/* -------------------------------------------------------------------------- */
/*                                  Arreglos                                  */
/* -------------------------------------------------------------------------- */
#if N_EJERCICIO == 1

/**
 * a) Un arreglo puede almacenar diferentes pos de valores.
 * 
 * Falso. Un arreglo en memoria se ordena como una serie consecutiva de elementos
 * de una misma longitud por lo que no puede estar conformado por diferentes tipos 
 * que tengan diferente longitud.
 * 
 * b) En la expresión a[i], siendo a un arreglo, el subíndice i puede ser de 
 * tipo double.
 * 
 * Falso. Los arreglos tienen indices naturales. "No existe algo tal como un medio 
 * elemento"
 * 
 * c) Si hay menos inicializadores en la lista de inicializadores del arreglo que 
 * elementos en el arreglo, C automticamente inicializa los elementos restantes con 
 * el ultimo valor en la lista de inicializadores.
 * 
 * Falso. 
 * 
 * d) Es un error si una lista de inicializadores contiene más inicializadores que 
 * la cantidad de elementos que hay en el arreglo.
 * 
 * 
 * e) Si se pasa un elemento a una función, en la forma a[i], y se modifica ese valor 
 * en el interior de la función, el arreglo contendrá el valor modificado.
 * 
 */

int main(void){

struct main
{
    
};


    int a[8];
    for (size_t i = 0; i < 8; i++)
    {
        printf("%d %zu\n",a[i],sizeof(float));
    }
    
}

#endif  // Arreglos

/* -------------------------------------------------------------------------- */
/*                          Arreglos unidimensionales                         */
/* -------------------------------------------------------------------------- */

#if N_EJERCICIO == 2
#elif N_EJERCICIO == 3
#elif N_EJERCICIO == 4
#elif N_EJERCICIO == 5
#elif N_EJERCICIO == 6
#elif N_EJERCICIO == 7
#endif  // Arreglos unidimensionales

/* -------------------------------------------------------------------------- */
/*                   Funciones con arreglos unidimensionales                  */
/* -------------------------------------------------------------------------- */

#if N_EJERCICIO == 8
#elif N_EJERCICIO == 9
#elif N_EJERCICIO == 10
#elif N_EJERCICIO == 11
#elif N_EJERCICIO == 12
#elif N_EJERCICIO == 13
#elif N_EJERCICIO == 14
#elif N_EJERCICIO == 15
#endif  // Funciones con arreglos unidimensionales

/* -------------------------------------------------------------------------- */
/*                  Funciones con arreglos multidimensionales                 */
/* -------------------------------------------------------------------------- */

#if N_EJERCICIO == 16
#elif N_EJERCICIO == 17
#elif N_EJERCICIO == 18
#elif N_EJERCICIO == 19
#endif  // Funciones con arreglos multidimensionales

/* -------------------------------------------------------------------------- */
/*                              Graficos Net PBM                              */
/* -------------------------------------------------------------------------- */

#if N_EJERCICIO == 20
#elif N_EJERCICIO == 21
#elif N_EJERCICIO == 22
#elif N_EJERCICIO == 23
#elif N_EJERCICIO == 24
#endif  // Graficos Net PBM

/* -------------------------------------------------------------------------- */
/*                            Conway's game of LIFE                           */
/* -------------------------------------------------------------------------- */

#if N_EJERCICIO == 25
#elif N_EJERCICIO == 26
#elif N_EJERCICIO == 27
#elif N_EJERCICIO == 28
#elif N_EJERCICIO == 29
#elif N_EJERCICIO == 30
#endif  // Conway's game of LIFE
