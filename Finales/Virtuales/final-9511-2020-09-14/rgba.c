#include "rgba.h"

rgba_t rgba(const componente_t r, const componente_t g, const componente_t b, const componente_t a){
    return r << 24 | g << 16 | b << 8 | a;
}

componente_t rgba_r(const rgba_t rgba){
    return rgba >> 24;
}

componente_t rgba_g(const rgba_t rgba){
    return rgba >> 16;
}

componente_t rgba_b(const rgba_t rgba){
    return rgba >> 8;
}

componente_t rgba_a(const rgba_t rgba){
    return rgba & 0xFF;
}

