
/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-09-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "main.h"
#include <math.h>

float producto_interno(const float a[3], const float b[3]) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float norma(const float a[3]) {
    return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

void normalizar(float a[3]) {

    const float __norma = norma(a);

    a[0] /= __norma;
    a[1] /= __norma;
    a[2] /= __norma;
}

void resta(float r[3], const float a[3], const float b[3]) {
    r[0] = a[0] - b[0];
    r[1] = a[1] - b[1];
    r[2] = a[2] - b[2];
}

float distancia_esfera(const float c[3], float r, const float o[3], const float d[3]) {

    float co[3] = {0};

    resta(co, c, o);

    const float cd = producto_interno(co, d);
    const float delta = pow(cd, 2) - producto_interno(co, co) + r * r;

    if (delta >= 0) {
        const float sqrtDelta = sqrt(delta);
        const float t = cd - sqrtDelta > 0 ? cd - sqrtDelta : cd + sqrtDelta;

        return t;
    }

    return INFINITO;
}

void normal_esfera(float normal[3], const float c[3], float r, const float p[3]) {

    resta(normal, p, c);

    normal[0] /= r;
    normal[1] /= r;
    normal[2] /= r;
}

void interpolar_recta(float p[3], const float o[3], const float d[3], float t) {
    p[0] = o[0] + t * d[0];
    p[1] = o[1] + t * d[1];
    p[2] = o[2] + t * d[2];
}

int computar_intensidad(const float cs[][3], const float rs[], size_t n_esferas, const float luz[3], const float o[3], const float d[3]) {
    float normalImpacto[3] = {0};
    float puntoImpacto[3] = {0};

#ifdef DEBUG
    LONG_H_LINE
#endif

    for (size_t i = 0; i < n_esferas; i++) {

        const float t = distancia_esfera(cs[i], rs[i], o, d);

        if (t != INFINITO) {

            interpolar_recta(puntoImpacto, o, d, t);
            normal_esfera(normalImpacto, cs[i], rs[i], puntoImpacto);

            for (size_t j = 0; j < n_esferas; j++) {

#ifdef DEBUG
                const int I = IA + II * producto_interno(normalImpacto, luz);
                DEBUG_TABLE
#endif
                if ((i != j) && ((distancia_esfera(cs[j], rs[j], puntoImpacto, luz) != INFINITO))) return IA;
                
#ifndef DEBUG
                const int I = IA + II * producto_interno(normalImpacto, luz);
#endif

                return I > II ? II : (I < 0 ? IA : I);
            }
        }
    }

#ifdef DEBUG
    MISSED_RAY
#endif

    return NEGRO;
}

void generarImagen(const float o[3], unsigned int _ANCHO, unsigned int _ALTO, unsigned int _FOV) {

    printf("P2\n%d %d\n%d\n", _ANCHO, _ALTO, II);

    const float z = _ANCHO / (2 * tan(DEG_TO_RAD(_FOV) / 2));

    for (int y = _ALTO / 2; y > -(int)_ALTO / 2; y--) {

        for (int x = -(int)_ANCHO / 2; x < (int)_ANCHO / 2; x++) {

            float rayo[3] = {x, y, z};
            normalizar(rayo);

#ifdef DEBUG
            computar_intensidad(CENTROS, RADIOS, OBJ_QTY, LUZ, o, rayo);
#else
            printf("%i ", computar_intensidad(CENTROS, RADIOS, OBJ_QTY, LUZ, o, rayo));
#endif
        }
        printf("\n");
    }
}

int main(void) {

    //(Default) Coordenas Observador: Origen
    //(Default) Resolucion: VGA (640 x 480)

    //En un futuro se podria escalar a imagenes de diferentes tamaños, FOV y posicion de origen mediante argumentos en la funcion main
    generarImagen(ORIGEN_OBSERVADOR, ANCHO, ALTO, FOV);

    return 0;
}

// Buenas noches a quién corresponda.

// Al igual que en el ejercicio anterior decidí documentarlo. Esta vez haciendo foco en las correcciones/recomendaciones recibidas en el EJ1.
// Adjunto un link a donde subí la documentación:
// https://ejercicio-obligatorio-2.netlify.app/
// ______________________________________________________________________________
// Correcciones recibidas EJ1:

// Sobre el .h:
// -Definiste PI como un literal double, por lo que deberías aprovechar la precisión que te provee, sin importar cómo lo vayas a usar después.

// -Incluí las bibliotecas que vayas a usar en este módulo. Por ejemplo, math.h no tiene nada que hacer en main.h, sí estaría bien incluirla en main.c, en donde efectivamente es utilizada.

// -OJO con las protecciones de archivos con doble guión bajo al inicio y al final. Es una convención de las bibliotecas estándar usar ese formato y podría llegar a pasar que alguna etiqueta ya esté definida. Si sabés lo que estás haciendo, está OK.
// En general tengo entendido que se usa algo tipo MAIN_H_ o EJ1_MAIN_H_ aclarando el nombre del proyecto.

// Sobre el .c:

// -La documentación de las funciones suele ir en el header, que es el archivo que le llega al usuario para que utilice las funciones, como nos llegan a nosotros las bibliotecas estándar (aunque los fuentes son de código abierto también).

// -Seguí así con los espacios entre operadores, después de las comas, etc. Lo que estaría bueno es que NO haya líneas en blanco innecesarias. De esas tu código está lleno.
// En particular: nunca van líneas en blanco en la 1er línea de una función, y solo deberían ir para separar bloques de código de distinta funcionalidad.

// - +1 por el uso de macro de función, pero ojo, ¿qué pasa si yo hago `DEG_TO_RAD(89 + 1)'?
// Revisá cómo sobrepasar ese problema.
// ______________________________________________________________________________

// De antemano agradezco cualquier comentario, mejoras y recomendaciones de buenas prácticas que me permitan mejorar la calidad del código.

// Nuevamente muchas gracias. Un saludo.