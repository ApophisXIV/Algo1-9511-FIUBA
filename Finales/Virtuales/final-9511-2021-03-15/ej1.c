#include <assert.h>
#include <stdio.h>

// HACER: Implementar la funcion `buscar`

int calc_med(int izq, int der, int num, int arr[]) {
    return izq + ((der - izq) * (num - arr[izq]) / (arr[der] - arr[izq]));
}

int buscar(int numeros[], size_t n, int num) {

    if (numeros == NULL || n == 0)
        return -1;

    int izq = 0;
    if (numeros[izq] == num)
        return izq;

    int der = n - 1;
    if (numeros[der] == num)
        return der;
    
    int med = calc_med(izq, der, num, numeros);

    while (izq <= der) {
        if (numeros[med] == num)
            return med;
        else if (numeros[med] < num)
            izq = med + 1;
        else
            der = med - 1;
        med = calc_med(izq, der, num, numeros);
    }

    return -1;
}

int buscar_r(int numeros[], size_t n, int num) {
    if (numeros == NULL || n == 0)
        return -1;

    if (numeros[0] == num)
        return 0;
    if (numeros[n - 1] == num)
        return n - 1;

    int med = calc_med(0, n - 1, num, numeros);

    if (numeros[med] == num)
        return med;
    else if (numeros[med] < num)
        return buscar_r(numeros + med + 1, n - med - 1, num);
    else
        return buscar_r(numeros, med, num);
}

int main(void) {
    // Pruebas con un arreglo de longitud 8
    int numeros[] = {2, 5, 7, 12, 14, 15, 20, 20, 25};
    size_t len = sizeof(numeros) / sizeof(int);
    assert(buscar_r(numeros, len, 12) == 3);

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

    assert(buscar_r(numeros, len, 2) == 0);
    assert(buscar_r(numeros, len, 25) == 8);
    assert(buscar_r(numeros, len, 20) == 6 || buscar_r(numeros, len, 20) == 7);
    assert(buscar_r(numeros, len, 1) == -1);
    assert(buscar_r(numeros, len, 26) == -1);
    assert(buscar_r(numeros, len, 14) == 4);

    int numeros_2[] = {2};
    size_t len_2 = sizeof(numeros_2) / sizeof(int);
    assert(buscar_r(numeros_2, len_2, 2) == 0);

    printf("%s: OK\n", __FILE__);
    return 0;
}

//38 min