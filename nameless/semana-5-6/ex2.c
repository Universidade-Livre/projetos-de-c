#include <stdio.h>
#include <math.h>

int main() {
    float altura;
    float base;

    printf("informe a altura ");
    scanf("%f", &altura);

    printf("Informe a base ");
    scanf("%f", &base);

    printf("Valor do tamanho da hipotenusa: %f\n", sqrtf(base * base + altura * altura));
    printf("Valor da área do quadrado da hipotenusa: %f\n", base * base + altura * altura);
    printf("Valor da área do quadrado da altura: %f\n", altura * altura);
    printf("Valor da área do quadrado da base: %f\n", base * base);
    printf("Valor do tamanho do triangulo: %f\n", base * altura / 2);
}
