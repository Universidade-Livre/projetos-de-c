#include <stdio.h>

int main(void) {
    int impar, par;

    printf("Jogador ímpar: ");
    scanf("%d", &impar);

    printf("Jogador par: ");
    scanf("%d", &par);

    if ((impar + par) & 1)
        printf("ÍMPAR\n");
    else
        printf("PAR\n");

    return 0;
}
