
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
    float _c[3] = {0};

    resta(_c, c, o);

    const float cd = producto_interno(_c, d);
    const float delta = pow(cd, 2) - producto_interno(_c, _c) + r * r;

    if (delta >= 0) {
        const float rootDelta = sqrt(delta);
        const float t = cd - rootDelta > 0 ? cd - rootDelta : cd + rootDelta;

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

        float t = distancia_esfera(cs[i], rs[i], o, d);

        if (t != INFINITO) {

            interpolar_recta(puntoImpacto, o, d, t);
            normal_esfera(normalImpacto, cs[i], rs[i], puntoImpacto);

            for (size_t j = 0; j < n_esferas; j++) {

                int I = IA + II * producto_interno(normalImpacto, luz);
#ifdef DEBUG
                DEBUG_TABLE
#endif
                if ((i != j) && ((distancia_esfera(cs[j], rs[j], puntoImpacto, luz) != INFINITO) || (I < 0))) return IA;

                return I > II ? II : I;
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

    float z = _ANCHO / (2 * tan(DEG_TO_RAD(_FOV) / 2));

    for (int y = _ALTO / 2; y > -(int)_ALTO / 2; y--) {

        for (int x = -(int)_ANCHO / 2; x < (int)_ANCHO / 2; x++) {

            float rayo[3] = {x, y, z};
            normalizar(rayo);

#ifdef DEBUG
            computar_intensidad(centros, radios, OBJ_QTY, luz, o, rayo);
#else
            printf("%i ", computar_intensidad(centros, radios, OBJ_QTY, luz, o, rayo));
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