/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief Introducción al lenguaje de programación C - Guia 1
 * @version 0.1
 * @date 2021-09-06
 *
 * @copyright Copyright (c) 2021
 *
 */

// TODO 27 59

/* ---------------------------------- Notes --------------------------------- */
/**
 * %d = %i -> Entero con signo
 * %u -> Entero sin signo
 * %o -> Octal
 * %x -> Hexadecimal
 * %X -> Hexadecimal en mayusculas
 * %f = %F -> Float (%1.4) (4 decimales)
 * %e -> Notacion cientifica en minisculas
 * %E -> Notacion cientifica en mayusculas
 * %g = %G -> La representacion mas corta de un numero %f o %e. Tanto en minusculas como mayusculas
 * %a = %A -> Float en hexadecimal en minusculas y mayusculas
 */
/* -------------------------------------------------------------------------- */
/**
 * fgets (buffer, sizeof(buffer), stdin) devuelve NULL si ocurrio un error o llego a un EOF
 */
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#define N_Ejercicio 52

/* -------------------------------------------------------------------------- */
/*                                Introducción                                */
/* -------------------------------------------------------------------------- */

#if N_Ejercicio == 1

#include <math.h>

float totalAmount(float initialCap, float interestRate, unsigned int years) {

    return (initialCap * pow(1 + interestRate / 100, years));
}

int main(void) {

    printf("Monto Final: %1.3f\n", totalAmount(100, 100, 3));

    return 0;
}

#elif N_Ejercicio == 2

float farenheitToCelsius(float tempFarenheit) {

    return ((tempFarenheit - 32) * 5) / 9;
}

int main(void) {

    printf("%1.1f°F = %1.1f°C\n", 199.4, farenheitToCelsius(199.4));

    return 0;
}

#elif N_Ejercicio == 3

float celsiusToFahrenheit(float tempCelsius) {

    return (tempCelsius * 9) / 5 + 32;
}

int main(void) {

    printf("%1.1f°C = %1.1f°F\n", 93.0, celsiusToFahrenheit(93.0));

    return 0;
}

#elif N_Ejercicio == 4

unsigned long timeToSeconds(unsigned short hour, unsigned short minute, unsigned short seconds) {

    if ((hour > 23) || (minute > 59) || (seconds > 59)) {

        printf("ERROR La funcion no acepta valores mayores a 23:59:59\n");
        return 0;
    }

    else {

        return (hour * 3600 + minute * 60 + seconds);
    }
}

int main(void) {

    printf("Transcurrieron %u segundos desde que comenzo el dia", timeToSeconds(11, 35, 34));

    return 0;
}

#elif N_Ejercicio == 5

#include <math.h>

double vectorNorm(double x, double y, double z) {

    return sqrt(x * x + y * y + z * z);
}

int main(void) {

    printf("La norma del vector (5 , 3.4 , 8) es %f", vectorNorm(5, 3.4, 8));

    return 0;
}

#elif N_Ejercicio == 6

#define PI 3.14159265358979323846

#define cylinderRadius 5.5
#define cylinderHeight 8.0

double diameter(double radius) {

    return (2 * radius);
}

double circumference(double radius) {

    return (diameter(radius) * PI);
}

double circleArea(double radius) {

    return (PI * radius * radius);
}

double cylinderVolume(double radius, double height) {

    return (circleArea(radius) * height);
}

double cylinderArea(double radius, double height) {

    return (2 * circleArea(radius) + circumference(radius) * height);
}

int main(void) {

    double cc[5] = {

        diameter(cylinderRadius),
        circumference(cylinderRadius),
        circleArea(cylinderRadius),
        cylinderVolume(cylinderRadius, cylinderHeight),
        cylinderArea(cylinderRadius, cylinderHeight)};

    printf("\n=======================Caracteristicas del cilindro========================\n");
    printf("Radio: %f                      Altura: %f\n", cylinderRadius, cylinderHeight);
    printf("===========================================================================\n");

    printf("===========================================================================\n");
    printf("Diametro: %f   Perimetro: %f   Area base: %f\n", cc[0], cc[1], cc[2]);
    printf("Volumen: %f   Area: %f \n", cc[3], cc[4]);
    printf("===========================================================================\n");

    return 0;
}

#elif N_Ejercicio == 7

unsigned int oddEven(int n) {

    return n % 2;
}

int main(void) {

    printf("8 es %s, pero 3 es %s", (!oddEven(8) ? "PAR" : "IMPAR"), (!oddEven(3) ? "PAR" : "IMPAR"));

    return 0;
}

#elif N_Ejercicio == 8

#define n1 "-84, "
#define n2 "345, "
#define n3 "10 "
#define _n1 -84
#define _n2 345
#define _n3 10

int specialMultiple(int n) {

    return (n - n % 10);
}

int main(void) {

    printf("Los multiplos de 10 inferiores a " n1 n2 n3 "mas cercanos son %i %i %i respectivamente", specialMultiple(_n1), specialMultiple(_n2), specialMultiple(_n3));
    return 0;
}

#elif N_Ejercicio == 9

int isGreater(int a, int b) {

    return a == b ? 0 : (a < b ? -1 : 1);
}

const char *isGreater_string(int a, int b) {

    return a == b ? "IGUAL" : (a < b ? "MENOR" : "MAYOR");
}

int main(void) {

    printf("%i %i %i\n", isGreater(7, 9), isGreater(12, -10), isGreater(99, 99));
    printf("7 es %s que 9, 12 es %s que -10 y 99 es %s que 99", isGreater_string(7, 9), isGreater_string(12, -10), isGreater_string(99, 99));
    return 0;
}

#elif N_Ejercicio == 10

int signCheck(int n) {

    return n == 0 ? 0 : (n > 0 ? 1 : -1);
}

const char *signCheck_string(int n) {

    return n == 0 ? "NEUTRO" : (n > 0 ? "POSITIVO" : "NEGATIVO");
}

int main(void) {

    printf("%i %i %i\n", signCheck(-324), signCheck(7676), signCheck(0));
    printf("-324 es %s, 7676 es %s y 0 es %s", signCheck_string(-324), signCheck_string(7676), signCheck_string(0));
    return 0;
}

#elif N_Ejercicio == 11

unsigned int signCheck(int n) {

    return n == 0 ? 0 : (n > 0 ? 1 : 0);
}

const char *signCheck_string(int n) {

    return n == 0 ? "NEUTRO" : (n > 0 ? "POSITIVO" : "NEGATIVO");
}

int main(void) {

    printf("%i %i %i\n", signCheck(-324), signCheck(7676), signCheck(0));
    printf("-324 es %s, 7676 es %s y 0 es %s", signCheck_string(-324), signCheck_string(7676), signCheck_string(0));
    return 0;
}

