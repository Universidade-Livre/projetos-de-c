#include <stdio.h>
#include <stdint.h>

// Exercícios:

// A função deve retornar 1 se o número passado por parâmetro for ímpar,
// caso contrário deve retornar 0. Esta função deve obrigatoriamente usar
// operadores bitwise para o teste.
int is_even(int number) {
	return number & 0x1;
}

// Esta função deve receber uma cor de 32 bits no formato BGRA e converter
// para o formato ARGB, semelhante a uma conversão Big-Endian/Little-Endian.
uint32_t to_argb(uint32_t color) {
	uint32_t B, G, R, A;

	B = (color & 0xFF000000) >> 24;
	G = (color & 0x00FF0000) >> 8;
	R = (color & 0x0000FF00) << 8;
	A = (color & 0x000000FF) << 24;

	return A|R|G|B;
}

int main(void) {
	printf("O número 55 é ímpar? %d \n", is_even(55));
	printf("O número 56 é ímpar? %d \n", is_even(56));

	uint32_t color_argb = to_argb(0x563412FF);
	printf("Cor convertida para o formato ARGB: %x \n", color_argb);

	return 0;
}
