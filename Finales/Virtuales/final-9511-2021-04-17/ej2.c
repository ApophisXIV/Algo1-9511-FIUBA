#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Valor Caracter  Valor Caracter  Valor Caracter  Valor Caracter
//     0 A             9 J            18 S            27 3
//     1 B            10 K            19 T            28 4
//     2 C            11 L            20 U            29 5
//     3 D            12 M            21 V            30 6
//     4 E            13 N            22 W            31 7
//     5 F            14 O            23 X
//     6 G            15 P            24 Y
//     7 H            16 Q            25 Z
//     8 I            17 R            26 2

#define MASK_CHUNK 0x1F
#define MASK_LAST_2BIT 0x03
#define CHUNK_SIZE 5
#define SHIFT_CHUNK 5
#define SHIFT_GAP 3

typedef struct {
    uint32_t hs;
    uint8_t ls;
} uint40_t;

/**
 * @brief  Imprime por consola en binario una variable de maximo 32 bits
 * @param  data: variable a imprimir
 * @param  n: numero de bits a imprimir
 * @param  chunk_size: tamaño de los chunks a imprimir
 * @retval None
 */
void print_bin(uint32_t data, size_t n, size_t chunk_size) {
    for (int i = n - 1; i >= 0; i--) {
        printf("%d", (data >> i) & 1);
        if (((n - i) % chunk_size) == 0)
            printf(" ");
    }
}

/**
 * @brief  Debug. Imprime en binario el valor de cada chunk con su respectiva letra
 * @param  *data: Puntero a la estructura de 40 bits
 * @param  s[9]: Array de caracteres para imprimir
 * @param  ec: Chunks vacios
 * @retval None
 */
void base32_debug_encoder(uint40_t *data, char s[9], size_t ec) {
    for (int i = 27, j = 0; i >= 2; i -= 5, j++) {
        printf("[%c] ", s[j]);
        print_bin((data->hs >> i) & MASK_CHUNK, SHIFT_CHUNK, CHUNK_SIZE);
    }
    printf("[%c] ", s[6]);
    print_bin((data->hs & MASK_CHUNK) << SHIFT_GAP | (data->ls >> SHIFT_CHUNK), SHIFT_CHUNK, CHUNK_SIZE);
    printf("[%c] ", s[7]);
    print_bin(data->ls & MASK_CHUNK, SHIFT_CHUNK, CHUNK_SIZE);

    printf(" | Chunks vacios: %zd\n", ec);
}

/**
 * @brief  Convierte la estructura de 40 bits en una cadena de caracteres en base 32.
 * @param  *serial_data: Puntero a la estructura de 40 bits
 * @param  s[9]: Array de caracteres para imprimir
 * @param  empty_chunks: Chunks vacios
 * @retval None
 */
void base32_encoder(uint40_t *serial_data, char s[9], size_t empty_chunks) {

    if (serial_data == NULL)
        return;

    static const char BASE32_ALPHABET_LUT[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

    // 30 Bits (HS)
    for (int i = 27, j = 0; i >= 2; i -= 5, j++)
        s[j] = BASE32_ALPHABET_LUT[(serial_data->hs >> i) & MASK_CHUNK];

    // 2 Bits (HS) + 3 Bits (LS)
    s[6] = BASE32_ALPHABET_LUT[(serial_data->hs & MASK_LAST_2BIT) << SHIFT_GAP | (serial_data->ls >> CHUNK_SIZE)];

    // 5 Bits (LS)
    s[7] = BASE32_ALPHABET_LUT[(serial_data->ls & MASK_CHUNK)];

    for (size_t i = 0; i < empty_chunks; i++)
        s[7 - i] = '=';
    s[8] = '\0';

    base32_debug_encoder(serial_data, s, empty_chunks);
}

/**
 * @brief  Serializa un arreglo de bytes en una estructura de 40 bits.
 * @note   Siempre tomara los primeros 5 bytes del arreglo. Si el arreglo es menor a 5 bytes, se completará con 0.
 * @param  data[]: Arreglo de bytes
 * @param  n: Cantidad de bytes
 * @param  *serialized_data: Puntero a la estructura de 40 bits
 * @retval Chunks vacios
 */
size_t base32_serializer_40B(uint8_t data[], size_t n, uint40_t *serialized_data) {

    serialized_data->hs = 0;
    serialized_data->ls = 0;

    if (n == 0)
        return 0;

    size_t i = 0;
    for (; i < (n > 4 ? 4 : n); i++)
        serialized_data->hs |= (data[i] << (3 - i) * 8);
    if (n > 4) {
        serialized_data->ls = data[4];
        i++;
    }

    return 8 - (8.0 * i / 5.0);
}

/**
 * @brief  Codifica una cadena de caracteres en base 32.
 * @param  data[]: Buffer de caracteres a codificar
 * @param  len: Cantidad de caracteres
 * @param  s[]: Buffer de caracteres para almacenar la codificación.
 *              Minimamente debe tener 8 caracteres + 1 para el '\0'
 * @retval None
 */
void base32_codificar(uint8_t data[], size_t len, char s[]) {

    const size_t QTY_CHUNKS = len / 5 + (len % 5 ? 1 : 0);

    for (size_t i = 0; i < QTY_CHUNKS; i++) {
        uint40_t data_40B;
        size_t n = base32_serializer_40B(data + i * 5, len - i * 5, &data_40B);
        base32_encoder(&data_40B, s + i * 8, n);
    }
}

int main(void) {
    uint8_t bytes[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'W', '1'};
    char s[64];
    base32_codificar(bytes, sizeof(bytes), s);

    printf("Str: %s\n", s);
    assert(!strcmp(s, "IFBEGRCFIZDUQSKKJNLTC==="));

    printf("%s: OK\n", __FILE__);
    return 0;
}
