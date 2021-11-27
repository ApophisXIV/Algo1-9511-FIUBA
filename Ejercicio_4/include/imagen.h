/**
 * @file imagen.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef IMAGEN_H
#define IMAGEN_H

/* -------------------------------- Includes -------------------------------- */
#include <stdbool.h>
#include <stddef.h>

#include "color.h"

/* ----------------------------- Data structures ---------------------------- */
struct imagen;
typedef struct imagen imagen_t;

/** @addtogroup Core
 *  @{
 */

/** @defgroup Canvas Canvas
 *  Lista de funciones primitivas de imagen
 *  @{
 */

/* ------------------------------- Prototypes ------------------------------- */
/**
 * @brief   Crea una imagen vacía.
 * @pre     El ancho y el alto de la imagen deben ser mayores a cero.
 * @param   ancho: Ancho de la imagen.
 * @param   alto: Alto de la imagen.
 * @retval  imagen_t*: Puntero a la imagen creada.
 */
imagen_t*   imagen_crear(size_t ancho, size_t alto);

/**
 * @brief   Libera la memoria de una imagen.
 * @pre     La imagen debe haber sido creada previamente.
 * @param   *im: Puntero a la imagen a liberar.
 * @retval  None
 */
void        imagen_destruir(imagen_t *im);

/**
 * @brief   Rellena una imagen con la forma que genera una funcion recibida por parametro.
 * @pre     La imagen debe haber sido creada previamente.
 * @param   *im: Puntero a la imagen.
 * @param   *ancho: Puntero a la variable que almacenara el ancho de la imagen.
 * @param   *alto: Puntero a la variable que almacenara el alto de la imagen.
 * @retval  None
 */
void        imagen_dimensiones(const imagen_t *im, size_t *ancho, size_t *alto);

/**
 * @brief   Setea un pixel de la imagen.
 * @pre     La imagen debe haber sido creada previamente.
 * @pre     El valor de x e y deben ser mayores o iguales a cero y menores a la dimension de la imagen.
 * @param   *im: Puntero a la imagen.
 * @param   x: Coordenada x del pixel a setear.
 * @param   y: Coordenada y del pixel a setear.
 * @param   color: Color que se le asignara al pixel.
 * @retval  bool: True si el pixel fue seteado correctamente, false en caso contrario.
 */
bool        imagen_set_pixel(imagen_t *im, size_t x, size_t y, color_t color);

/**
 * @brief   Obtiene el color de un pixel de la imagen.
 * @pre     La imagen debe haber sido creada previamente.
 * @pre     El valor de x e y deben ser mayores a cero y menores a la dimension de la imagen.
 * @param   *im: Puntero a la imagen.
 * @param   x: Coordenada x del pixel a obtener.
 * @param   y: Coordenada y del pixel a obtener.
 * @retval  color_t: Color del pixel.
 */
color_t     imagen_get_pixel(const imagen_t *im, size_t x, size_t y);

/** @} */
/** @} */

#endif
