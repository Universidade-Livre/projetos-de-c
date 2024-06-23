#include <criterion/criterion.h>
#include <criterion/new/assert.h>

int media_simples(int n1, int n2, int n3);

// Dado 3 valores, implemente uma função que retorna a média simples dos valores
Test(Aritmetica, media_simples)
{
    int res1 = media_simples(10, 10, 10);
    int res2 = media_simples(10, 20, 30);
    int res3 = media_simples(40, 40, 10);

    cr_expect(eq(int, res1, 10));
    cr_expect(eq(int, res2, 20));
    cr_expect(eq(int, res3, 30));
}

int media_simples(int n1, int n2, int n3)
{
    // implementação

    return 0;
}
