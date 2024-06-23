#include <criterion/criterion.h>
#include <criterion/new/assert.h>

float square_area(float size);
float hypotenuse(float height, float base);
float hypotenuse_square_area(float hypotenuse);
float triangle_area(float height, float base);

// Dado um triângulo com altura 6.0 e base 8.0, calcule os seguintes valores:
// Área do quadrado da altura
// Área do quadrado da base
// Hipotenusa
// Área do quadrado da hipotenusa
// Área do triângulo
Test(Aritmetica, pitagoras)
{
    float height = 6.0;
    float base = 8.0;

    cr_expect(epsilon_eq(flt, square_area(height), 36, 1), "Área do quadrado da altura deve ser 36");
    cr_expect(epsilon_eq(flt, square_area(base), 64, 1), "Área do quadrado da base deve ser 64");
    cr_expect(epsilon_eq(flt, hypotenuse(height, base), 10, 1), "Hipotenusa deve ter valor de 10");
    cr_expect(epsilon_eq(flt, hypotenuse_square_area(hypotenuse(height, base)), 100, 1), "Quadrado da hipotenusa deve ter valor de 100");
    cr_expect(epsilon_eq(flt, triangle_area(height, base), 24, 1), "Área do triângulo deve ser 24");

    cr_expect(epsilon_eq(flt, square_area(height), 36, 1), "Área do quadrado da altura deve ser 36");
    cr_expect(epsilon_eq(flt, square_area(base), 64, 1), "Área do quadrado da base deve ser 64");
    cr_expect(epsilon_eq(flt, hypotenuse(height, base), 10, 1), "Hipotenusa deve ter valor de 10");
    cr_expect(epsilon_eq(flt, hypotenuse_square_area(hypotenuse(height, base)), 100, 1), "Quadrado da hipotenusa deve ter valor de 100");
    cr_expect(epsilon_eq(flt, triangle_area(height, base), 24, 1), "Área do triângulo deve ser 24");
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

float hypotenuse_square_area(float hypotenuse)
{
    // implementação ...

    return 0.0;
}

float triangle_area(float height, float base)
{
    // implementação ...

    return 0.0;
}
