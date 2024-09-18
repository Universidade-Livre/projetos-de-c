#include <stdio.h>
#include <math.h>

int main(void) {
    float base, altura, hipo;
    float base2, altura2, hipo2;
    float area;

    printf("Comprimento da altura: ");
    scanf("%f", &altura);

    printf("Comprimento da base: ");
    scanf("%f", &base);

    base2 = base * base;
    altura2 = altura * altura;
    hipo2 = base2 + altura2;
    hipo = sqrtf(hipo2);
    area = base * altura / 2;

    printf("Comprimento da hipotenusa: %.4f\n", hipo);
    printf("Quadrado do comprimento da hipotenusa: %.4f\n", hipo2);
    printf("Quadrado do comprimento da altura: %.4f\n", altura2);
    printf("Quadrado do comprimento da base: %.4f\n", base2);
    printf("Área do triângulo: %.4f\n", area);

    return 0;
}
