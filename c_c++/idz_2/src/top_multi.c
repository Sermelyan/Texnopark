/*
Copyright 2019 Сергей Меликян АПО-12
*/

#include "top_multi.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct args {
    unsigned count;
    unsigned u_right;
    unsigned o_right;
    unsigned *u_arr;
    Object *o_arr;
    Top *result;
    int error;
} Thr_args;

void free_arg(Thr_args *a, unsigned size) {
    for (unsigned i = 0; i < size; i++) {
        free(a[i].result);
    }
    free(a);
}

void* worker(void *args) {
    Thr_args *a = args;

    unsigned size = a->o_right;
    Top *temp = calloc(size, sizeof(Top));
    if (!temp) {
        a->error = 1;
        pthread_exit(NULL);
    }

    unsigned left = 0, right = a->u_right;
    unsigned *u_arr = a->u_arr;
    Object *objs = a->o_arr;

    for (unsigned i = 0; i < size; i++) {
        unsigned id = objs[i].obj_id;
        temp[i].obj_id = id;
        long left_t = bin_search(u_arr, left, right, id);
        if (left_t != -1) {
            left = left_t;
            temp[i].avr_rate = -1;
            continue;
        }
        temp[i].avr_rate = objs[i].rate_ptr != 0 ? get_average(&(objs[i])) : 0;
    }

    a->result = find_top(temp, size, a->count);
    free(temp);
    a->error = a->result ? 0 : 1;
    pthread_exit(NULL);
}

Top* prepare_answer(Thr_args *t, unsigned size) {
    unsigned count = t[0].count;
    Top *temp = calloc(size*count, sizeof(Top));
    if (size == 1) {
        return memcpy(temp, t[0].result, count*sizeof(Top));
    }

    for (unsigned i = 0 , j = 0; i < size; i++, j += count) {
        memcpy(&temp[j], t[i].result, count*sizeof(Top));
    }
    Top *ret =  find_top(temp, size*count, count);
    free(temp);
    return ret;
}

Top* get_top(Objects *objs, User *user, unsigned count) {
    unsigned o_size = objs->size;
    if (count > o_size)
        return NULL;
    unsigned max_thr = (o_size / count > count) ? count : 1;
    pthread_t thr[max_thr];
    int errflag = 0;
    unsigned size = o_size / max_thr;

    Thr_args *t = calloc(max_thr, sizeof(Thr_args));

    for (unsigned i = 0, ptr = 0; i < max_thr; i++, ptr += size) {
        t[i].u_arr = user->marked_obj;
        t[i].u_right = user->mark_ptr;
        t[i].count = count;
        t[i].o_arr = &(objs->array[ptr]);
        if (i < count - 1) {
            t[i].o_right = size;
        } else {
            t[i].o_right = o_size - ptr;
        }
        errflag = pthread_create(&(thr[i]), NULL, worker, (void *) &(t[i])) ? 1 : 0;
        if (errflag) {
            for (unsigned j = 0; j < i; j++) {
                pthread_cancel(thr[j]);
            }
            return NULL;
        }
    }

    for (unsigned j = 0; j < max_thr; j++) {
        pthread_join(thr[j], NULL);
        errflag = errflag || t[j].error;
        if (errflag) {
            free_arg(t, max_thr);
            return NULL;
        }
    }

    Top *ret =  prepare_answer(t, max_thr);
    free_arg(t, max_thr);
    return ret;
}
