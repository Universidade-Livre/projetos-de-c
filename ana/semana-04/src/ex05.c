#include <stdio.h>

int main(void) {
    int min = 0;
    int max = 100;
    int chute;
    char input;

    printf("Escolha um número entre 0 e 100\n");

    while (min <= max) {
        chute = (min + max) >> 1;

        printf("O número que você escolheu é %d?\n", chute);
        printf("(s: sim, M: maior, m: menor)\n");
        input = getchar();
        getchar();

        if (input == 's') {
            printf("Parabéns! Tirou 10! ^-^\n");
            break;
        } else if (input == 'M')
            min = chute + 1;
        else if (input == 'm')
            max = chute - 1;
        else
            printf("Erro: resposta diferente de 's', 'M' e 'm'\n");
    }

    if (min > max)
        printf("Parabéns! Você quebrou o código kkkkkk\n");

    return 0;
}
