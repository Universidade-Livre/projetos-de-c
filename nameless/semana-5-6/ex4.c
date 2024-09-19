#include <math.h>
#include <stdio.h>

int main() {
    int a, b, c;
    int delta;
    float result, result2;

    printf("Valor de a: ");
    scanf("%d", &a);

    printf("Valor de b: ");
    scanf("%d", &b);

    printf("Valor de c: ");
    scanf("%d", &c);

    delta = b * b - 4 * a * c;
    result = (-b + sqrtf(delta)) / (2 * a);
    result2 = (-b - sqrtf(delta)) / (2 * a);

    if (delta < 0) {
        printf("equação não possuí raízes reais");
    } else if (delta > 0) {
        printf("Valor positivo %f e valor negativo %f\n", result, result2);
    } else {
        if (result == result2) {
            printf("Os dois valores são iguais, o resultado é: %f", result);
        }
    }
}