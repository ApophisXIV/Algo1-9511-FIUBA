
/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-09-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "main.h"

/* ---------------------------------- Utils --------------------------------- */

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

/* -------------------------------------------------------------------------- */

float distancia_esfera(const float c[3], float r, const float o[3], const float d[3]) {
}

void normal_esfera(float normal[3], const float c[3], float r, const float p[3]) {
}

int computar_intensidad(const float cs[][3], const float rs[], size_t n_esferas, const float luz[3], const float o[3], const float d[3]) {

    // IA + II
}

void interpolar_recta(float p[3], const float o[3], const float d[3], float t) {

    // P = O + t · d

    // p[0] = o[0] + producto_interno(,d)
}

/**
 * @brief  Detector de colision entre un rayo y una esfera de radio R
 * @note   Esta funcion se encarga de detectar si un rayo intersecta o no con la esfera dada
 *         a patir del discriminante de la ecuacion resolvente aplicada a la siguiente ecuacion.
 *         (C · d)^2 - C · C + R^2 >= 0
 * @param  dx: Componente X del rayo
 * @param  dy: Componente Y del rayo
 * @param  dz: Componente Z del rayo
 * @param  ox: Coordenada X de la posicion del observador
 * @param  oy: Coordenada Y de la posicion del observador
 * @param  oz: Coordenada Z de la posicion del observador
 * @param  cx: Coordenada X de la posicion de la esfera
 * @param  cy: Coordenada Y de la posicion de la esfera
 * @param  cz: Coordenada Z de la posicion de la esfera
 * @param  radius: Radio de la esfera
 * @retval 0:  No hubo colision
 * @retval 1:  Hubo colision
 */
bool intersecta_esfera(const float d[3], const float c[3], const float o[3], const float r) {

    // return pow(producto_interno(cx - ox, cy - oy, cz - oz, dx, dy, dz), 2) - producto_interno(cx, cy, cz, cx, cy, cz) + radius * radius >= 0;
}

#include <stdlib.h>
#include <time.h>

/**
 * @brief  Generador de imagen primitiva
 * @note   Esta funcion se encarga del proceso de generacion de una escena de ancho y alto definido
 * @param  ox: Coordenada X de la posicion del observador
 * @param  oy: Coordenada Y de la posicion del observador
 * @param  oz: Coordenada Z de la posicion del observador
 * @param  _ANCHO: Ancho de la imagen a generar
 * @param  _ALTO: Alto de la imagen a generar
 * @retval None
 */
void generarImagen(const float o[3], unsigned int _ANCHO, unsigned int _ALTO, unsigned int _FOV) {

    printf("P2\n%d %d\n%d\n", _ANCHO, _ALTO, II);

    float z = _ANCHO / (2 * tan(DEG_TO_RAD(_FOV) / 2));

    for (int y = _ALTO / 2; y > -(int)_ALTO / 2; y--) {

        for (int x = -(int)_ANCHO / 2; x < (int)_ANCHO / 2; x++) {

            float ray[3] = {(float)x, (float)y, z};

            normalizar(ray);

            /* ------------------------------ Distance calc ----------------------------- */
            
            //Por cada rayo voy a calcular la distancia de este a cada esfera
            for (size_t i = 0; i < ROWS_QTY; i++) {

                

            }

            float rayDistance = distancia_esfera();

            /* ------------------------------ Interpolation ----------------------------- */

            float intersectionPoint[3] = {0};

            interpolar_recta(intersectionPoint, o, ray, rayDistance);

            //!Test random
            // printf("%d ",rand()%255);
        }

        printf("\n");
    }
}

int main(void) {

    //(Default) Coordenas Observador: Origen
    //(Default) Resolucion: VGA (640 x 480)

    //!Test random
    // time_t t;
    // srand(time(&t));

    const float OBSERVADOR[3] = {0};

    //En un futuro se podria escalar a imagenes de diferentes tamaños, FOV y posicion de origen mediante argumentos en la funcion main
    generarImagen(OBSERVADOR, ANCHO, ALTO, FOV);

    return 0;
}
