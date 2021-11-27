/**
 * @file parser.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef PARSER_H
#define PARSER_H

/* -------------------------------- Includes -------------------------------- */
#include <stdbool.h>
#include <stdint.h>

/* ---------------------------------- Enums --------------------------------- */
enum FILE_TYPE {
    FT_BMP,
    FT_PPM
};

/* ------------------------------- Prototypes ------------------------------- */
/**
 * @brief   Verifica si la entrada de datos es valida.
 * @param   argc: Cantidad de argumentos pasados por linea de comandos.
 * @param   *argv[]: Puntero a un arreglo de punteros a cadenas de caracteres pasados por linea de comandos.
 * @param   *ancho: Puntero a un entero donde se almacenara el ancho de la imagen.
 * @param   *alto: Puntero a un entero donde se almacenara el alto de la imagen.
 * @param   *extension: Puntero a un entero donde se almacenara el tipo de archivo.
 * @retval  bool: True si la entrada es valida, false en caso contrario.
 */
bool is_a_valid_input(int argc, char *argv[], int *ancho, int *alto, int *extension);

#endif // PARSER_H