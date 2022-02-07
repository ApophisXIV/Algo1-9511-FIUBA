#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include <stdlib.h>

typedef struct {
	uint8_t dia;
	uint8_t mes;
	uint16_t anno;

	uint32_t dni;

	bool es_positivo;
} resultado_t;

int fecha_comparar(resultado_t *r1, resultado_t *r2) {
    if (r1->anno < r2->anno) return -1;
    if (r1->anno > r2->anno) return 1;

    if (r1->mes < r2->mes) return -1;
    if (r1->mes > r2->mes) return 1;

    if (r1->dia < r2->dia) return -1;
    if (r1->dia > r2->dia) return 1;

    return 0;
}

int comparar_resultados(const void *a, const void *b) {
    resultado_t *res_a = (resultado_t *)a;
    resultado_t *res_b = (resultado_t *)b;
    if (fecha_comparar(res_a, res_b) == 0)
        return res_a->dni - res_b->dni; //Si es de la misma fecha ordena por DNI
    return fecha_comparar(res_a, res_b); //Si es de distinta fecha ordena por fecha
}

void ordenar_resultados(resultado_t resultados[], size_t n) {
	if (n <= 1)
		return;
	qsort(resultados, n, sizeof(resultado_t), comparar_resultados);
}

int main(int argc, const char *argv[]) {
	resultado_t resultados[] = {
		{04, 01, 2022, 25879462, true},
		{01, 01, 2022, 25879462, false},
		{01, 01, 2022, 1234567, true},
		{15, 12, 2021, 98765432, true},
	};
	ordenar_resultados(resultados, 4);

	resultado_t ordenado[] = {
		{15, 12, 2021, 98765432, true},
		{01, 01, 2022, 1234567, true},
		{01, 01, 2022, 25879462, false},
		{04, 01, 2022, 25879462, true},
	};

#define EQ(x) assert(resultados[i].x == ordenado[i].x)
	for (int i = 0; i < 4; i++) {
		EQ(dia);
		EQ(mes);
		EQ(anno);
		EQ(dni);
		EQ(es_positivo);
	}

	// OPCIONAL: escribir pruebas adicionales

	printf("%s: OK\n", __FILE__);
	return 0;
}