#elif N_Ejercicio == 12

int main(void) {

    printf("Nombre: Guido\nApellido: Rodriguez\nPadron: 108723");
    return 0;
}

#endif    // Introduccion

/* -------------------------------------------------------------------------- */
/*                         Programas sencillos: Ciclos                        */
/* -------------------------------------------------------------------------- */

#if N_Ejercicio == 13

int main(void) {

    for (int i = 0; i <= 10; i++) {

        printf("7 x %d = %d\n", i, i * 7);
    }

    return 0;
}

#elif N_Ejercicio == 14

int main(void) {

    for (int i = 1; i <= 10; i++) {

        printf("\n====Tabla del %d====\n", i);

        for (int j = 0; j <= 10; j++) {

            printf("    %d x %d = %d\n", i, j, i * j);
        }

        printf("====================\n");
    }

    return 0;
}

#elif N_Ejercicio == 15

float celsiusToFahrenheit(float tempCelsius) {

    return (tempCelsius * 9) / 5 + 32;
}

int main(void) {

    for (int i = 0; i <= 100; i += 10) {

        printf("%d°C = %1.2f°F\n", i, celsiusToFahrenheit((float)i));
    }

    return 0;
}

#elif N_Ejercicio == 16

void hLine(int i) {

    printf("\n");

    for (int k = 0; k <= i; k++) {
        printf("+---+---+ ");
    }
}

int main(void) {

    printf("====Fichas del domino====\n");

    for (int i = 6; i >= 0; i--) {

        hLine(i);

        printf("\n");

        for (int j = 0; j <= i; j++) {

            printf("| %d | %d | ", i, j);
        }
        hLine(i);
    }

    printf("\n");

    return 0;
}

#elif N_Ejercicio == 17

#include <math.h>

// En estos ejercicios en vez de usar u
//  long o cosas así podemos usar double que
//  si bien perdemos exactitud podemos tener
//  un buen rango de representacion

long nFactorial(int n) {

    if (n <= 1)
        return 1;

    return n * nFactorial(n - 1);
}

double euler(int res) {

    double e = (1.0 / nFactorial(res));

    if (res > 1) {

        return 1.0 / nFactorial(res) + euler(res - 1);
    }

    else {

        return 1.0 + e;
    }
}

// #define _DEBUG

double eulerX(float x, int depth) {

    double _x = x;

    double result;

    for (int i = 1; i < depth; i++) {    // Potencia de x^1 a x^n

        _x *= x;
    }

    if (depth > 1) {

        result = (_x / nFactorial(depth)) + eulerX(x, depth - 1);
    }

    else {

        result = 1.0 + (_x / nFactorial(depth));
    }

#ifdef _DEBUG
    printf("[%03d] | Retval: %04.1f | depth: %i | x: %1.1f | x^%i: %08.1f | n!: %05lu | Coeff(E): %04.1f | Coeff(R): %04.1f \n", depth, result, depth, x, depth, _x, nFactorial(depth), (_x / nFactorial(depth)), coefficient);
#endif

    return result;
}

double eulerX_(float x, int n) {

    return (pow(euler(n), x));
}

int main(void) {

    // Consultar sobre como determinar la profundidad y definir precision

    printf("---------------------------------\n");
    printf("n!  | n=8  |     | -> %lu\n", nFactorial(8));
    printf("---------------------------------\n");
    printf("e   | n=8  |     | -> %f\n", euler(8));
    printf("------------------------------------------------------------------------\n");

    for (int i = 0; i <= 20; i++) {

        printf("e^x | n=%02d | x=4 | -> %012f | %012f <- | x=4 | n=%02d | e^x\n", i, eulerX(4, i), eulerX_(4, i), i);
        printf("------------------------------------------------------------------------\n");
        printf("DR: %f\n", eulerX(4, i) - eulerX_(4, i));
        printf("------------------------------------------------------------------------\n");
    }

    return 0;
}

#elif N_Ejercicio == -17    // Forma Santisi

#define EPSILON 1e-16

double factorial(int n) {
    double f = 1;
    for (int i = 2; i <= n; i++)
        f *= i;

    return f;
}

double euler() {
    double e = 0;
    int i;    // Tarea para el hogar: Eliminar la doble llamada a factorial.
    for (i = 0; 1 / factorial(i) > EPSILON; i++)
        e += 1 / factorial(i);

    return e;
}

double euler_2() {
    double e = 1;
    double f = 1;
    int i;
    for (i = 1; 1 / f > EPSILON; i++) {
        f *= i;
        e += 1 / f;
    }

    return e;
}

int main(void) {

    for (int i = 0; i <= 50; i++) {
        printf("%d! = %.f\n", i, factorial(i));
    }

    printf("%.16f\t%.16f\n", euler(), euler_2());

    return 0;
}

#elif N_Ejercicio == 18

long nFactorial(int n) {

    if (n <= 1)
        return 1;

    return n * nFactorial(n - 1);
}

long binomialCoefficient(long n_Set, long subSetLength) {

    return (nFactorial(n_Set) / (nFactorial(subSetLength) * nFactorial(n_Set - subSetLength)));
}

int main(void) {
    printf("Combinaciones posibles: n=10 k=3 -> %lu\n", binomialCoefficient(3, 1));
    return 0;
}

#elif N_Ejercicio == 19

long nFactorial(int n) {

    if (n <= 1)
        return 1;

    return n * nFactorial(n - 1);
}

long binomialCoefficient(long n_Set, long subSetLength) {

    return (nFactorial(n_Set) / (nFactorial(subSetLength) * nFactorial(n_Set - subSetLength)));
}

void desarrollar_binomio(int n) {

    printf("(x + y)^%i = ", n);

    for (int k = 0; k <= n; k++) {

        printf("%li .x^%i. y^%i + ", binomialCoefficient(n, k), n - k, k);
    }
}

int main(void) {

    desarrollar_binomio(3);

    return 0;
}

#elif N_Ejercicio == 20

void mirroring(int i) {

    int mirrorNumber = 0;

    while (i != 0) {

        mirrorNumber = mirrorNumber * 10 + i % 10;
        i /= 10;
    }

    printf("%d\n", mirrorNumber);
}

int main(void) {

    mirroring(9511);

    int i, j = 0;
    j = i;
    i = j = 5;

    return 0;
}

#endif    // Programas sencillos: Ciclos

/* -------------------------------------------------------------------------- */
/*                       Programas sencillos: Decisiones                      */
/* -------------------------------------------------------------------------- */

#if N_Ejercicio == 21

#include <stdbool.h>

// Ejemplo de early return
// Pruebo mediante un contra ejemplo que el numero n no es primo

