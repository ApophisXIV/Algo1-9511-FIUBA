// #include <stdio.h>

// // HACER: implementar la funcion.
// // Recomendacion: pensarla en forma recursiva.
// // Puede que sea necesario crear funciones auxiliares.

// static size_t n_imp = 0;

// void print_fila(char c_inicial, char *arr, size_t n, size_t k) {
// 	if (n == 0 || k > n + 1)
// 		return;
// 	printf("%c", c_inicial);
// 	for (size_t i = 0; i < k - 1; i++)
// 		printf("%c", arr[i]);
// 	printf("\n");
// 	n_imp++;
// 	print_fila(c_inicial, arr + 1, n - 1, k);
// }

// void combinaciones(char caracteres[], size_t n, size_t k) {
// 	if (k > n)
// 		return;
// 	print_fila(caracteres[0], caracteres + 1, n - 1, k);
// 	combinaciones(caracteres + 1, n - 1, k);
// 	// FIXME Generalizar la solucion
// }

// int main(void) {
// 	char caracteres[] = {'a', 'b', 'c', 'd'};
// 	size_t n = 4;
// 	size_t k = 3;
// 	combinaciones(caracteres, n, k);

// 	printf("n: %zu\n", n_imp);

// 	// debe imprimir:
// 	//
// 	//  ab
// 	//  ac
// 	//  ad
// 	//  bc
// 	//  bd
// 	//  cd

// 	// NOTE: Numero combinatorio (Investigar #GaspiTip)

// 	return 0;
// }


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

size_t factorial(size_t n) {
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

size_t numero_combinatorio(size_t n, size_t k){
    return factorial(n) / (factorial(k) * factorial(n - k));
}

void imprimir_fila(char c_inicial, char *arr, size_t n, size_t k) {
    if (n == 0 || k > n + 1)
        return;
    printf("%c", c_inicial);
    for (size_t i = 0; i < k - 1; i++)
        printf("%c", arr[i]);
    printf("\n");

    if(n - k > 0){

    }


    // imprimir_fila(c_inicial, arr + 1, n - 1, k);
}

void combinaciones (char *caracteres, size_t n, size_t k){
    if (k > n)
        return;
    imprimir_fila(caracteres[0], caracteres + 1, n - 1, k);
    combinaciones(caracteres + 1, n - 1, k);
}

int main (void){
    char caracteres[] = {'a', 'b', 'c', 'd'};

    printf ("%zu\n", numero_combinatorio(4, 3));

    combinaciones (caracteres, 4, 3);

    //abc
    //abd
    //acd
    //bcd

    return 0;
}
