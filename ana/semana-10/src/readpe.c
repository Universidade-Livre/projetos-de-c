#include <stdio.h>
#include <stdlib.h>
#include "../lib/petest.h"

void readpe_error(char *msg);

int main(int argc, char *argv[]) {
    PEFILE pe;

    if (argc != 2) {
        readpe_error("número de argumentos inválido\nUso: readpe <arquivo.exe>");
        exit(1);
    }

    pe.filepath = argv[1];
    if (!petest_init(&pe))
        readpe_error("não foi possível ler o arquivo");
    
    if (petest_is_pe(&pe)) {
        printf("É um arquivo PE! :)\n");
        printf("File: %s\n", pe.filepath);
        printf("MZ header: %X\n", pe.hdr_dos->e_magic);
        printf("COFF header offset: %X\n", pe.hdr_dos->e_lfanew);
    } else
        printf("Não é um arquivo PE! :(\n");

    petest_deinit(&pe);
    return 0;
}

void readpe_error(char *msg) {
    fprintf(stderr, "Erro: %s\n", msg);
    exit(1);
}
