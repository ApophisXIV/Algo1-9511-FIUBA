/**
 * @file bmp.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef BMP_H
#define BMP_H

/* -------------------------------- Includes -------------------------------- */
#include <stdio.h>
#include "imagen.h"

/** @addtogroup Output
 *  @{
 */

/** @defgroup BMP BMP
 *  Generación de archivos BMP
 *  @{
 */

/* ------------------------------- Prototypes ------------------------------- */
/**
 * @brief  Crea un archivo de extension bmp y almacena la imagen en el mismo.
 * @pre    La imagen debe estar creada previamente.
 * @pre    El archivo debe estar abierto en modo escritura binaria.
 * @pre    El archivo debe ser de tipo BMP.
 * @param  *imagen: Puntero a la imagen a almacenar.
 * @param  *f: Descriptor de archivo donde se almacenara la imagen en formato BMP.
 * @retval None
 */
void escribir_BMP(const imagen_t *imagen, FILE *f);

/** @} */
/** @} */

#endif    // BMP_H