bool es_primo(int n) {

    if (n < 2)
        return false;

    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;
    return true;
}

int main(void) {

    for (int i = 0; i < 100; i++)
        if (es_primo(i))
            printf("Primo: %d\n", i);

    return 0;
}

#elif N_Ejercicio == 22

const char *isGreater(int x, int y) {

    return x > y ? "x es mayor que y" : (x < y ? "x es menor que y" : "x e y son iguales");
}

int main(void) {

    printf("%s\n%s\n%s\n", isGreater(5, 2), isGreater(1, 7), isGreater(4, 4));

    return 0;
}

#elif N_Ejercicio == 23

int abs(int i) {
    return (i < 0) ? (-1 * i) : (i);
}

int main(void) {

    printf("-7 -> %i\n 0 -> %i\n 3 -> %i\n", abs(-7), abs(0), abs(3));

    return 0;
}

#elif N_Ejercicio == 24

void printIdentity(unsigned int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (i == j)
                printf("1 ");
            else
                printf("0 ");
        }
        printf("\n");
    }
}

int main(void) {

    printIdentity(8);

    return 0;
}

#elif N_Ejercicio == 25

#include <math.h>

int resolvente(float raices[2], float coefficient[3]) {

    float discriminant = coefficient[1] * coefficient[1] - 4 * coefficient[0] * coefficient[2];

    if (discriminant < 0 || !coefficient[0])
        return -1;

    discriminant = sqrt(discriminant);
    raices[0] = (coefficient[1] + discriminant) / (2 * coefficient[0]);
    raices[1] = (coefficient[1] - discriminant) / (2 * coefficient[0]);

    return 0;
}

int main(void) {

    float pol[3] = {3, 4, -85};    // 2x² + 4x -85

    float solution[2] = {0};

    if (!(resolvente(solution, pol))) {
        printf("Polinomio: %1.2fx^2 %1.2fx %1.2f -> x1: %1.2f x2: %1.2f\n", pol[0], pol[1], pol[2], solution[0], solution[1]);
        return 0;
    }

    printf("El polinomio %1.2fx^2 %1.2fx %1.2f no tiene solucion en los numeros reales\n", pol[0], pol[1], pol[2]);
    return 1;
}

#elif N_Ejercicio == 26

float interseccionRectas(float m1, float o1, float m2, float o2) {

    return (o2 - o1) / (m1 - m2);
}

int main(void) {

    float m1 = 4.0;
    float o1 = 1.0;
    float m2 = 8.0;
    float o2 = -3.0;

    if (!(m1 - m2)) {
        printf("ERR. Las rectas son paralelas\n");
        return 1;
    }

    printf("%f\n", interseccionRectas(m1, o1, m2, o2));

    return 0;
}

#elif N_Ejercicio == 27

#define uint unsigned int

#include <stdbool.h>

bool esBisiesto(uint anio) {

    return !(anio % 4) && ((anio % 100) || (anio % 400)) ? 1 : 0;
}

float toDays(float dia, uint mes, uint anio) {

    return (dia + mes * 30.417 + anio * 365);
}

bool isValidDate(float dia, uint mes, uint anio) {

    return dia > 30.417 || dia < 1 || mes > 12 || mes < 1 || anio < 0 ? 0 : 1;
}

void daysRemaining(float dia, uint mes, uint anio) {

    if (isValidDate(dia, mes, anio)) {
        printf("Dias restantes hasta fin del mes %d: %f\n", mes, 30 - dia);
        printf("Dias restantes hasta fin de anio: %f\n", 365 - toDays(dia, mes, anio));
        printf("Dias transcurridos desde el inicio de %d: %f\n", anio, 2 * 365 - dia);
    }

    printf("No es una fecha valida\n");
}

void oraculo(uint dia1, uint mes1, uint anio1, uint dia2, uint mes2, uint anio2) {
}

int main(void) {

    printf("2020 %s es bisiesto pero 2021 %s lo es\n", esBisiesto(2020) ? "SI" : "NO", esBisiesto(2021) ? "SI" : "NO");
    printf("Mes: 4 Anio: 1989 -> Dias %f\n", toDays(0, 4, 1989));
    printf("-2 1 2001 %s es valido pero 29 11 2001 %s lo es\n", isValidDate(-2, 1, 2001) ? "SI" : "NO", isValidDate(29, 11, 2001) ? "SI" : "NO");
    daysRemaining(8, 10, 2021);
    return 0;
}

#elif N_Ejercicio == 28

void minPesos(unsigned long pesos) {

    unsigned int denominaciones[7] = {1000, 500, 200, 100, 50, 20, 10};

    printf("%ld ARS = (", pesos);

    for (size_t i = 0; i < sizeof(denominaciones) / sizeof(denominaciones[0]); i++) {

        if (pesos >= denominaciones[i]) {

            printf("%ldx%d ARS", pesos / denominaciones[i], denominaciones[i]);
            pesos %= denominaciones[i];

            if (pesos >= 10)
                printf(" + ");
        }
    }
    printf(")\n");

    if (pesos)
        printf("Faltan %ld monedas de 1$\n", pesos);
}

int main(void) {

    minPesos(6287);
    return 0;
}

#elif N_Ejercicio == 29

// Opcion recursiva
int mcd_r(int n, int m) {

    if (!m)
        return n;
    return mcd_r(m, n % m);
}

int mcd(int n, int m) {

    if (!n || !m) {
        printf("Error: Ninguno de los numeros debe ser 0\n");
        return 1;
    }

    int r = m % n;

    while (r != 0) {
        m = n;
        n = r;
        r = m % n;
    }

    return n;
}

int main(void) {

    printf("2940 y 3150 MCD: %d\n", mcd(2940, 3150));
    printf("2940 y 3150 MCD: %d (recursivo)\n", mcd_r(2940, 3150));
    return 0;
}

#elif N_Ejercicio == 30

void messages(char c) {

    switch (c) {
    case 'A':
        printf("House Arryn\n");
        break;
    case 'B':
        printf("House Baratheon\n");
        break;
    case 'F':
        printf("House Frey\n");
        break;
    case 'G':
        printf("House Greyjoy\n");
        break;
    case 'L':
        printf("House Lannister\n");
        break;
    case 'M':
        printf("House Martell\n");
        break;
    case 'S':
        printf("House Stark\n");
        break;
    case 'T':
        printf("House Targaryen\n");
        break;
    default:
        printf("No lo conozco\n");
        break;
    }
}

int main(void) {

    char *c = "ABFGLMST-";

    for (size_t i = 0; c[i]; i++) {
        messages(c[i]);
    }

    return 0;
}

#endif    // Programas sencillos: Decisiones

/* -------------------------------------------------------------------------- */
/*                                Entendiendo C                               */
/* -------------------------------------------------------------------------- */

