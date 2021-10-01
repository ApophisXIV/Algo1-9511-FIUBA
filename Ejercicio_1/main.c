
/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-09-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "main.h"

/**
 * @brief  Calcula el producto interno de los vectores provistos a partir de sus componentes individuales
 * @param  x1: Componente X del primer vector provisto
 * @param  y1: Componente Y del primer vector provisto
 * @param  z1: Componente Z del primer vector provisto
 * @param  x2: Componente X del segundo vector provisto
 * @param  y2: Componente Y del segundo vector provisto
 * @param  z2: Componente Z del segundo vector provisto
 * @retval Producto interno de los vectores provistos
 */
float producto_interno(float x1, float y1, float z1, float x2, float y2, float z2) {

    return x1 * x2 + y1 * y2 + z1 * z2;
}


/**
 * @brief  Calcula la norma del vector provisto a partir de sus componentes
 * @param  x: Componente X del vector
 * @param  y: Componente Y del vector
 * @param  z: Componente Z del vector
 * @retval Norma del vector provisto
 */
float norma(float x, float y, float z) {

    return sqrt(producto_interno(x,y,z,x,y,z));
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
bool intersecta_esfera(float dx, float dy, float dz, float ox, float oy, float oz, float cx, float cy, float cz, float radius) {

#ifdef DEBUG

    float c_d_2 = pow(producto_interno(cx - ox, cy - oy, cz - oz, dx, dy, dz), 2);
    float c_2 = producto_interno(cx, cy, cz, cx, cy, cz);
    float r_2 = radius * radius;
    float res = c_d_2 - c_2 + r_2;

#ifdef DEBUG_L2

    printf("-----------------------------------------------------------------------------------\n");
    printf("dx: %03.3f dy: %03.3f dz: %03.3f \n", dx, dy, dz);
    printf("c_d_2: %03.3f c_2: %03.3f r_2: %03.3f res: %03.3f\n", c_d_2, c_2, r_2, res);
    printf("-----------------------------------------------------------------------------------\n");

#endif

    return res >= 0;

#else

    return pow(producto_interno(cx - ox, cy - oy, cz - oz, dx, dy, dz), 2) - producto_interno(cx, cy, cz, cx, cy, cz) + radius * radius >= 0;

#endif

}


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
void generarImagen(float ox, float oy, float oz, unsigned int _ANCHO, unsigned int _ALTO, unsigned int _FOV) {

    printf("P1\n%d %d\n", _ANCHO, _ALTO);

    float z = _ANCHO / (2 * tan(DEG_TO_RAD(_FOV) / 2));

    for (int y = _ALTO / 2; y > -(int)_ALTO / 2; y--) {

        for (int x = -(int)_ANCHO / 2; x < (int)_ANCHO / 2; x++) {

            float normaRayo = norma(x, y, z);

            printf("%u ", intersecta_esfera(x / normaRayo, y / normaRayo, z / normaRayo, ox, oy, oz, CX, CY, CZ, R));
        }

        printf("\n");
    }
}


int main(void) {

    //(Default) Coordenas Observador: Origen
    //(Default) Resolucion: VGA (640 x 480)

    //En un futuro se podria escalar a imagenes de diferentes tamaños, FOV y posicion de origen mediante argumentos en la funcion main
    generarImagen(0, 0, 0, ANCHO, ALTO, FOV);

    return 0;
}
