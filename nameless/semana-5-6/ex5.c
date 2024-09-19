// Forcei minha namorada a usar goto, mas ela passa bem. Não repitam o que eu fiz!

#include <stdio.h>

int main() {
    int min = 0;
    int max = 100;
    int chute;
    char input;

    printf("Pense em um número entre 0 e 100 e eu vou tentar adivinhar.\n");

    while (min <= max) {
        chute = (min + max) >> 1;

        printf("O número que você pensou é %d?\n", chute);
        printf("(s: sim, M: maior, m: menor)\n");
        input = getchar();
        getchar();

        switch (input) {
        case 's':
            printf("Adivinhei!");
            goto exit;
        case 'M':
            min = chute + 1;
            break;
        case 'm':
            max = chute - 1;
            break;
        default:
            printf("Erro: resposta diferente de 's', 'M' e 'm'\n");
            }
    }

    if (min > max) {
        printf("Algo deu errado. Tente novamente.\n");
    }
exit:
    return 0;
}