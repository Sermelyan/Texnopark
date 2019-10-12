#include "blank_pack.h"

int main() {
    FILE* f = fopen("a.txt", "r");
    Blank_pack *packs = get_packs(f, stdout);
    if (!packs)
        return 1;
    print_packs(stdout, packs);
    free_blank_pack(packs);
    fclose(f);
    return 0;
}
