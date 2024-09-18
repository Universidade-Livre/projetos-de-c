#include "petest.h"

bool petest_init(PEFILE *pe) {
    FILE *fstream = fopen(pe->filepath, "rb");
    if (!fstream)
        return false;

    pe->hdr_dos = malloc(sizeof *(pe->hdr_dos));
    if (!(pe->hdr_dos)) {
        fclose(fstream);
        return false;
    }

    fread(pe->hdr_dos, sizeof *(pe->hdr_dos), 1, fstream);

    fclose(fstream);
    return true;
}

void petest_deinit(PEFILE *pe) {
    if (pe->hdr_dos)
        free(pe->hdr_dos);
    return;
}

bool petest_is_pe(PEFILE *pe) {
    return pe->hdr_dos->e_magic == 0x5A4D;
}
