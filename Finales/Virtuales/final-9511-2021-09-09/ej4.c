#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimir_matriz(size_t m, size_t n, int matriz[m][n]) {

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			printf("%d ", matriz[i][j]);
		printf("\n");
	}
}

void rellenar(size_t m, size_t n, int matriz[m][n], int i, int j, int color) {

	if (i < 0 || j < 0 || i >= m || j >= n)    // Si esta fuera de la matriz
		return;

	if (matriz[i][j] == color)    // Si ya esta pintado el casillero actual
		return;

	static int color_inicial = 0;        // Color inicial
	if (!color_inicial)                  // Si es el primer color
		color_inicial = matriz[i][j];    // Guardamos el color inicial para poder compararlo con el resto de casilleros

	matriz[i][j] = color;    // Pintamos el casillero actual

	if (matriz[i - 1][j] == color_inicial)          // Si el color inicial ya esta en el vecino de arriba
		rellenar(m, n, matriz, i - 1, j, color);    // Pintamos el vecino de arriba
	if (matriz[i + 1][j] == color_inicial)          // Si el color inicial ya esta en el vecino de abajo
		rellenar(m, n, matriz, i + 1, j, color);    // Pintamos el vecino de abajo
	if (matriz[i][j - 1] == color_inicial)          // Si el color inicial ya esta en el vecino de la izquierda
		rellenar(m, n, matriz, i, j - 1, color);    // Pintamos el vecino de la izquierda
	if (matriz[i][j + 1] == color_inicial)          // Si el color inicial ya esta en el vecino de la derecha
		rellenar(m, n, matriz, i, j + 1, color);    // Pintamos el vecino de la derecha
}

/* -------------------------------------------------------------------------- */
/*                          RGB Version (In progress)                         */
/* -------------------------------------------------------------------------- */

/*

void imprimir_matriz_rgb(size_t m, size_t n, int matriz[m][n][3]) {

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			printf("%d %d %d \n", matriz[i][j][0], matriz[i][j][1], matriz[i][j][2]);
}

bool is_same_color(int a[3], int b[3]) {
	return a[0] == b[0] && a[1] == b[1] && a[2] == b[2];
}

void apply_color(int a[3], int b[3]) {
	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];
}

void rellenar_rgb(size_t m, size_t n, int matriz[m][n][3], int i, int j, int color[3]) {

	if (i < 0 || j < 0 || i >= m || j >= n)    // Si esta fuera de la matriz
		return;

	if (matriz[i][j] == color)    // Si ya esta pintado el casillero actual
		return;

	static int color_inicial[3] = {0, 0, 0};                // Color inicial
	if (is_same_color(color_inicial, (int[3]){0, 0, 0}))    // Si es el primer color
		apply_color(color_inicial, color);                  // Guardamos el color inicial para poder compararlo con el resto de casilleros

	apply_color(matriz[i][j], color);    // Pintamos el casillero actual

	if (is_same_color(matriz[i - 1][j], color_inicial))    // Si el color inicial ya esta en el vecino de arriba
		rellenar_rgb(m, n, matriz, i - 1, j, color);       // Pintamos el vecino de arriba
	if (is_same_color(matriz[i + 1][j], color_inicial))    // Si el color inicial ya esta en el vecino de abajo
		rellenar_rgb(m, n, matriz, i + 1, j, color);       // Pintamos el vecino de abajo
	if (is_same_color(matriz[i][j - 1], color_inicial))    // Si el color inicial ya esta en el vecino de la izquierda
		rellenar_rgb(m, n, matriz, i, j - 1, color);       // Pintamos el vecino de la izquierda
	if (is_same_color(matriz[i][j + 1], color_inicial))    // Si el color inicial ya esta en el vecino de la derecha
		rellenar_rgb(m, n, matriz, i, j + 1, color);       // Pintamos el vecino de la derecha
}

void rgb_Test() {

	int matriz_rgb[7][6][3] = {

		{{0xff, 0xff, 0x00}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}},
		{{0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x16, 0x66}},
		{{0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x16}, {0x3F, 0x16, 0x66}},
		{{0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x16, 0x66}, {0x3F, 0x16, 0x66}, {0x3F, 0x66, 0x66}},
		{{0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x16, 0x66}, {0x3F, 0x16, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}},
		{{0x3F, 0x16, 0x66}, {0x3F, 0x16, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}},
		{{0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}, {0x3F, 0x66, 0x66}},

	};

	// pintamos con el color ROJO a partir de la celda en fila 2, columna 1
	rellenar_rgb(7, 6, matriz_rgb, 2, 1, (int[3]){0xFF, 0x00, 0x00});

	printf("P3\n");
	printf("%d %d\n", 7, 6);
	printf("255\n");
	imprimir_matriz_rgb(7, 6, matriz_rgb);
	printf("\n");
}

*/

/* -------------------------------------------------------------------------- */

int main(void) {

	int matriz[7][6] = {
		{0, 0, 2, 0, 0},
		{0, 1, 1, 3, 0},
		{1, 1, 1, 4, 0},
		{1, 1, 1, 1, 5},
		{0, 5, 1, 5, 5},
		{1, 1, 5, 5, 0},
		{1, 1, 1, 0, 0},
	};

	imprimir_matriz(7, 6, matriz);
	printf("\n");

	// pintamos con el color 5 a partir de la celda en fila 2, columna 1
	rellenar(7, 6, matriz, 2, 1, 5);

	int resultado[7][6] = {
		{0, 0, 2, 0, 0},
		{0, 5, 5, 3, 0},
		{5, 5, 5, 4, 0},
		{5, 5, 5, 5, 5},
		{0, 5, 5, 5, 5},
		{1, 1, 5, 5, 0},
		{1, 1, 1, 0, 0},
	};

	imprimir_matriz(7, 6, matriz);
	printf("\n");

	assert(memcmp(matriz, resultado, sizeof(matriz)) == 0);

	// OPCIONAL: Pruebas adicionales

	// rgb_Test();

	printf("%s: OK\n", __FILE__);
	return 0;
}
