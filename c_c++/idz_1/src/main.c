/*
Copyright 2019 Сергей Меликян АПО-12
    Создать структуру для хранения информации 
    о бланках строгой отчетности: их номерах,
    месте хранения, ответственном и т.д.
    Составить с ее использованием программу 
    разбиения всех бланков на пачки бланков с
    последовательными номерами (без пропусков),
    единым местом хранения и ответственным.
*/
#include "../include/blank_pack.h"
#include <getopt.h>

int main(int argc, char** argv) {
    FILE* in = stdin;
    FILE* out = stdout;

    int opt = 0;
    char *opts = "i:o:h", *i = NULL, *o = NULL;
    while ((opt = getopt(argc, argv, opts)) != -1) {
        switch (opt) {
            case 'i':
                i = &optarg[0];
                break;
            case 'o':
                o = &optarg[0];
                break;
            case 'h':
                printf("Usage: %s [-i]: input file, don`t pass if want stdin, ", argv[0]);
                printf("[-o]: output file, don`t pass if want stdout\n");
                return 0;
            default:
                break;
        }
    }
    if (i)
        in = fopen(i, "r");
    if (o)
        out = fopen(o, "w");
    Blank_pack *packs = get_packs(in, out);
    if (!packs)
        return 1;
    print_packs(out, packs);
    free_blank_pack(packs);
    fclose(in);
    fclose(out);
    return 0;
}
