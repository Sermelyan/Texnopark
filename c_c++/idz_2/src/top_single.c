/*
Copyright 2019 Сергей Меликян АПО-12
*/

#include "utils.h"
#include "top_single.h"
#include <stdlib.h>
#include <stdio.h>

void sift_down(Top *arr, long i, unsigned size) {
    unsigned left = 2 * i + 1;
    unsigned right = 2 * i + 2;
    unsigned biggest = i;
    if(left < size && arr[left].avr_rate > arr[i].avr_rate)
        biggest = left;
    if(right < size && arr[right].avr_rate > arr[biggest].avr_rate)
        biggest = right;
    if(biggest != i) {
        Top temp = arr[i];
        arr[i] = arr[biggest];
        arr[biggest] = temp;
        sift_down(arr, biggest, size);
    }
}

void make_heap(Top *arr, unsigned size) {
    for (long i = size / 2 - 1; i >= 0; i--) {
        sift_down(arr, i, size);
    }
}

Top extract_max(Top *arr, unsigned size) {
    Top result = arr[0];
    arr[0] = arr[--size];
    sift_down(arr, 0, size);
    return result;
}

Top* find_top(Top * temp, unsigned size, unsigned count) {
    Top *t_top = calloc(count, sizeof(Top));
    if (!t_top)
        return NULL;

    make_heap(temp, size);

    for (unsigned i = 0; i < count; i++) {
        t_top[i] = extract_max(temp, size);
    }

    return t_top;
}

double get_average(const Object *obj) {
    unsigned i;
    unsigned size = obj->rate_ptr < 4 ? 0 : obj->rate_ptr - 3;
    double acc0 = 0;
    double acc1 = 0;
    double acc2 = 0;
    double acc3 = 0;

    Rate *a = obj->rating_array;

    for (i = 0; i < size; i+=4) {
        acc0 += a[i].mark;
        acc1 += a[i+1].mark;
        acc2 += a[i+2].mark;
        acc3 += a[i+3].mark;
    }
    size = obj->rate_ptr;
    while (i < size)
        acc0 += a[i++].mark;
    return (acc0 + acc1 + acc2 + acc3) / size;
}

Top* get_top(Objects *objs, User *user, unsigned count) {
    unsigned size = objs->size;
    Top *temp = calloc(size, sizeof(Top));
    if (!temp)
        return NULL;

    unsigned left = 0, right = user->mark_ptr;
    unsigned *u_arr = user->marked_obj;

    for (unsigned i = 0; i < size; i++) {
        unsigned id = objs->array[i].obj_id;
        temp[i].obj_id = id;
        long left_t = bin_search(u_arr, left, right, id);
        if (left_t != -1) {
            left = left_t;
            temp[i].avr_rate = -1;
            continue;
        }
        temp[i].avr_rate = objs->array[i].rate_ptr == 0 ? 0 : get_average(&(objs->array[i]));
    }

    Top *t_top = find_top(temp, size, count);
    free(temp);
    return t_top;
}
