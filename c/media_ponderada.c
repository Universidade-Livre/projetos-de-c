#include <criterion/criterion.h>
#include <criterion/new/assert.h>

float media_ponderada(float n1, int p1, float n2, int p2, float n3, int p3);

// Dado 3 valores e 3 pesos, implemente uma função que retorna a média ponderada dos valores
Test(Aritmetica, media_ponderada)
{
    float res1 = media_ponderada(8.0, 1, 9.0, 3, 7.0, 6);
    float res2 = media_ponderada(11.0, 3, 2.5, 4, 20.5, 1);

    cr_expect(epsilon_eq(flt, res1, 7.70, 1));
    cr_expect(epsilon_eq(flt, res2, 7.9375, 1));
}

float media_ponderada(float n1, int p1, float n2, int p2, float n3, int p3)
{
    // implementação

    return 0.0;
}
