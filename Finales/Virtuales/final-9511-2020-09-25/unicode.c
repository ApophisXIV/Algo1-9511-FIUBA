#include "unicode.h"
#include <stdio.h>

// ---- Ejerciocio 1 (10 min) ----

size_t unicode_longitud(const uchar_t *s) {
	if (s == NULL || *s == '\0')
		return 0;
	size_t n = 0;
	while (*s != '\0') {
		s++;
		n++;
	}
	return n;
}

int unicode_comparar(const uchar_t *s1, const uchar_t *s2) {
	if (s1 == NULL || s2 == NULL)
		return -1;

	while (*s1 != '\0' && *s2 != '\0') {
		if (*s1 < *s2)
			return *s1 - *s2;
		if (*s1 > *s2)
			return *s1 - *s2;
		s1++;
		s2++;
	}

	return *s1 - *s2;
}

// ---- Ejercicio 2 (37 min) ----

void unicode_concatenar(uchar_t *dst, const uchar_t *src) {
	if (dst == NULL || src == NULL)
		return;
	while (*dst != '\0')
		dst++;	  // Muevo el puntero al final
	while (*src != '\0')
		*dst++ = *src++;
	*dst = '\0';
}

void unicode_insertar(uchar_t *dst, int desde, const uchar_t *src) {
	if (dst == NULL || src == NULL)
		return;

	dst += desde;
	const size_t len_src = unicode_longitud(src);
	const size_t len_dst_aux = unicode_longitud(dst);

	for (size_t i = 0; i < len_dst_aux; i++)
		*(dst + len_src + i) = *dst;

	while (*src != '\0') {
		*dst = *src;
		src++;
		dst++;
	}

	*(dst + 1) = '\0';
}

// ---- Ejercicio 3 (35 min) ----

#define MASK_1b 0x01
#define MASK_3b 0x07
#define MASK_4b 0x0F
#define MASK_5b 0x1F
#define MASK_6b 0x3F
#define MASK_7b 0x7F

#define CODE_POINT_1B 0x00
#define CODE_POINT_2B 0xC0
#define CODE_POINT_3B 0xE0
#define CODE_POINT_4B 0xF0
#define CODE_POINT_ENCODING 0x80

// D - Decode
#define D_ES_CODE_POINT_1B(x) (!((x & (MASK_1b << 7)) ^ CODE_POINT_1B))
#define D_ES_CODE_POINT_2B(x) (!((x & (MASK_3b << 5)) ^ CODE_POINT_2B))
#define D_ES_CODE_POINT_3B(x) (!((x & (MASK_4b << 4)) ^ CODE_POINT_3B))
#define D_ES_CODE_POINT_4B(x) (!((x & (MASK_5b << 3)) ^ CODE_POINT_4B))

// E - Encode
#define E_ES_CODE_POINT_1B(x) (x <= 0x7F)
#define E_ES_CODE_POINT_2B(x) (x >= 0x80 && x <= 0x7FF)
#define E_ES_CODE_POINT_3B(x) (x >= 0x800 && x <= 0xFFFF)
#define E_ES_CODE_POINT_4B(x) (x >= 0x10000)

void unicode_decodificar_utf8(uchar_t *dst, const uint8_t *src) {

	if (dst == NULL || src == NULL)
		return;

	while (*src != '\0') {

		*dst = 0;

		if (D_ES_CODE_POINT_1B(*src)) {
			*dst = *src;
			src++;
			dst++;
		} else if (D_ES_CODE_POINT_2B(*src)) {
			*dst = ((*src & MASK_5b) << 6) | (*(src + 1) & MASK_6b);
			src += 2;
			dst++;
		} else if (D_ES_CODE_POINT_3B(*src)) {
			*dst = ((*src & MASK_4b) << 12) | ((*(src + 1) & MASK_6b) << 6) | (*(src + 2) & MASK_6b);
			src += 3;
			dst++;
		} else if (D_ES_CODE_POINT_4B(*src)) {
			*dst = ((*src & MASK_3b) << 18) | ((*(src + 1) & MASK_6b) << 12) | ((*(src + 2) & MASK_6b) << 6) | (*(src + 3) & MASK_6b);
			src += 4;
			dst++;
		} else {
			*dst = '\0';
			return;
		}
	}
}

// ---- Ejercicio 4 (20 min) ----

void unicode_codificar_utf8(const uchar_t *src, uint8_t *dst) {
	if (src == NULL || dst == NULL)
		return;

	for (size_t i = 0, j = 0; src[i] != 0; i++) {

		dst[j] = 0;

		if (E_ES_CODE_POINT_1B(src[i])) {
			dst[j++] = src[i];
		} else if (E_ES_CODE_POINT_2B(src[i])) {
			dst[j++] = CODE_POINT_2B | (src[i] >> 6);
			dst[j++] |= (src[i] & MASK_6b) | CODE_POINT_ENCODING;
		} else if (E_ES_CODE_POINT_3B(src[i])) {
			dst[j++] |= CODE_POINT_3B | (src[i] >> 12);
			dst[j++] |= ((src[i] >> 6) & MASK_6b) | CODE_POINT_ENCODING;
			dst[j++] |= (src[i] & MASK_6b) | CODE_POINT_ENCODING;
		} else if (E_ES_CODE_POINT_4B(src[i])) {
			dst[j++] |= CODE_POINT_4B | (src[i] >> 18);
			dst[j++] |= ((src[i] >> 12) & MASK_6b) | CODE_POINT_ENCODING;
			dst[j++] |= ((src[i] >> 6) & MASK_6b) | CODE_POINT_ENCODING;
			dst[j++] |= (src[i] & MASK_6b) | CODE_POINT_ENCODING;
		} else {
			dst[j++] = '\0';
			return;
		}
	}
}