#if N_Ejercicio == 31

#include <limits.h>
#include <stdbool.h>

int main(void) {

    char a0;
    unsigned char a1;
    short b0;
    unsigned short b1;
    int c0;
    unsigned int c1;
    long d0;
    long long d1;
    unsigned long d2;
    size_t e0;
    bool f0;
    float g0;
    double h0;
    long double h1;

    printf("\033[31;1m char \033[0m----------- \033[32;1m %zu\033[0m\033[33;1m Byte\033[0m  --- \033[34;1m(%d a %d)\033[0m\n", sizeof(a0), CHAR_MIN, CHAR_MAX);
    printf("\033[31;1m unsigned char \033[0m-- \033[32;1m %zu\033[0m\033[33;1m Byte\033[0m  --- \033[34;1m(0 a %d)\033[0m\n", sizeof(a1), UCHAR_MAX);
    printf("\033[31;1m short \033[0m---------- \033[32;1m %zu\033[0m\033[33;1m Bytes\033[0m --- \033[34;1m(%hd a %hd)\033[0m\n", sizeof(b0), SHRT_MIN, SHRT_MAX);
    printf("\033[31;1m unsigned short \033[0m- \033[32;1m %zu\033[0m\033[33;1m Bytes\033[0m --- \033[34;1m(0 a %hu)\033[0m\n", sizeof(b1), USHRT_MAX);
    printf("\033[31;1m int \033[0m------------ \033[32;1m %zu\033[0m\033[33;1m Bytes\033[0m --- \033[34;1m(%d a %d)\033[0m\n", sizeof(c0), INT_MIN, INT_MAX);
    printf("\033[31;1m unsigned int \033[0m--- \033[32;1m %zu\033[0m\033[33;1m Bytes\033[0m --- \033[34;1m(0 a %lu)\033[0m\n", sizeof(c1), UINT_MAX);
    printf("\033[31;1m long \033[0m----------- \033[32;1m %zu\033[0m\033[33;1m Bytes\033[0m --- \033[34;1m(%ld a %ld)\033[0m\n", sizeof(d0), LONG_MIN, LONG_MAX);
    printf("\033[31;1m long long \033[0m------ \033[32;1m %zu\033[0m\033[33;1m Bytes\033[0m --- \033[34;1m(%ld a %ld)\033[0m\n", sizeof(d1), LLONG_MIN, LLONG_MAX);
    printf("\033[31;1m unsigned long \033[0m-- \033[32;1m %zu\033[0m\033[33;1m Bytes\033[0m --- \033[34;1m(0 a %lu)\033[0m\n", sizeof(d2), ULONG_MAX);
    printf("\033[31;1m size_t \033[0m--------- \033[32;1m %zu\033[0m\033[33;1m Bytes\033[0m --- \033[34;1m(0 a %zu)\033[0m\n", sizeof(e0), __SIZE_MAX__);
    printf("\033[31;1m bool \033[0m----------- \033[32;1m %zu\033[0m\033[33;1m Bytes\033[0m --- \033[34;1m(0 a 1) (true o false)\033[0m\n", sizeof(f0));
    printf("\033[31;1m float \033[0m---------- \033[32;1m %zu\033[0m\033[33;1m Bytes\033[0m --- \033[34;1m(+/-)(%e a %e)\033[0m\n", sizeof(g0), __FLT_MIN__, __FLT_MAX__);
    printf("\033[31;1m double \033[0m--------- \033[32;1m %zu\033[0m\033[33;1m Bytes\033[0m --- \033[34;1m(+/-)(%e a %e)\033[0m\n", sizeof(h0), __DBL_MIN__, __DBL_MAX__);
    printf("\033[31;1m long double \033[0m---- \033[32;1m%zu\033[0m\033[33;1m Bytes\033[0m --- \033[34;1m(+/-)(%Le a %Le)\033[0m\n", sizeof(h1), __LDBL_MIN__, __LDBL_MAX__);

    return 0;
}

#elif N_Ejercicio == 32

int main(void) {
    printf("a) %li bytes\n", sizeof(float) * 3600);
    printf("b1) %i bytes\n", (1920 * 1080) / 8);
    printf("b2) %i bytes\n", (1920 * 1080 * 8) / 8);
    printf("b3) %i bytes\n", (1920 * 1080 * 24) / 8);
    printf("c) %i bytes\n", ((int)(12e6 * 24)) / 8);
    printf("d1) %i bytes\n", (int)(44.1e3 * 60 * 16) / 8);
    printf("d2) %i bytes\n", (int)(192e3 * 60 * 16) / 8);
    printf("d3) %i bytes\n", (int)(44.1e3 * 2 * 60 * 16) / 8);
    return 0;
}

#elif N_Ejercicio == 33

long sumar(int a, int b) {
    return a + b;
}

long restar(int a, int b) {
    return a - b;
}

float multiplicar(int multiplicando, int multiplicador) {
    return multiplicando * multiplicador;
}

double dividir(int dividendo, int divisor) {
    return (float)dividendo / divisor;
}

int mod(int a, int b) {
    return (a % b);
}

int main(void) {

    printf("Suma 8+3= %li\n", sumar(8, 3));
    printf("Resta 6-83= %li\n", restar(6, 83));
    printf("Multiplicar 45*3= %.0f\n", multiplicar(45, 3));
    printf("Dividir 184/1145= %f\n", dividir(184, 1452));
    printf("Mod 9 mod 2= %d\n", mod(9, 2));

    return 0;
}
// b) Deberiamos modificar los datatypes en las firmas de funcion

#elif N_Ejercicio == 34

int main(void) {

    const int numero = 6;
    const char caracter = '6';
    const char *cadena = "666"

        return 0;
}

#elif N_Ejercicio == 35

int main(void) {

    const float M_PI = 3.14159265358979;
    const char *STR_HOLA_MUNDO = "Hola Mundo";
    const unsigned int NOTA_MAX = 10;
    const unsigned int NOTA_MIN_APROBADO = 4;
    const unsigned int SEGxHORA = 3600;

    return 0;
}

#elif N_Ejercicio == 36

int main(void) {

    if (8 == 8)    // Comparacion
        printf("Son iguales\n");

    int p = 32;    // Asignacion
    printf("%d\n", p);

    return 0;
}

#elif N_Ejercicio == 37

int main(void) {

    const float M_PI = 3.14159265358979;

    // M_PI = 3.14159; -> El compilador daria un error ya que no podemos escribir en memoria de tipo read-only

    return 0;
}

#elif N_Ejercicio == 38

int main(void) {

    const unsigned int NOTA_MAX = 10;

    int nota = 6;

    NOTA_MAX == nota;    // Esta sentencia es valida pero inutil ya que comparamos pero descartamos el resultado booleano

    return 0;
}

