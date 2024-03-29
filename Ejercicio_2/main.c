
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
    const float delta = cd * cd - producto_interno(co, co) + r * r;

    //Decidi priorizar legibilidad sobre performance al hacer uso de sqrt(delta) 2 veces
    
    if ((delta >= 0) && (cd + sqrt(delta) > 0)) { //Corto circuito. Priorizo delta >= 0.
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

    //Una vez mas decidi priorizar legibilidad sobre performance haciendo uso de un par de variables extra
    float tUltimoImpacto = INFINITO;
    size_t n_esferaMinZ = -1;

    for (size_t i = 0; i < n_esferas; i++) {

        const float t = distancia_esfera(cs[i], rs[i], o, d);

        if (t != INFINITO && t < tUltimoImpacto) {
            tUltimoImpacto = t;
            n_esferaMinZ = i;
        }
    }

    if (tUltimoImpacto != INFINITO) {

        float normalImpacto[3] = {0};
        float puntoImpacto[3] = {0};

        interpolar_recta(puntoImpacto, o, d, tUltimoImpacto);
        normal_esfera(normalImpacto, cs[n_esferaMinZ], rs[n_esferaMinZ], puntoImpacto);

        for (size_t j = 0; j < n_esferas; j++) {

            if ((n_esferaMinZ != j) && ((distancia_esfera(cs[j], rs[j], puntoImpacto, luz) != INFINITO))) return IA;
        }   

        const int I = IA + II * producto_interno(normalImpacto, luz);
        return I > II ? II : (I <= IA ? IA : I);
    }

    return NEGRO;
}

void generarImagen(const float o[3], unsigned int _ANCHO, unsigned int _ALTO, unsigned int _FOV, const float _LUZ[3]) {

    printf("P2\n%d %d\n%d\n", _ANCHO, _ALTO, II);

    const float z = _ANCHO / (2 * tan(DEG_TO_RAD(_FOV) / 2));

    for (int y = _ALTO / 2; y > -(int)_ALTO / 2; y--) {

        for (int x = -(int)_ANCHO / 2; x < (int)_ANCHO / 2; x++) {

            float rayo[3] = {x, y, z};
            normalizar(rayo);

            printf("%i ", computar_intensidad(CENTROS, RADIOS, OBJ_QTY, _LUZ, o, rayo));
        }
        printf("\n");
    }
}

int main(void) {

    //(Default) Coordenas Observador: Origen
    //(Default) Resolucion: VGA (640 x 480)

    //En un futuro se podria escalar a imagenes de diferentes tamaños, FOV y posicion de origen mediante argumentos en la funcion main
    generarImagen(ORIGEN_OBSERVADOR, ANCHO, ALTO, FOV,LUZ);

    return 0;
}