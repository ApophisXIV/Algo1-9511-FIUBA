#include <stdio.h>
#include <assert.h>

// HACER: Implementar la funcion `buscar`

int main(void) {
    // Pruebas con un arreglo de longitud 8
    int numeros[] = {2, 5, 7, 12, 14, 15, 20, 25};
    assert(buscar(numeros, 8, 12) == 3);

    // OPCIONAL: agregar pruebas.  Sugerencias:
    // * buscar un numero que este al principio del arreglo
    // * buscar un numero que este al final del arreglo
    // * buscar un numero que este repetido en el arreglo (buscar() deberia
    //   devolver el indice de cualquiera de ellos)
    // * buscar un numero x que no este en el arreglo y sea:
    //   * menor que el minimo del arreglo
    //   * mayor que el maximo del arreglo
    //   * entre el minimo y el maximo
    // * repetir las pruebas con un arreglo de longitud 1

    printf("%s: OK\n", __FILE__);
    return 0;
}