#elif N_Ejercicio == 39

// NOTE En mi caso la salida siempre es 0. Pero esto debe ser por alguna
// optmimizacion que hace el compilador asignando 0 a las variables sin
// inicializar que esten presentes
int main(void) {

    int d;
    float f;
    char c;

    printf("%d %f %c\n", d, f, c);

    return 0;
}

#elif N_Ejercicio == 40

int main(void) {
    /* -------------------------------------------------------------------------- */

    // printf ("El producto de %d y %d es %d"\n, x, y);
    printf("El producto de %d y %d es %d\n", x, y, x * y);

    /* -------------------------------------------------------------------------- */

    // a + b = suma;
    suma = a + b;

    /* -------------------------------------------------------------------------- */

    // */ Programa para obtener el máximo */
    /* Programa para obtener el máximo */

    /* -------------------------------------------------------------------------- */

    // if (numero => maximo)
    //     maximo == numero;
    if (numero >= maximo)
        maximo = numero;

    /* -------------------------------------------------------------------------- */

    // printf ("El resto de dividir %d por %d es\n",
    //     numerador,
    //     denominador,
    //     numerador % denominador);
    printf("El resto de dividir %d por %d es %d\n",
           numerador,
           denominador,
           numerador % denominador);

    /* -------------------------------------------------------------------------- */

    // if (x = y)
    //      print ("%d es igual a %d\n", x, y);
    if (x == y)
        printf("%d es igual a %d\n", x, y);

    /* -------------------------------------------------------------------------- */

    // print ("La suma da %d\n," x + y);
    printf("La suma da %d\n", x + y);

    /* -------------------------------------------------------------------------- */
    return 0;
}

#elif N_Ejercicio == 41

int main(void) {

    printf("A\n");
    printf("%d\n", '0');
    printf("%d\n", 'J');
    return 0;
}

#elif N_Ejercicio == 42

int main(void) {

    int cero = 0;
    char ceroChar = '0';

    char resta = '6' - '0';     // Esto es equivalente a 54 - 48 = 6. En la tabla ASCII esto es un caracter de control
    char resta2 = 'X' - 'A';    // Esto es equivalente a 88 - 65 = 23. En la tabla ASCII esto es un caracterde control

    // Los que son caracteres de control no son representados en la salida ya que no tienen un simbolo definido
    // Sin embargo si los representamos como enteros si aparece 6 y 23 respectivamente
    printf("%d %c %d %c %d %c\n", cero, ceroChar, resta, resta, resta2, resta2);

    return 0;
}

#elif N_Ejercicio == 43

#include <limits.h>    //Header donde estan declarados los limites de los tipos de datos
#include <stdlib.h>

int main(void) {
    printf("%d\n", INT_MIN);
    printf("%d\n", INT_MAX);
    printf("%d\n", RAND_MAX);
    printf("%u\n", UINT_MAX);
    return 0;
}

#elif N_Ejercicio == 44

void datosPersonales1() {
    puts("Nombre: Guido");
    puts("Apellido: Rodriguez");
    puts("Padron: 108723");
}
void datosPersonales2() {
    puts("\nNombre: Guido\nApellido: Rodriguez\nPadron: 108723");
}
void datosPersonales3() {
    printf("\nNombre: Guido\n");
    printf("Apellido: Rodriguez\n");
    printf("Padron: 108723\n");
}

int main(void) {
    datosPersonales1();
    datosPersonales2();
    datosPersonales3();
    return 0;
}

#elif N_Ejercicio == 45

int main(void) {
    printf("%.2f\n", 3.1415927f);                 //%.2f  Dos decimales
    printf("%.3f\n", 3.1415927f);                 //%.3f  Tres decimales
    printf("%+.2f\n", 3.1415927f);                //%+.2f Dos decimales con signo explicito
    printf("%+.5f\n", -3.1415927f);               //%+.4f Cinco decimales con signo explicito
    printf("%10c%+010.4f\n", ' ', 3.1415927f);    //%10c 10 espacios en blanco para alinear a la derecha
                                                  //%+010.4f 4 decimales con signo explicito y en longitud
                                                  // fija de 10 digitos
    return 0;
}

#elif N_Ejercicio == 46

/* Implementacion de datatype bool */

typedef enum {
    FALSE,
    TRUE
} bool;

typedef unsigned int bool_T;

int main(void) {

    bool bit = FALSE;
    bool_t bit2 = TRUE;

    printf("bit: %s bit2: %s\n", bit ? "VERDADERO" : "FALSO", bit2 ? "VERDADERO" : "FALSO");

    return 0;
}

#elif N_Ejercicio == 47

#include <stdlib.h>

typedef enum {
    ST_OK,
    ST_ERR_VALOR_NEGATIVO,
    ST_ERR_VALOR_NULO
} status_t;

int main(void) {

    status_t errorCode = ST_OK;

    printf("Ingrese un numero positivo por favor\n");

    char buffer[100];
    fgets(buffer, 100, stdin);

    if (atoi(buffer) == 0) {
        errorCode = ST_ERR_VALOR_NULO;
        printf("ERR_CODE: %d\n", errorCode);
    }

    if (atoi(buffer) < 0) {
        errorCode = ST_ERR_VALOR_NEGATIVO;
        printf("ERR_CODE: %d\n", errorCode);
    }

    if (atoi(buffer) > 0) {
        errorCode = ST_OK;
        printf("Gracias, vuelvan pronto. ERR_CODE: %d\n", errorCode);
    }

    return errorCode;
}

#elif N_Ejercicio == 48

typedef unsigned char byte_t;

int main(void) {

    byte_t reg = 76;    // Un byte es un arreglo de 8 bits

    printf("%d\n", reg);

    return 0;
}

#elif N_Ejercicio == 49

#include <inttypes.h>
#include <stdint.h>

