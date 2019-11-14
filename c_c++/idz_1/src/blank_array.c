/*
Copyright 2019 Сергей Меликян АПО-12
*/
#include "../include/blank_array.h"

Blank_array* new_blank_array(size_t n) {
    Blank_array *temp = calloc(1, sizeof(Blank_array));
    temp->size = n;
    temp->array = calloc(n, sizeof(Blank *));
    return temp;
}

void free_blank_array_full(Blank_array *blank_array) {
    if (!blank_array)
        return;
    for (size_t i = 0; i < blank_array->size; i++)
        if (blank_array->array[i])
            free(blank_array->array[i]);
    free(blank_array->array);
    free(blank_array);
}

void free_blank_array(Blank_array *blank_array) {
    if (!blank_array)
        return;
    free(blank_array->array);
    free(blank_array);
}

//  Get array of blanks from input
Blank_array* get_blanks(FILE *in, FILE *out) {
    check_and_print(in, "Enter number of blanks: ");
    unsigned long n = 0;
    fscanf(in, "%lu", &n);
    Blank_array *blanks = new_blank_array(n);
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
