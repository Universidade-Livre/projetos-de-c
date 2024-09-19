#include <stdio.h>

void media(float x, float y, float z) {
    printf("Digite o primeiro salário ");
    scanf("%f", &x);

    printf("Digite o segundo salário ");
    scanf("%f", &y);

    printf("Digite o terceiro salário ");
    scanf("%f", &z);

    printf("O valor da média é: %2.0f", (x + y + z) / 3);
}

int main() {
    float salario = 0.0;
    float salario2 = 0.0;
    float salario3 = 0.0;

    media(salario, salario2, salario3);
}