int main(void) {

/***************************** stdint.h ***************************/

    // Defined Width Type
    int8_t uint8_t
    int16_t uint16_t
    int32_t uint32_t
    int64_t uint64_t
    intmax_t uintmax_t  // El datatype con el size maximo con y sin signo
    intptr_t uintptr_t  // El datatype capaz de almacenar punteros con y sin signo

    // Fast Type
    int_fast8_t uint_fast8_t
    int_fast16_t uint_fast16_t
    int_fast32_t uint_fast32_t
    int_fast64_t uint_fast64_t

    int_least8_t uint_least8_t
    int_least16_t uint_least16_t
    int_least32_t uint_least32_t
    int_least64_t uint_least64_t

    intX_t
    // Is a type of exactly X bit width, two's complement
    // representation, and no padding bits. Such is useful e.g. for work
    // in binary interfaces; its presence is optional, defined only on
    // architectures that have an integer type of exactly that width.

    int_leastX_t
    // The smallest possible type of at least X bit
    // width, with implementation-defined representation and padding.
    // It might be wider, if exact X bit width is unavailable, e.g. for
    // work in algorithmics where you need a specific minimum value range.

    int_fastX_t
    // Is a type of at least X bit width. It might be wider
    // if the wider type can be handled more efficiently by the CPU,
    // trading memory footprint for speed.

    // The first one is very specific, but optional. The other two give
    // the compiler some wiggle room if the underlying hardware is tricky,
    // i.e. you tell the compiler under which conditions you would accept
    // a wider type than requested.

    // Un ejemplo es en el caso de tener un compilador C para un sistema de 36 bits,
    // con char = 9 bits, short = 18 bits, int = 36 bits, y long = 72 bits.
    // En ese caso int8_t no existe, porque no hay forma de satisfacer la restricción
    // de tener exactamente 8 bits de valor sin relleno con 0. (int8_t no es "nativo")
    // int_least8_t es un typedef de char. NO de short o int, porque el estándar
    // requiere el tipo más pequeño con al menos 8 bits.
    // int_fast8_t puede ser cualquier cosa. Es probable que sea un typedef de int
    // si el tamaño "nativo" (Bus de datos, ALU, CPU) se considera "rápido".

/******************************************************************/

/**************************** inttypes.h **************************/

    //-----------------------------------------------------------------
    // Resumen: inttypes.h incluye a stdint.h por lo que voy a tener las
    // mismas definiciones de base pero ademas voy a tener otras macros
    // como las PRIuXX muy utiles para la portabilidad de codigo al usar
    // printf, fprintf, sprintf, snprintf, scanf, etc
    //-----------------------------------------------------------------

    // The purpose of <inttypes.h> is to provide a set of integer types
    // whose definitions are consistent across machines and independent
    // of operating systems and other implementation idiosyncrasies.
    // It defines, via typedef, integer types of various sizes.
    // Implementations are free to typedef them as ISO C standard integer
    // types or extensions that they support. Consistent use of this
    // header will greatly increase the portability of
    // applications across platforms.

    //############ Macros para print ############

    //----Decimal con signo en n-bits-----
    PRId8 PRIdLEAST8 PRIdFAST8
    PRId16 PRIdLEAST16 PRIdFAST16
    PRId32 PRIdLEAST32 PRIdFAST32
    PRId64 PRIdLEAST64 PRIdFAST64

    PRIi8 PRIiLEAST8 PRIiFAST8
    PRIi16 PRIiLEAST16 PRIiFAST16
    PRIi32 PRIiLEAST32 PRIiFAST32
    PRIi64 PRIiLEAST64 PRIiFAST64
    //------------------------------------

    //----Decimal sin signo en n-bits-----
    PRIu8 PRIuLEAST8 PRIuFAST8
    PRIu16 PRIuLEAST16 PRIuFAST16
    PRIu32 PRIuLEAST32 PRIuFAST32
    PRIu64 PRIuLEAST64 PRIuFAST64
    //------------------------------------

    //----Octal en n-bits-----------------
    PRIo8 PRIoLEAST8 PRIoFAST8
    PRIo16 PRIoLEAST16 PRIoFAST16
    PRIo32 PRIoLEAST32 PRIoFAST32
    PRIo64 PRIoLEAST64 PRIoFAST64
    //------------------------------------

    //----Hexa minuscula en n-bits--------
    PRIx8 PRIxLEAST8 PRIxFAST8
    PRIx16 PRIxLEAST16 PRIxFAST16
    PRIx32 PRIxLEAST32 PRIxFAST32
    PRIx64 PRIxLEAST64 PRIxFAST64
    //----Hexa mayuscula en n-bits--------
    PRIX8 PRIXLEAST8 PRIXFAST8
    PRIX16 PRIXLEAST16 PRIXFAST16
    PRIX32 PRIXLEAST32 PRIXFAST32
    PRIX64 PRIXLEAST64 PRIXFAST64
    //------------------------------------

    //----Formato para u/intmax_t en diferentes bases--------
    PRIdMAX PRIiMAX     // Decimal con signo
    PRIuMAX             // Decimal sin signo
    PRIoMAX             // Octal
    PRIxMAX             // Hexa minuscula
    PRIXMAX             // Hexa mayuscula
    //-------------------------------------------------------

    //----Formato para u/intptr_t en diferentes bases--------
    PRIdPTR PRIiPTR     // Decimal con signo
    PRIuPTR             // Decimal sin signo
    PRIoPTR             // Octal
    PRIxPTR             // Hexa minuscula
    PRIXPTR             // Hexa mayuscula
    //-------------------------------------------------------

    //############ Macros para scan ############

    //----Decimal con signo en n-bits-----
    SCNd8 SCNdLEAST8 SCNdFAST8
    SCNd16 SCNdLEAST16 SCNdFAST16
    SCNd32 SCNdLEAST32 SCNdFAST32
    SCNd64 SCNdLEAST64 SCNdFAST64

    SCNi8 SCNiLEAST8 SCNiFAST8
    SCNi16 SCNiLEAST16 SCNiFAST16
    SCNi32 SCNiLEAST32 SCNiFAST32
    SCNi64 SCNiLEAST64 SCNiFAST64
    //------------------------------------

    //----Decimal sin signo en n-bits-----
    SCNu8 SCNuLEAST8 SCNuFAST8
    SCNu16 SCNuLEAST16 SCNuFAST16
    SCNu32 SCNuLEAST32 SCNuFAST32
    SCNu64 SCNuLEAST64 SCNuFAST64
    //------------------------------------

    //----Octal en n-bits-----------------
    SCNo8 SCNoLEAST8 SCNoFAST8
    SCNo16 SCNoLEAST16 SCNoFAST16
    SCNo32 SCNoLEAST32 SCNoFAST32
    SCNo64 SCNoLEAST64 SCNoFAST64
    //------------------------------------

    //----Hexa minuscula en n-bits--------
    SCNx8 SCNxLEAST8 SCNxFAST8
    SCNx16 SCNxLEAST16 SCNxFAST16
    SCNx32 SCNxLEAST32 SCNxFAST32
    SCNx64 SCNxLEAST64 SCNxFAST64
    //------------------------------------

    //----Formato para u/intmax_t en diferentes bases--------
    SCNdMAX SCNiMAX     // Decimal con signo
    SCNuMAX             // Decimal sin signo
    SCNoMAX             // Octal
    SCNxMAX             // Hexa minuscula
    //-------------------------------------------------------

    //----Formato para u/intptr_t en diferentes bases--------
    SCNdPTR SCNiPTR     // Decimal con signo
    SCNuPTR             // Decimal sin signo
    SCNoPTR             // Octal
    SCNxPTR             // Hexa minuscula
    //-------------------------------------------------------

/******************************************************************/
}

