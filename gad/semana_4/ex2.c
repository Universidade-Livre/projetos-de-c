#include <stdio.h>
#include <math.h>

int main() {
	float a, b, a2, b2, h, h2;

	printf("Altura: ");
	scanf("%f", &a);

	printf("Base: ");
	scanf("%f", &b);

	a2 = powf(a, 2);
	b2 = powf(b, 2);

	h2 = a2 + b2;
	h = sqrtf(2);

	printf("Área: %.2f\n", (b * a) / 2);

	printf("Tamanho da hipotenusa: %.2f\n", h);
	printf("Valor da área da Hipotenusa^2: %.2f\n", h2);
	printf("Valor da área da Altura^2: %.2f\n", a2);
	printf("Valor da área da Base^2: %.2f\n", b2);
	printf("Tamanho do triângulo: %.2f\n", (b * a) / 2);

	return 0;
}
