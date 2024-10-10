#include <stdio.h>
#include <math.h>

float bhaskara(int b, float delta, int a, int p)
{
	if (p)
		return (-b + sqrt(delta)) / (2 * a);
	return (-b - sqrt(delta)) / (2 * a);
}

int main() {
	int a, b, c;
	float delta;

	printf("Insira o valor 'a': ");
	scanf("%d", &a);

	printf("Insira o valor 'b': ");
	scanf("%d", &b);

	printf("Insira o valor 'c': ");
	scanf("%d", &c);

	delta = powf(b, 2) - (4 * a * c);

	if (delta < 0)
		puts("Esta equação não possuí raízes reais.");
	else if (delta == 0)
		printf("x = %f\n", bhaskara(b, delta, a, 1));
	else
		printf("x1 = %f\nx2 = %f\n", bhaskara(b, delta, a, 1),
		       bhaskara(b, delta, a, 0));

	return 0;
}