#endif    // Entendiendo C

/* -------------------------------------------------------------------------- */
/*                        Interactuando con el usuario                        */
/* -------------------------------------------------------------------------- */

#if N_Ejercicio == 50

#include <complex.h>
#include <math.h>
#include <stdlib.h>

int main(void) {

    char buffer[100];
    char *errPtr = NULL;

    printf("Ingrese un numero real. Se calculara la raiz e inverso del mismo.\n");

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        float n = strtof(buffer, &errPtr);

        if (errPtr == buffer || *errPtr != '\n') {

            printf("Ingrese un numero valido. Intentelo nuevamente.\n");
        } else {

            if (n < 0) {
                printf("El inverso es: %.2f\n", 1 / n);
                double complex nC = n;
                double complex raizC = csqrt(nC);
                printf("La raiz compleja es: %.2f + %.2fi\n", creal(raizC), cimag(raizC));
            }

            else if (n == 0) {
                printf("El inverso no puede calcularse\n");
                printf("La raiz es 0.00\n");
            }

            else {
                printf("El inverso es: %.2f\n", 1 / n);
                printf("La raiz es: %.2f\n", sqrt(n));
            }
        }

        printf("Ingrese un numero real. Se calculara la raiz e inverso del mismo.\n");
    }

    return 0;
}

#elif N_Ejercicio == 51

#include <stdlib.h>

int main(void) {

    char buffer[100];
    char *errPtr = NULL;

    enum semana {
        DOMINGO = 1,
        LUNES,
        MARTES,
        MIERCOLES,
        JUEVES,
        VIERNES,
        SABADO,
    };

    const char *tablaDias[] = {
        [DOMINGO] = "Domingo",
        [LUNES] = "Lunes",
        [MARTES] = "Martes",
        [MIERCOLES] = "Miercoles",
        [JUEVES] = "Jueves",
        [VIERNES] = "Viernes",
        [SABADO] = "Sabado",
    };

    printf("Ingrese un dia entre [1 - 366]:\n");

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        int i = strtol(buffer, &errPtr, 10);

        if (errPtr == buffer || *errPtr != '\n') {
            printf("La fecha ingresada esta por fuera de los limites [1-366] o no es una entrada valida. Vuelva a intentarlo.\n");
        } else {
            printf("El dia %d es %s\n", i, tablaDias[!(i % 7) ? 7 : i % 7]);
        }

        printf("Ingrese un dia entre [1 - 366]:\n");
    }

    return 0;
}

#elif N_Ejercicio == 52

#include <stdlib.h>

int main(void) {

    char buffer[100];
    char *errPtr = NULL;

    printf("Ingrese una cantidad de segundos:\n");

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        int i = strtol(buffer, &errPtr, 10);

        if (errPtr == buffer || *errPtr != '\n') {
            printf("La cantidad de segundos ingresada esta por fuera de los limites [0-inf] o no es una entrada valida. Vuelva a intentarlo.\n");
        } else {
            unsigned int horas = i / 3600;
            unsigned int minutos = (i - horas * 3600) / 60;
            unsigned int segundos = i - (horas * 3600 + minutos * 60);
            printf("Horas: %d Minutos: %d Segundos: %d\n", horas, minutos, segundos);
        }

        printf("Ingrese una cantidad de segundos:\n");
    }

    return 0;
}

#elif N_Ejercicio == 53

int main(void) {

    unsigned int lineas = 0;
    char c = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n')
            lineas++;
    }

    printf("%u\n", lineas);

    return 0;
}

#elif N_Ejercicio == 54

int main(void) {

    printf("Ingrese texto: ");

    unsigned int contador_espacio = 0;
    unsigned int contador_tab = 0;
    unsigned int contador_newline = 0;
    unsigned int contador_letras = 0;

    char c = '\0';

    while (c != EOF) {

        c = getchar();

        switch (c) {

        case ' ':
            contador_espacio++;
            break;

        case '\t':
            contador_tab++;
            break;

        case '\n':
            contador_newline++;
            break;

        default:

            if ('A' <= c && c <= 'z') {
                contador_letras++;
            }
            break;
        }
    }

    printf("%u Espacios %u Tabulaciones %u Lineas %u Letras\n", contador_espacio, contador_tab, contador_newline, contador_letras);

    return 0;
}

#elif N_Ejercicio == 55

#define Version 1

#include <stdlib.h>

int main(void) {

#if Version == 1
    int contador = 0;
#elif Version == 2
    unsigned int contador = 0;
#endif

    float max = 0;
    float min = 0;
    float numero_inicio = 0;
    char buffer[20];

#if Version == 1

    char *cPtr = NULL;

    do {

        printf("Ingrese un numero: \n");

        cPtr = fgets(buffer, sizeof(buffer), stdin);

        float aux = atof(buffer);

        if (aux && cPtr != NULL) {

            numero_inicio += aux;

            if (aux > max || !contador) {
                max = aux;
            }

            if (aux < min || !contador) {
                min = aux;
            }

            contador++;
        }

    } while (cPtr != NULL);

    printf("--  %d  %f--\n", contador, numero_inicio);

#elif Version == 2

    printf("Ingrese un numero: ");

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        printf("Ingrese un numero: ");

        float aux = atof(buffer);

        if (aux) {

            numero_inicio += aux;

            if (aux > max || !contador) {
                max = aux;
            }

            if (aux < min || !contador) {
                min = aux;
            }

            contador++;
        }
    }

#else

    size_t contador = 0;

    printf("Ingrese un numero: ");

    for (contador = 0; fgets(buffer, sizeof(buffer), stdin) != NULL; contador++) {

        printf("Ingrese un numero: ");

        float aux = atof(buffer);

        if (aux) {

            numero_inicio += aux;

            if (aux > max || !contador) {
                max = aux;
            }

            if (aux < min || !contador) {
                min = aux;
            }
        }
    }

#endif

    printf("El maximo es %1.3f\n El minimo es %1.3f\n El promedio es %1.3f\n ", max, min, numero_inicio / contador);

    return 0;
}

#elif N_Ejercicio == 56

#include <stdlib.h>

