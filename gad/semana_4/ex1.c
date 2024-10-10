#include <stdio.h>

int main() {
	float notas[3];

	printf("Nota 1: ");
	scanf("%f", &notas[0]);

	printf("Nota 2: ");
	scanf("%f", &notas[1]);

	printf("Nota 3: ");
	scanf("%f", &notas[2]);

	printf("Média: %.2f\n", (notas[0] + notas[1] + notas[2]) / 3);

	return 0;
}
