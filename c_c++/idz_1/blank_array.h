//
// Created by ser on 10.10.2019.
//

#ifndef BLANK_ARRAY_H_
#define BLANK_ARRAY_H_

#include "blank.h"

typedef struct blank_array {
    Blank** array;
    size_t size;
} Blank_array;

Blank_array* new_blank_array(size_t n) {
    Blank_array* temp = (Blank_array *) calloc(1, sizeof(Blank_array));
    temp->size = n;
    temp->array = (Blank **) calloc(n, sizeof(Blank *));
    return temp;
};

void free_blank_array_full(Blank_array* blank_array) {
    if (!blank_array)
        return;
    for (size_t i = 0; i < blank_array->size; i++)
        if (blank_array->array[i])
            free(blank_array->array[i]);
    free(blank_array->array);
    free(blank_array);
}

void free_blank_array(Blank_array* blank_array) {
    if (!blank_array)
        return;
    free(blank_array->array);
    free(blank_array);
}

//  Get array of blanks from input
Blank_array* get_blanks(FILE* in, FILE* out) {
    check_and_print(out, "Enter number of blanks: ");
    size_t n = 0;
    fscanf(in, "%lu", &n);
    Blank_array* blanks = new_blank_array(n);
    if (!blanks) {
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        blanks->array[i] = get_blank(in, out);
        if (!blanks->array[i]) {
            free_blank_array(blanks);
            return NULL;
        }
    }

    return blanks;
}

#endif //  BLANK_ARRAY_H_
