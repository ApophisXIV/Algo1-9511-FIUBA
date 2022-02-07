#include "img.h"
#include "tipografia8x8.h"

#include <stdlib.h>
#include <string.h>

struct img {
	size_t ancho, alto;
	rgba_t **pixels;
};

// ---- Ejercicio 1 (41 min) ----

img_t *img_crear(const size_t ancho, const size_t alto) {
	if (ancho < 0 || alto < 0)
		return NULL;

	img_t *img = malloc(sizeof(img_t));
	if (img == NULL)
		return NULL;

	img->pixels = malloc(sizeof(rgba_t *) * alto);
	if (img->pixels == NULL) {
		free(img);
		return NULL;
	}

	for (size_t i = 0; i < alto; i++) {
		img->pixels[i] = malloc(sizeof(rgba_t) * ancho);
		if (img->pixels[i] == NULL) {
			img_destruir(img);
			return NULL;
		}
	}

	img->ancho = ancho;
	img->alto = alto;

	return img;
}

void img_destruir(img_t *img) {
	if (img == NULL)
		return;
	for (size_t i = 0; i < img->alto; i++)
		free(img->pixels[i]);
	free(img->pixels);
	free(img);
}

size_t img_ancho(const img_t *img) {
	return img->ancho;
}

size_t img_alto(const img_t *img) {
	return img->alto;
}

void img_set_pixel(img_t *img, const size_t x, const size_t y, const rgba_t color) {
	if (img == NULL || x < 0 || y < 0 || x >= img->ancho || y >= img->alto)
		return;
	img->pixels[y][x] = color;
}

rgba_t img_get_pixel(img_t *img, const size_t x, const size_t y) {
	if (img == NULL || x < 0 || y < 0 || x >= img->ancho || y >= img->alto)
		return 0;
	return img->pixels[y][x];
}

img_t *img_clonar(const img_t *img) {
	if (img == NULL)
		return NULL;

	img_t *img_clon = img_crear(img->ancho, img->alto);
	if (img_clon == NULL)
		return NULL;

	for (size_t i = 0; i < img->alto; i++)
		for (size_t j = 0; j < img->ancho; j++)
			img_set_pixel(img_clon, j, i, img->pixels[i][j]);
	return img_clon;
}

// ---- Ejercicio 2 (8 min) ----

bool img_escribir(const img_t *img, FILE *f) {
	if (f == NULL || img == NULL)
		return false;

	if (fwrite(&img->ancho, sizeof(img->ancho), 1, f) != 1)
		return false;
	if (fwrite(&img->alto, sizeof(img->alto), 1, f) != 1)
		return false;
	for (size_t i = 0; i < img->alto; i++)
		for (size_t j = 0; j < img->ancho; j++)
			if (fwrite(&img->pixels[i][j], sizeof(rgba_t), 1, f) != 1)
				return false;
	return true;
}

img_t *img_leer(FILE *f) {
	if (f == NULL)
		return NULL;

	size_t ancho, alto;
	if (fread(&ancho, sizeof(ancho), 1, f) != 1)
		return NULL;
	if (fread(&alto, sizeof(alto), 1, f) != 1)
		return NULL;

	img_t *img_leida = img_crear(ancho, alto);
	if (img_leida == NULL)
		return NULL;

	for (size_t i = 0; i < alto; i++)
		for (size_t j = 0; j < ancho; j++)
			if (fread(&img_leida->pixels[i][j], sizeof(rgba_t), 1, f) != 1) {
				img_destruir(img_leida);
				return NULL;
			}

	return img_leida;
}

// ---- Ejercicio 3 (6 min) ----

int comparar_tamangno(const void *a, const void *b) {
	// Tamagno = ancho * alto
	// Casteo del puntero generico "a" a un puntero que apunta a un arreglo de punteros de tipo "img_t *".
	// Casteo del puntero generico "b" a un puntero que apunta a un arreglo de punteros de tipo "img_t *".
	int tam_a = ((img_t **)a)[0] == NULL ? 0 : ((img_t **)a)[0]->ancho * ((img_t **)a)[0]->alto;
	int tam_b = ((img_t **)b)[0] == NULL ? 0 : ((img_t **)b)[0]->ancho * ((img_t **)b)[0]->alto;
	return tam_a - tam_b;
}

void img_ordenar_por_tamagno(img_t *img[], const size_t n) {
	qsort(img, n, sizeof(img_t *), comparar_tamangno);
}

// ---- Ejercicio 4 (46 min) ----

bool img_pintar(img_t *img, const rgba_t color) {
	if (img == NULL)
		return false;
	for (size_t i = 0; i < img->alto; i++)
		for (size_t j = 0; j < img->ancho; j++)
			img_set_pixel(img, j, i, color);
	return true;
}

void print_img(img_t *img) {
	if (img == NULL)
		return;
	for (size_t i = 0; i < img->alto; i++) {
		for (size_t j = 0; j < img->ancho; j++) {
			fprintf(stderr, "{%02x %02x %02x %02x} ", rgba_r(img->pixels[i][j]), rgba_g(img->pixels[i][j]), rgba_b(img->pixels[i][j]), rgba_a(img->pixels[i][j]));
		}
		fprintf(stderr, "\n");
	}
}

bool img_sellar(img_t *img_papel, const img_t *img_sello, const int x, const int y) {
	if (img_papel == NULL || img_sello == NULL)
		return false;

	for (size_t i = 0; i < img_sello->alto; i++)
		for (size_t j = 0; j < img_sello->ancho; j++)
			if (x + j >= 0 && y + i >= 0 && x + j < img_papel->ancho && y + i < img_papel->alto && rgba_a(img_sello->pixels[i][j]) != 0)
				img_set_pixel(img_papel, x + j, y + i, img_sello->pixels[i][j]);
	return true;
}

// ---- Ejercicio 5 (23 min) ----

static void img_sellar_caracter(img_t *img, const size_t x, const size_t y, const char c, const rgba_t c_fondo, const rgba_t c_letra) {

	for (size_t i = 0; i < 8; i++) {
		for (size_t j = 0; j < 8; j++) {
			if ((tipografia8x8[(uint8_t)c][i] >> j) & 1) {
				// Color texto
                img_set_pixel(img, x + j, y + i, c_letra);
			} else {
				// Color fondo
                img_set_pixel(img, x + j, y + i, c_fondo);
			}
		}
	}
}

img_t *img_crear_texto(const char *s, const rgba_t c_fondo, const rgba_t c_texto) {
	if (s == NULL)
		return NULL;

	const size_t n_chars = strlen(s);

	img_t *img = img_crear(n_chars * 8, 8);
	if (img == NULL)
		return NULL;

	for (size_t k = 0; k < n_chars; k++)
        img_sellar_caracter(img, k * 8, 0, s[k], c_fondo, c_texto);

	return img;
}