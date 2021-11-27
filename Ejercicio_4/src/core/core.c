/**
 * @file core.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <math.h>

#include "../../include/core.h"

#define PI 3.1415927f
#define FOV 90

bool fill_img_w_shape(imagen_t *img, size_t ancho, size_t alto, color_t (*figura)(color_t, vector_t, vector_t)) {

	const color_t ambiente = {.05, .05, .05};
	const vector_t origen = {0, 0, 0};

	const float z = ancho / 2 / tan(FOV / 2 * PI / 180);

	const int y_max = alto / 2;
	const int x_max = ancho / 2;

	for (int y = y_max; y > -y_max; y--)
		for (int x = -x_max; x < x_max; x++) {

			const color_t c = figura(ambiente, origen, vector_normalizar((vector_t){x, y, z}));

			if (!imagen_set_pixel(img, x + x_max, y + y_max - 1, c))
				return false;
		}

	return true;
}