int main(void) {

    char buffer[256];

    int aprobados = 0;
    int desaprobados = 0;

    printf("Ingrese un nota valida [0 - 100]: ");

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        printf("Ingrese un nota valida [0 - 100]: ");

        int aux = atoi(buffer);

        if (aux >= 40 && aux <= 100)
            aprobados++;
        else if (aux >= 0 && aux < 40)
            desaprobados++;
        else
            break;
    }

    float porcentajeAprobado = (float)(aprobados * 100) / (aprobados + desaprobados);

    printf("Aprobados: %1.1f%%\n", porcentajeAprobado);

    if (porcentajeAprobado == 100)
        printf("Esto es raro\n");
    else if (porcentajeAprobado >= 80)
        printf("Muy bien\n");
    else if (porcentajeAprobado >= 60 && porcentajeAprobado < 80)
        printf("No esta mal\n");
    else if (porcentajeAprobado >= 40 && porcentajeAprobado < 60)
        printf("Algo no esta bien\n");
    else
        printf("Algo esta mal\n");

    return 0;
}

#elif N_Ejercicio == 57

#include <stdlib.h>

int main(void) {

    char buffer[256];

    int aprobados = 0;
    int desaprobados = 0;
    unsigned int cantidadNotas = 0;

    printf("Ingrese la cantidad de notas que desea computar\n");

    for (size_t i = -1; (fgets(buffer, sizeof(buffer), stdin) != NULL) && (i != cantidadNotas - 1); i++) {

        if (cantidadNotas > 0) {

            printf("Ingrese una nota valida [0 - 100]: ");

            int aux = atoi(buffer);

            if (aux >= 40 && aux <= 100)
                aprobados++;
            else if (aux >= 0 && aux < 40)
                desaprobados++;
            else
                break;
        }

        else {

            if (atoi(buffer) > 0) {
                cantidadNotas = atoi(buffer);
                printf("Ingrese una nota valida [0 - 100]: ");
            }

            else {
                printf("Ingrese una cantidad de notas valida. Intente nuevamente\n");
                i--;
            }
        }
    }

    float porcentajeAprobado = (float)(aprobados * 100) / (aprobados + desaprobados);

    printf("Aprobados: %1.1f%%\n", porcentajeAprobado);

    if (porcentajeAprobado == 100)
        printf("Esto es raro\n");
    else if (porcentajeAprobado >= 80)
        printf("Muy bien\n");
    else if (porcentajeAprobado >= 60 && porcentajeAprobado < 80)
        printf("No esta mal\n");
    else if (porcentajeAprobado >= 40 && porcentajeAprobado < 60)
        printf("Algo no esta bien\n");
    else
        printf("Algo esta mal\n");

    return 0;
}

#elif N_Ejercicio == 58

#include <stdlib.h>

int main(void) {

    char buffer[100];
    char *errPtr = NULL;

    float min = 0.0f, max = 0.0f;

    printf("Indique el MINIMO valor del intervalo\n");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        min = strtof(buffer, &errPtr);

        if (errPtr == buffer || *errPtr != '\n')
            printf("La entrada de datos es invalida, intente nuevamente.\n");
        else
            break;
        printf("Indique el MINIMO valor del intervalo\n");
    }

    printf("Indique el MAXIMO valor del intervalo\n");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        max = strtof(buffer, &errPtr);

        if (errPtr == buffer || *errPtr != '\n')
            printf("La entrada de datos es invalida, intente nuevamente.\n");
        else
            break;
        printf("Indique el MAXIMO valor del intervalo\n");
    }

    unsigned int cNumFueraIntervalo = 0;
    unsigned int cNumEnIntervalo = 0;
    float minIngresado = 0;
    float maxIngresado = 0;

    printf("Ingrese un numero real. Recuerde que el 0 finaliza el programa.\n");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        float n = strtof(buffer, &errPtr);

        if (errPtr == buffer || *errPtr != '\n')
            printf("La entrada de datos es invalida, intente nuevamente.\n");
        else {

            if (!n)
                break;

            if (n < minIngresado || (!cNumEnIntervalo && !cNumFueraIntervalo))
                minIngresado = n;

            if (n > maxIngresado || (!cNumEnIntervalo && !cNumFueraIntervalo))
                maxIngresado = n;

            if (n >= min && n <= max)
                cNumEnIntervalo++;
            else
                cNumFueraIntervalo++;
        }
        printf("Ingrese un numero\n");
    }

    printf("Cantidad de numeros ingresados: %d\n", cNumEnIntervalo + cNumFueraIntervalo);
    printf("Cantidad de numeros ingresados pertenecientes al intevalo [%.2f - %.2f]: %d\n", min, max, cNumEnIntervalo);
    printf("[ABS]: %d | [REL]: %d | [%%]: %.2f%%\n", cNumEnIntervalo, cNumEnIntervalo - cNumFueraIntervalo, cNumEnIntervalo * 100.0 / (!(cNumEnIntervalo + cNumFueraIntervalo) ? 1 : (cNumEnIntervalo + cNumFueraIntervalo)));
    printf("Los valores minimos y maximos ingresados son: %.2f %.2f\n", minIngresado, maxIngresado);

    return 0;
}

#elif N_Ejercicio == 59

#include <stdlib.h>

int main(void) {

    char buffer[256];
    char *errPtr = NULL;

    float min = 0.0f, max = 0.0f;

    unsigned int muestras = 0;

    float kilometrosTotales = 0.0f;
    float costoTotal = 0.0f;
    float litrosTotales = 0.0f;

    printf("Ingrese los kilometros recorridos (-1 para terminar)\n");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {

        float n = strtof(buffer, &errPtr);

        if (errPtr == buffer || *errPtr != '\n' || n < -1) {
            printf("Los datos ingresados son invalidos. Intente nuevamente\n");
        }

        else {

            if (n == -1) {
                break;
            }
            kilometrosTotales += n;
            printf("Ingrese los kilometros recorridos (-1 para terminar): ");

            break;

        case MSG_L:
            printf("Ingrese el precio del combustible por litro: ");

            break;

        case MSG_PR:
            printf("Ingrese los kilometros recorridos (-1 para terminar): ");
            break;

        default:
            break;
        }
    }

    if (n < min || !muestras) {
        min = n;
    }
    if (n < max || !muestras) {
        max = n;
    }
}
}

int main(void) {

    char buffer[15];
    printf("Ingrese 12 numeros: ");

    float temp_mensuales[12] = {0};

    for (size_t i = 0; i < 12; i++) {
        printf("n%zu: ", i + 1);
        fgets(buffer, 15, stdin);

        char *endptr;
        float aux = strtof(buffer, &endptr);

        if (*endptr == '\0' || *endptr == '\n') {
            temp_mensuales[i] = aux;
        } else {
            i--;
            printf("\nEntrada invalida. Vuelve a intentarlo.\n");
        }
    }
    for (size_t i = 0; i < 12; i++) {
        printf("Los nummeros almacenados en el array son: %f\n ", temp_mensuales[i]);
    }

    return 0;
}

#endif    // Interactuando con el usuario
