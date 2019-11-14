//
// Created by ser on 10.10.2019.
//

#ifndef INCLUDE_BLANK_ARRAY_H_
#define INCLUDE_BLANK_ARRAY_H_

#include "blank.h"

typedef struct blank_array {
    Blank **array;
    size_t size;
} Blank_array;

Blank_array* new_blank_array(size_t n);
void free_blank_array_full(Blank_array *blank_array);
void free_blank_array(Blank_array *blank_array);
Blank_array* get_blanks(FILE *in, FILE *out);

#endif  //  INCLUDE_BLANK_ARRAY_H_
