/*
Copyright 2019 Сергей Меликян АПО-12
*/

#include "top_single.h"
#include <stdlib.h>

Top* get_top(const Objects *objs, const User *user, unsigned count) {
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
        temp[i].avr_rate = objs->array[i].rate_ptr != 0 ? get_average(&(objs->array[i])) : 0;
    }

    Top *t_top = find_top(temp, size, count);
    free(temp);
    return t_top;
}
