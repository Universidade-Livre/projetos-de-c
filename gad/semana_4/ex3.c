#include <stdio.h>

char* paridade(int n)
{
	if (n & 0x1)
		return "IMPAR";
	return "PAR";
}

int main() {
	int j1, j2;

	printf("Jogador 1 (PAR): ");
	scanf("%d", &j1);

	printf("Jogador 2 (IMPAR): ");
	scanf("%d", &j2);

	puts(paridade(j1 + j2));

	return 0;
}
