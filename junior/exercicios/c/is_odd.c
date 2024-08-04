#include <criterion/criterion.h>
#include <criterion/new/assert.h>

_Bool is_odd(int num);

Test(IsEven, is_odd)
{
    cr_expect(eq(int, is_odd(1), 1));
    cr_expect(eq(int, is_odd(2), 0));
    cr_expect(eq(int, is_odd(3), 1));
    cr_expect(eq(int, is_odd(4), 0));
    cr_expect(eq(int, is_odd(5), 1));
    cr_expect(eq(int, is_odd(6), 0));
}

_Bool is_odd(int num)
{
    return num & 1;
}
