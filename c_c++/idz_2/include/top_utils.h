/*
Copyright 2019 Сергей Меликян АПО-12
*/

#ifndef _TOP_UTILS_H
#define _TOP_UTILS_H

#include "utils.h"

typedef struct top {
    double avr_rate;
    unsigned obj_id;
} __attribute__ ((packed)) Top;

void sift_down(Top *arr, long i, unsigned size);
void make_heap(Top *arr, unsigned size);
Top extract_max(Top *arr, unsigned *size);
Top* find_top(Top * temp, unsigned size, unsigned count);
double get_average(const Object *obj);
void print_top(Top *top, unsigned size);
int bin_search(const unsigned *arr,
               unsigned first, unsigned right,
               unsigned element);

#endif //  _TOP_UTILS_H
