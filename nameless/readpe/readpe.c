#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib/petest.h"

void msg(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if (argc < 2)
        msg("readpe: executable [file ...]");

    PEFILE pe;

    pe.filepath =  argv[1];
    pe_init(&pe);
    if (pe_ispe(&pe))
      printf("Is a pe... continue");
    else
      msg("it's not... exit");

    printf("File: %s\n", pe.filepath);
    printf("MZ header: %x\n", pe.hdr_dos->e_magic);
    printf("COFF header offset: %x\n", pe.hdr_dos->e_lfanew);

    pe_deinit(&pe);

    return 0;
}

