/* -----------------------------------------------------------------------------
 * # Exercício 1
 * Criar uma função is_even, usando operadores bitwise, que retorna 1 quando o
 * parâmetro for par, e retorna 0 quando o parâmetro for ímpar.
----------------------------------------------------------------------------- */

#include <stdio.h>

int is_even(int n);

int main(void) {
    int n = -31;
    printf("O número %d é %s\n", n, is_even(n) ? "par" : "ímpar");
    return 0;
}

int is_even(int n) {
    return (n & 1) ^ 1;
}
