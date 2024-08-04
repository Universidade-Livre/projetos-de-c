#include <criterion/criterion.h>
#include <criterion/new/assert.h>

int fibonacci_sum(int num);

Test(Mat, fibonacci_sum)
{
    int result1 = fibonacci_sum(10);
    int result2 = fibonacci_sum(20);

    cr_expect(eq(int, result1, 55));
    cr_expect(eq(int, result2, 6765));
}

int fibonacci_sum(int num)
{
    if (num <= 1) return num;

    return fibonacci_sum(num - 1) + fibonacci_sum(num - 2);
}
