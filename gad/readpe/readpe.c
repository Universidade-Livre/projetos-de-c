#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib/petest.h"

void usage(void);
void pr_fatal(char *msg);

void usage(void) {
	printf("uso: readpe <arquivo.exe>\n");
	exit(1);
}

void pr_fatal(char *msg) {
	fprintf(stderr, "ERRO: %s\n", msg);
	exit(1);
}

int main(int argc, char* argv[]) {
	if (argc != 2)
		usage();

	PEFILE pe;

	pe.filepath = argv[1];
	petest_init(&pe);

	if (petest_is_pe(&pe))
		printf("Arquivo reconhecido. continuando...\n");
	else
		pr_fatal("Arquivo não reconhecido.");

	printf("File:      %s\n", pe.filepath);
	printf("MZ header: %x\n", pe.hdr_dos->e_magic);
	printf("COFF header offset: %x\n", pe.hdr_dos->e_lfanew);

	petest_deinit(&pe);

	return 0;
}
