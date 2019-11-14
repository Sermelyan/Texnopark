//
// Created by ser on 10.10.2019.
//

#ifndef INCLUDE_BLANK_PACK_H_
#define INCLUDE_BLANK_PACK_H_

#include "blank_array.h"

typedef struct blank_pack {
    Blank_array *blanks;
    struct blank_pack *next;
} Blank_pack;

Blank_pack* new_blank_pack(size_t n);
void free_blank_pack(Blank_pack *pack);
int is_less(Blank *left, Blank *right);
Blank** merge_sort(Blank **up, Blank **down,
                   size_t left, size_t right,
                   int compare(Blank *, Blank *));
size_t find_right(Blank **a, size_t left, size_t size);
Blank_pack* get_packs(FILE *in, FILE *out);
void print_packs(FILE *out, Blank_pack *packs);

#endif  //  INCLUDE_BLANK_PACK_H_
