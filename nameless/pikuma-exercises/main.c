#include <stdio.h>
#include <stdint.h>

int is_even(int number) {
    return number & 1 ? 0 : 1;
}

uint32_t to_argb(uint32_t color) {
    uint32_t f = 0;
    f |= (color & 0x000000ff) << 24;
    f |= (color & 0x0000ff00) << 8;
    f |= (color & 0x00ff0000) >> 8;
    f |= (color & 0xff000000) >> 24;
    return f;
}

int main() {
    printf("O número 55 é ímpar? %d \n", is_even(55));
    uint32_t color_argb = to_argb(0x563412FF);
    printf("Cor convertida para o formato ARGB: %x \n", color_argb);
    return 0;
}
