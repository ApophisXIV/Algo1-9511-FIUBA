/**
 * @file core.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef CORE_H
#define CORE_H

/* -------------------------------- Includes -------------------------------- */
#include <stdint.h>
#include <stdbool.h>

#include "imagen.h"
#include "mandelbrot.h"

/* --------------------------------- Macros --------------------------------- */
#define MANDELBROT &mandelbrot


/** @defgroup Core Core
 *  @{
 */

/* ------------------------------- Prototypes ------------------------------- */
/**
 * @brief  Rellena una imagen con la forma que genera una funcion recibida por parametro.
 * @pre    La imagen debe haber sido creada previamente.
 * @pre    La funcion recibida por parametro debe ser coincidente con la forma color_t (f)(ambiente, origen, rayo versor).
 * @param  *img: Puntero a la imagen a rellenar.
 * @param  color_t(*figura)(color_t, vector_t, vector_t): Puntero a la funcion que genera la forma.
 * @retval bool: True si la imagen fue rellenada correctamente, false en caso contrario.
 */
bool fill_img_w_shape(imagen_t *img, size_t ancho, size_t alto, color_t (*figura)(color_t, vector_t, vector_t));

/** @} */

/** @addtogroup Core
 *  @{
 */
/** @defgroup Shapes Shapes */
/** @defgroup Canvas Canvas */
/** @defgroup Output Output */
/** @} */



#endif    // CORE_H