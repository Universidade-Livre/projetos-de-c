#include <criterion/criterion.h>
#include <criterion/new/assert.h>

int media_aritmetica_simples(int n1, int n2, int n3);

// Dado 3 números inteiros, implemente uma função que retorna a média aritmética simples entre eles.

/*
    A Média Aritmética será chamada de Média Aritmética Simples quando for calculada como o quociente entre a soma de todos os valores do conjunto e o número de
    elementos que esse conjunto possui.
    Por exemplo:
    Em uma família, de quatro pessoas, a idade do pai é 40, da mãe é 36, do filho é 10 e da filha é 14. Então, qual é a média entre os valores relacionados?
    O primeiro passo é somar todos os valores, ou seja:
    40 + 36 + 14 + 10 = 100
    E agora dividir o resultado pelo número de elementos que esse conjunto possui, nesse caso pai, mãe, filho e filha são 4 elementos.
    100 / 4 = 25
*/
Test(Aritmetica, media_aritmetica_simples)
{
    int res1 = media_aritmetica_simples(10, 10, 10);
    int res2 = media_aritmetica_simples(10, 20, 30);
    int res3 = media_aritmetica_simples(43, 43, 13);

    cr_expect(eq(int, res1, 10));
    cr_expect(eq(int, res2, 20));
    cr_expect(eq(int, res3, 33));
}

int media_aritmetica_simples(int n1, int n2, int n3)
{
    // implementação

    return 0;
}
