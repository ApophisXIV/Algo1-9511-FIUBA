#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// HACER: implementar los tipos de datos necesarios y las funciones

// Funciones auxiliares

/* -------------------------------------------------------------------------- */
// Invariante de representacion:
/* -------------------------------------------------------------------------- */
// - Si nombre == NULL, entonces saldo == 0 y archivo_movimientos == NULL
// - Si nombre != NULL, entonces saldo > 0 y archivo_movimientos != NULL
// - El saldo es un numero entero positivo
// - Todos los punteros apuntan a memoria valida
/* -------------------------------------------------------------------------- */

#define EXTENSION_MOVIMIENTOS ".movi"

typedef struct {
    char *nombre;
    uint64_t saldo;
    char *archivo_movimientos;
} cuenta_t;

/**
 * @brief   Crea una cuenta.
 * @pre     El nombre de la cuenta no debe estar vacio y no debe existir previamente.
 * @param   *nombre: nombre de la cuenta
 * @retval  Devuelve una cuenta con el nombre indicado
 */
cuenta_t *cuenta_crear(const char *nombre) {

    cuenta_t *cuenta = malloc(sizeof(cuenta_t));
    if (cuenta == NULL)
        return NULL;

    cuenta->nombre = malloc(strlen(nombre) + 1);
    if (cuenta->nombre == NULL) {
        free(cuenta);
        return NULL;
    }

    strcpy(cuenta->nombre, nombre);

    cuenta->saldo = 0;

    // Archivo.movi
    char *nombre_archivo = malloc(strlen(nombre) + 6);
    if (nombre_archivo == NULL) {
        free(cuenta->nombre);
        free(cuenta);
        return NULL;
    }

    strcpy(nombre_archivo, nombre);
    strcat(nombre_archivo, EXTENSION_MOVIMIENTOS);

    cuenta->archivo_movimientos = nombre_archivo;

    FILE *f_mov = fopen(nombre_archivo, "w");

    if (f_mov == NULL) {
        free(cuenta->nombre);
        free(cuenta->archivo_movimientos);
        free(cuenta);
        return NULL;
    }

    fclose(f_mov);

    return cuenta;
}

const char *cuenta_nombre(const cuenta_t *c) {
    if (c == NULL)
        return NULL;
    return c->nombre;
}

uint64_t cuenta_saldo(const cuenta_t *c) {
    if (c == NULL)
        return 0;
    return c->saldo;
}

bool cuenta_acreditar(cuenta_t *c, uint64_t cantidad, const char *descripcion) {
    if (c == NULL || cantidad == 0 || descripcion == NULL)
        return false;

    c->saldo += cantidad;

    // Archivo.movi
    FILE *f_mov = fopen(c->archivo_movimientos, "a");
    if (f_mov == NULL)
        return false;

    fprintf(f_mov, "%s %lu\n", descripcion, cantidad);

    fclose(f_mov);

    return true;
}

bool cuenta_extraer(cuenta_t *c, uint64_t cantidad, const char *descripcion) {
    if (c == NULL || cantidad == 0 || descripcion == NULL)
        return false;

    if (c->saldo < cantidad)
        return false;

    c->saldo -= cantidad;

    // Archivo.movi
    FILE *f_mov = fopen(c->archivo_movimientos, "a");
    if (f_mov == NULL)
        return false;

    fprintf(f_mov, "%s -%lu\n", descripcion, cantidad);

    fclose(f_mov);

    return true;
}

void cuenta_movimientos(cuenta_t *c, void f(int64_t cantidad, const char *descripcion)) {
    if (c == NULL || f == NULL)
        return;

    // Archivo.movi
    FILE *f_mov = fopen(c->archivo_movimientos, "r");
    if (f_mov == NULL)
        return;

    char buffer[1024];
    while (fgets(buffer, 1024, f_mov) != NULL) {
        char *descripcion = strtok(buffer, " ");
        char *cantidad_str = strtok(NULL, "\n");
        char *err_ptr;
        int64_t cantidad = (int64_t)strtol(cantidad_str, &err_ptr, 10);
        if (*err_ptr != '\0') {
            fprintf(stderr, "Error al convertir la cantidad\n");
            fclose(f_mov);
            return;
        }
        f(cantidad, descripcion);
    }

    fclose(f_mov);
}

void cuenta_destruir(cuenta_t *c) {
    if (c == NULL)
        return;

    free(c->nombre);
    free(c->archivo_movimientos);
    free(c);
}

// esto se utiliza en las pruebas
static uint64_t saldo_verificado = 0;
void sumar_movimiento(int64_t cantidad, const char *descripcion) {
    saldo_verificado += cantidad;
}

int main(void) {
    cuenta_t *c = cuenta_crear("Perez");
    assert(!strcmp(cuenta_nombre(c), "Perez"));
    assert(cuenta_saldo(c) == 0);
    cuenta_acreditar(c, 100, "Sueldo");
    assert(cuenta_saldo(c) == 100);
    assert(cuenta_extraer(c, 60, "Shopping") == true);
    assert(cuenta_saldo(c) == 40);
    assert(cuenta_extraer(c, 100, "Deudas") == false);
    assert(cuenta_saldo(c) == 40);

    cuenta_movimientos(c, sumar_movimiento);
    assert(saldo_verificado == 40);

    cuenta_destruir(c);

    printf("%s: OK\n", __FILE__);
    return 0;
}
