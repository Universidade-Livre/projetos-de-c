#include <criterion/criterion.h>
#include <criterion/new/assert.h>

char *even_or_odd(int n1, int n2);

/*
    Entrada:
    - Valor int da mão do jogador ímpar
    - Valor int da mão do jogador par

    Saída:
    - Mensagem dizendo "PAR" ou "ÍMPAR"

    Exemplo:
        primeiro valor: 2
        segundo valor: 5
        saída: "ÍMPAR"
*/
Test(Aritmetica, par_ou_impar)
{
    int n1 = 3;
    int n2 = 4;
    int n3 = 230;
    int n4 = 482;

    cr_expect(eq(chr[6], even_or_odd(n1, n2), "ÍMPAR"));
    cr_expect(eq(chr[4],even_or_odd(n3, n4), "PAR"));
}

char *even_or_odd(int n1, int n2)
{
    // implementação ...

    return "errado";
}
