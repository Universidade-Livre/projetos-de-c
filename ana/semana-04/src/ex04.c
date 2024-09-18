#include <stdio.h>
#include <math.h>

int main(void) {
    int a, b, c;
    int delta;
    float x1, x2;

    printf("Valor de a: ");
    scanf("%d", &a);

    printf("Valor de b: ");
    scanf("%d", &b);

    printf("Valor de c: ");
    scanf("%d", &c);

    delta = b * b - 4 * a * c;

    if (delta > 0) {
        x1 = (-b + sqrtf(delta)) / (2 * a);
        x2 = (-b - sqrtf(delta)) / (2 * a);
        printf("Soluções: %.4f, %.4f\n", x1, x2);
    } else if (delta == 0) {
        x1 = -b / (2 * a);
        printf("Solução: %.4f\n", x1);
    } else
        printf("A equação não possui raízes reais\n");

    return 0;
}
