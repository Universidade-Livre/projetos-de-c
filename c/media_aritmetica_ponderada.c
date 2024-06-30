#include <criterion/criterion.h>
#include <criterion/new/assert.h>

float media_aritmetica_ponderada(float n1, int p1, float n2, int p2, float n3, int p3);

// Dado 3 números reais e 3 números inteiros (representando os pesos), implemente uma função que retorna a média aritmética ponderada entre os números reais.
/*
 A média aritmética ponderada é calculada dividindo o somatório dos produtos dos valores por seus respectivos pesos pela soma dos pesos. Por exemplo:
 Dado os seguintes números: 8, 9 e 7
 Dado os seguintes pesos: 1, 3 e 6
 A média ponderada seria a soma do produto de cada número pelo seu respectivo peso, dividido pela soma dos pesos:
 (8 . 1 + 9 . 3 + 7 . 6) / (1 + 3 + 6) = 7.7
*/
Test(Aritmetica, media_aritmetica_ponderada)
{
    float res1 = media_aritmetica_ponderada(8.0, 1, 9.0, 3, 7.0, 6);
    float res2 = media_aritmetica_ponderada(11.0, 3, 2.5, 4, 20.5, 1);

    cr_expect(ieee_ulp_eq(flt, res1, 7.70, 4));
    cr_expect(ieee_ulp_eq(flt, res2, 7.9375, 4));
}

float media_aritmetica_ponderada(float n1, int p1, float n2, int p2, float n3, int p3)
{
    // implementação

    return 0;
}
