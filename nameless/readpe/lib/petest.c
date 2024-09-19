#include "petest.h"

bool pe_ispe(PEFILE *pe) {
    return (pe->hdr_dos->e_magic == 0x5a4d);
}

bool pe_init(PEFILE *pe) {
    FILE *file = fopen(pe->filepath, "rb");

    if (!file)
        return false;

    pe->hdr_dos = malloc(sizeof *(pe->hdr_dos));
    if (pe->hdr_dos == NULL)
        return false;

    fread(pe->hdr_dos, sizeof *(pe->hdr_dos), 1, file);

    fclose(file);

    return true;
}

void pe_deinit(PEFILE *pe) {
    if (pe->hdr_dos)
        free(pe->hdr_dos);
}