// ---- Ejercicio 5 (52 min) ----

/*NOTE: Plan de accion
 * - Macros para medir un caracter UTF-8 en Unicode y viceversa
 * - Leer el archivo completo (Truco: Mover ida y vuelta el file pointer y usar fteel)
 * - Reservar memoria para un buffer de dimension n_bytes + 1
 * - Leer el archivo completo y guardarlo en el buffer (Todo en un solo paso sin iteraciones)
 * - Agregar centinela al final del buffer UTF-8
 * - Cerrar archivo y limpiar lo necesario (Manejo optimo de recursos) (Mejora: Agregar un error_handler general)
 * - Contar cuantos caracteres Unicode validos hay en el buffer
 * - Reservar memoria para un buffer de caracteres Unicode de dimension n_caracteres + 1
 * - Codificar el buffer UTF-8 a Unicode
 * - Agregar centinela al final del buffer Unicode
 * - Cerrar archivo y limpiar lo necesario (Manejo optimo de recursos) (Mejora: Agregar un error_handler general)
 * - Devolver por el nombre puntero al buffer de caracteres Unicode
 *
 * - Pasos analogos para unicode_escribir_archivo_utf8
 */

#define UTF8_UCHAR_SIZE(x) (D_ES_CODE_POINT_1B(x) ? 1 : (D_ES_CODE_POINT_2B(x) ? 2 : (D_ES_CODE_POINT_3B(x) ? 3 : D_ES_CODE_POINT_4B(x) ? 4 \
																																		: 0)))
#define UCHAR_UTF8_SIZE(x) (E_ES_CODE_POINT_1B(x) ? 1 : (E_ES_CODE_POINT_2B(x) ? 2 : (E_ES_CODE_POINT_3B(x) ? 3 : E_ES_CODE_POINT_4B(x) ? 4 \
																																		: 0)))

uchar_t *unicode_leer_archivo_utf8(const char *nombre_archivo) {
	if (nombre_archivo == NULL)
		return NULL;

	FILE *f = fopen(nombre_archivo, "rb");
	if (f == NULL)
		return NULL;

	fseek(f, 0, SEEK_END);
	size_t n_bytes = ftell(f);
	fseek(f, 0, SEEK_SET);

	uint8_t *buffer = malloc(sizeof(uint8_t) * (n_bytes + 1));
	if (buffer == NULL) {
		fclose(f);
		return NULL;
	}

	if (fread(buffer, sizeof(uint8_t), n_bytes, f) != n_bytes) {
		fclose(f);
		free(buffer);
		return NULL;
	}
	fclose(f);
	buffer[n_bytes] = '\0';

	fprintf(stderr, "n_bytes: %zu\n", n_bytes);

	// Caracteres Unicode validos en el buffer
	size_t n_caracteres_unicode = 0;
	for (size_t i = 0, n_bytes_utf8; i < n_bytes; i += n_bytes_utf8) {
		n_bytes_utf8 = UTF8_UCHAR_SIZE(buffer[i]);
		n_caracteres_unicode++;
	}

	fprintf(stderr, "n_caracteres_unicode: %zu\n", n_caracteres_unicode);

	uchar_t *unicode_buffer = malloc(sizeof(uchar_t) * (n_caracteres_unicode + 1));
	if (unicode_buffer == NULL) {
		free(buffer);
		return NULL;
	}

	unicode_decodificar_utf8(unicode_buffer, buffer);
	unicode_buffer[n_caracteres_unicode] = '\0';

	free(buffer);

	return unicode_buffer;
}

bool unicode_escribir_archivo_utf8(const uchar_t *s, const char *nombre_archivo) {
	if (s == NULL || nombre_archivo == NULL)
		return false;

	FILE *f = fopen(nombre_archivo, "wb");
	if (f == NULL)
		return false;

	// Caracteres UTF-8 validos en el buffer
	size_t n_bytes_utf8 = 0;
	while (*s != '\0') {
		n_bytes_utf8 += UCHAR_UTF8_SIZE(*s);
		s++;
	}

	uint8_t *utf8_buffer = malloc(sizeof(uint8_t) * (n_bytes_utf8 + 1));
	if (utf8_buffer == NULL) {
		fclose(f);
		return false;
	}

	unicode_codificar_utf8(s, utf8_buffer);
	utf8_buffer[n_bytes_utf8] = '\0';

	if (fwrite(utf8_buffer, sizeof(uint8_t), n_bytes_utf8, f) != n_bytes_utf8) {
		fclose(f);
		free(utf8_buffer);
		return false;
	}

	fclose(f);

	free(utf8_buffer);

	return true;
}
