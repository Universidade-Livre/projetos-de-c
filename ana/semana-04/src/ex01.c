#include <stdio.h>

int main(void) {
    float s1, s2, s3;

    printf("Primeiro salário: ");
    scanf("%f", &s1);

    printf("Segundo salário: ");
    scanf("%f", &s2);

    printf("Terceiro salário: ");
    scanf("%f", &s3);
    
    printf("A média dos salários é: %.2f\n", (s1 + s2 + s3) / 3);

    return 0;
}
