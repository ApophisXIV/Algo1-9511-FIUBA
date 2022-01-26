#include <stdio.h>

static char _rot47_encoder(const char c) {

    if (c < 33 || c > 126)
        return c;

    return c + 47 > 126 ? c - 47 : c + 47;
}

void rot47_str_encoder(const char *str) {
    for (size_t i = 0; str[i] != 0; printf("%c", _rot47_encoder(str[i++])));
}

int main(int argc, const char *argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Uso: ./ej3 The Quick Brown Fox Jumps Over The Lazy Dog.\n");
        return 1;
    }

    for (size_t i = 1; i < argc; rot47_str_encoder(argv[i++])){
        putchar(' ');
    }

    return 0;
}

// 17 min