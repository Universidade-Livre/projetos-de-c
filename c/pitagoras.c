#include <criterion/criterion.h>
#include <criterion/new/assert.h>

float square_area(float size);
float hypotenuse(float height, float base);
float triangle_area(float height, float base);

/*
 Dado dois triângulos com alturas 8.0 e 6.0 e base 6.0 e 12.0, implemente funções que calculam:
 O valor da hipotenusa desses triângulos
 O valor da área do quadrado da hipotenusa
 O valor da área do quadrado da altura do triângulo
 O valor da área do quadrado da base do triângulo
 O valor da área do triângulo

 Fórmulas:
    Teorema de pitágoras: a² = b² + c²
    Área de um triângulo: (altura * base) / 2
*/
Test(Aritmetica, pitagoras)
{
    float height = 8.0;
    float base = 6.0;
    float height2 = 12.0;
    float base2= 10.0;

    cr_expect(ieee_ulp_eq(flt, hypotenuse(height, base), 10, 4));
    cr_expect(ieee_ulp_eq(flt, square_area(hypotenuse(height, base)), 100, 4));
    cr_expect(ieee_ulp_eq(flt, square_area(height), 36, 4));
    cr_expect(ieee_ulp_eq(flt, square_area(base), 64, 4));
    cr_expect(ieee_ulp_eq(flt, triangle_area(height, base), 24, 4));

    cr_expect(ieee_ulp_eq(flt, hypotenuse(height2, base2), 15.620499351813308, 4));
    cr_expect(ieee_ulp_eq(flt, square_area(hypotenuse(height2, base2)), 244, 4));
    cr_expect(ieee_ulp_eq(flt, square_area(height2), 100, 4));
    cr_expect(ieee_ulp_eq(flt, square_area(base2), 144, 4));
    cr_expect(ieee_ulp_eq(flt, triangle_area(height2, base2), 60, 4));
}

float square_area(float size)
{
    // implementação ...

    return 0.0;
}

float hypotenuse(float height, float base)
{
    // implementação ...

    return 0.0;
}

float triangle_area(float height, float base)
{
    // implementação ...

    return 0.0;
}
