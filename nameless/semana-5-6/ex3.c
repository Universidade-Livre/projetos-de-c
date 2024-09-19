#include <stdio.h>

int main() {
    int impar, par;
    printf("Valor da mão impar: ");
    scanf("%d", &impar);

    printf("Valor da mão par: ");
    scanf("%d", &par);

    if ((par + impar) & 1) {
        printf("Impar");
    } else {
        printf("Par");
    }
}