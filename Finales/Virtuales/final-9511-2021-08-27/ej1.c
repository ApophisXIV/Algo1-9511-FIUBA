#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// HACER: declarar el tipo sucursal_t

typedef struct {
	float lat, lon;
	uint8_t size_nombre;
	char *nombre_sucursal;
} sucursal_t;

/* -------------------------------------------------------------------------- */
// Invariante de representacion:
/* -------------------------------------------------------------------------- */
// - Si size_nombre == 0, entonces nombre_sucursal == NULL
// - Si size_nombre > 0, entonces nombre_sucursal != NULL
// - El tamaño del arreglo dinamico de char es el mismo que expresa "size_nombre"
// - Todos los punteros apuntan a memoria valida
/* -------------------------------------------------------------------------- */

void sucursal_destruir(sucursal_t *s) {
	free(s->nombre_sucursal);
	free(s);
}

bool leer_sucursales(const char *nombre_archivo, sucursal_t *sucursales[], size_t *cantidad) {

	FILE *f_r = fopen(nombre_archivo, "rb");
	if (f_r == NULL)
		return false;

	*cantidad = 0;

	while (true) {

		sucursal_t *s = malloc(sizeof(sucursal_t));
		if (s == NULL) {
			fclose(f_r);
			return false;
		}

		if (fread(&s->lat, sizeof(float), 1, f_r) != 1) {
			sucursal_destruir(s); // Va a destruir s, la cual todavia esta vacia
			break;
		}

		if (fread(&s->lon, sizeof(float), 1, f_r) != 1) {
			sucursal_destruir(s);
			break;
		}

		if (fread(&s->size_nombre, sizeof(uint8_t), 1, f_r) != 1) {
			sucursal_destruir(s);
			break;
		}

		s->nombre_sucursal = malloc(s->size_nombre);
		if (s->nombre_sucursal == NULL) {
			sucursal_destruir(s);
			break;
		}

		if (fread(s->nombre_sucursal, sizeof(char), s->size_nombre, f_r) != s->size_nombre) {
			sucursal_destruir(s);
			break;
		}

		sucursales[(*cantidad)++] = s;
	}

	fclose(f_r);

	return true;
}

int main(void) {
	sucursal_t *sucursales[10];
	size_t n;

	bool ok = leer_sucursales("sucursales.bin", sucursales, &n);
	assert(ok);
	assert(n == 3);

	// OPCIONAL: verificar con assert los datos de las sucursales.
	// Deberían ser:
	// - lat: -34.0  long: -58.0  nombre: "Sucursal A"
	// - lat: -35.0  long: -56.0  nombre: "Sucursal B"
	// - lat: -33.0  long: -57.0  nombre: "Sucursal C"

	assert(sucursales[0]->lat == -34.0);
	assert(sucursales[0]->lon == -58.0);
	assert(strcmp(sucursales[0]->nombre_sucursal, "Sucursal A") == 0);

	assert(sucursales[1]->lat == -35.0);
	assert(sucursales[1]->lon == -56.0);
	assert(strcmp(sucursales[1]->nombre_sucursal, "Sucursal B") == 0);

	assert(sucursales[2]->lat == -33.0);
	assert(sucursales[2]->lon == -57.0);
	assert(strcmp(sucursales[2]->nombre_sucursal, "Sucursal C") == 0);

	for (int i = 0; i < n; i++) {
		sucursal_destruir(sucursales[i]);
	}

	printf("%s: OK\n", __FILE__);
	return 0;
}


//44 min