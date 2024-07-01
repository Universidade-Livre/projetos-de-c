#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <math.h>

int calc_delta(int a, int b, int c);
double *quadratic_equation(int a, int b, int c);

Test(Aritmetica, calc_delta)
{
    int a1 = 1;
    int b1 = -2;
    int c1 = 1;

    int a2 = 4;
    int b2 = 2;
    int c2 = -6;

    cr_expect(eq(int, calc_delta(a1, b1, c1), 0));
    cr_expect(eq(int, calc_delta(a2, b2, c2), 100));
}

Test(Aritmetica, equacao_quadratica_delta_zero)
{
    int a1 = 1;
    int b1 = -2;
    int c1 = 1;

    double *first_equation = quadratic_equation(a1, b1, c1);

    // possuí duas raízes iguais
    cr_expect(ieee_ulp_eq(dbl, first_equation[0], 1.0, 4));
    cr_expect(ieee_ulp_eq(dbl, first_equation[1], 1.0, 4));
}

Test(Aritmetica, equacao_quadratica_delta_positivo)
{
    int a1 = 4;
    int b1 = 2;
    int c1 = -6;

    double *first_equation = quadratic_equation(a1, b1, c1);

    // possuí duas raízes diferentes
    cr_expect(ieee_ulp_eq(dbl, first_equation[0], 1.0, 4));
    cr_expect(ieee_ulp_eq(dbl, first_equation[1], -1.5, 4));
}

Test(Aritmetica, equacao_quadratica_delta_negativo)
{
    int a1 = 1;
    int b1 = 3;
    int c1 = 6;

    double *first_equation = quadratic_equation(a1, b1, c1);

    // não possuí raízes reais
    cr_expect(ieee_ulp_eq(dbl, first_equation[0], '\0', 4));
    cr_expect(ieee_ulp_eq(dbl, first_equation[1], '\0', 4));
}

int calc_delta(int a, int b, int c)
{
    return (b * b) - 4 * (a * c);
}

double *quadratic_equation(int a, int b, int c)
{
    static double roots[2];
    int delta = calc_delta(a, b, c);

    if (delta < 0) {
        roots[0] = '\0';
        roots[1] = '\0';
    }
    else if (delta == 0)
    {
        roots[0] = (-b + sqrt(delta)) / (2 * a);
        roots[1] = (-b - sqrt(delta)) / (2 * a);
    }
    else
    {
        roots[0] = (-b + sqrt(delta)) / (2 * a);
        roots[1] = (-b - sqrt(delta)) / (2 * a); 
    }

    return roots;
}
