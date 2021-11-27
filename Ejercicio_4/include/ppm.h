/**
 * @file ppm.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef PPM_H
#define PPM_H

/* -------------------------------- Includes -------------------------------- */
#include <stdio.h>

#include "imagen.h"

/** @addtogroup Output
 *  @{
 */

/** @defgroup PPM PPM
 *  Generación de archivos PPM
 *  @{
 */

/* ------------------------------- Prototypes ------------------------------- */
/**
 * @brief   Guarda una imagen en un archivo PPM.
 * @pre     La imagen debe estar creada previamente.
 * @pre     El archivo debe estar abierto en modo escritura de texto.
 * @pre     El archivo debe ser de tipo PPM.
 * @param   *imagen: Puntero a la imagen de la cual se obtendrá la información para guardar.
 * @param   *f: Descriptor de archivo donde se almacenara la imagen en formato PPM.
 * @retval  None
 */
void escribir_PPM(const imagen_t *imagen, FILE *f);

/** @} */
/** @} */

#endif // PPM_H