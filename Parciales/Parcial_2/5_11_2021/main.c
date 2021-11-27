/**
 * @file main.c
 * @author Rodriguez Guido Ezequiel (guerodriguez@fi.uba.ar)
 * @Note Padron 108723
 * @version 1.0
 * @date 2021-11-5
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N_EJERCICIO 3

#if N_EJERCICIO == 1

// MSB                                           LSB
// +-----+-----+-----+-----+-----+-----+-----+-----+
// | DER | FRE | G_2 | G_1 | G_0 | V_2 | V_1 | V_0 |
// +-----+-----+-----+-----+-----+-----+-----+-----+
//    7     6     5     4     3     2     1     0

// Si DER es 1 -> El coche se mueve a la derecha e incrementa en 1 el valor de giro. El valor de giro no puede ser mayor a 7.
// Si DER es 0 -> El coche se mueve a la izquierda y decrementa en 1 el valor de giro. El valor de giro no puede ser menor a 0.

#define DER_MASK 0x80       // 1000 0000 - Flag Derecha
#define FRE_MASK 0x40       // 0100 0000 - Flag Freno
#define G_MASK 0x38         // 0011 1000 - Grupo de bits de G
#define G_MAX_LIM G_MASK    // 0011 1000 - Limite superior de G (7)
#define G_MIN_LIM 0x00      // 0011 1000 - Limite inferior de G (0)
#define G_ADD 0x08          // 0000 1000 - Incremento de G
#define G_SHIFT 0x03        // 0000 0011 - Desplazamiento de G
bool girar_derecha(uint8_t *r) {

    if (*r & DER_MASK) {    // Si el flag DER es 1

        if ((*r & G_MASK) == G_MAX_LIM)    // Si el valor de giro ya es igual a 7
            return false;                  // No puedo girar mas a la derecha
        *r += G_ADD;                       // Incremento el valor de giro

        return true;
    }

    else {

        if ((*r & G_MASK) == G_MIN_LIM) {    // Si el valor de giro ya es igual a 0
            *r &= ~G_MASK;                   // Limpio el valor de giro
            *r &= ~DER_MASK;                 // Limpio el flag DER
            *r |= G_ADD;                     // Incremento el valor de giro
            *r |= DER_MASK;                  // Seteo el flag DER
            return false;                    // No puedo girar mas a la izquierda
        }

        *r -= G_ADD;    // Decremento el valor de giro
        return true;
    }

    return false;
}

int main(void) {

    uint8_t r = 0x30;    // 0 0 110 000 -> Valor de giro inicial

    girar_derecha(&r);
    printf("El coche tiene un valor de giro de %x\n", (r & G_MASK) >> G_SHIFT);

    r = 0x00;
    girar_derecha(&r);
    printf("El coche tiene un valor de giro de %x\n", (r & G_MASK) >> G_SHIFT);

    r = 0xA0;
    girar_derecha(&r);
    printf("El coche tiene un valor de giro de %x\n", (r & G_MASK) >> G_SHIFT);

    r = 0xB8;
    girar_derecha(&r);
    printf("El coche tiene un valor de giro de %x\n", (r & G_MASK) >> G_SHIFT);

    return 0;
}

#elif N_EJERCICIO == 2

char *join(const char **ss, char sep) {

    size_t i;
    size_t largo = 0;

    for (i = 0; ss[i] != NULL; i++)    // Calculo la longitud de las cadena
        largo += strlen(ss[i]);

    char *s = malloc(largo + i + 1);    // Longitud cadenas + separadores + '\0'

    s[0] = '\0';

    if (s == NULL)
        return NULL;

    for (size_t j = 0; j < i; j++) {
        strcat(s, ss[j]);
        if (j < i - 1) {
            strcat(s, &sep);
        }
    }

    s[strlen(s)] = '\0';

    return s;
}

int main(void) {

    const char *s[] = {"Hola", "que", "tal", NULL};

    char *str = join(s, '|');

    printf("%s\n", str);

    free(str);

    return 0;
}

#elif N_EJERCICIO == 3

int *generar_ruido(int maximo, size_t *n) {

    *n = 0;

    int *ruido = malloc(sizeof(int));

    if (ruido == NULL)
        return NULL;

    ruido[(*n)++] = maximo;

    size_t i;

    for (i = 0; ruido[i] <= maximo; i++) {

        int *ruido_vec_aux = realloc(ruido, sizeof(int) * (((*n)++) + 1));

        if (ruido_vec_aux == NULL){
            free(ruido);
            return NULL;
        }

        ruido = ruido_vec_aux;

        ruido[i+1] = rand();
    }


    return ruido;
}

int main(void) {

    srand(time(NULL));

    size_t n = 0;
    int *ruido_vec = generar_ruido(11, &n);

    for (size_t i = 0; i < n; i++) {
        printf("%d\n", ruido_vec[i]);
    }

    if(n > 0)
        free(ruido_vec);

    return 0;
}

#endif