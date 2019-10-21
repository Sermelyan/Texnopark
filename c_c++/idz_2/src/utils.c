/*
Copyright 2019 Сергей Меликян АПО-12
*/

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#define MAX_USR 50000000
#define MAX_OBJ 25000
#define MAX_RATE 750000000

Users* gen_users(unsigned size) {
    if (size > MAX_USR)
        return NULL;
    Users *temp =  create_users(size);
    User *arr = temp->array;
    for (size_t i = 0; i < size; i++) {
        arr[i].user_id = i;
    }
    return temp;
}

Objects* gen_objects(unsigned size){
    if (size > MAX_OBJ)
        return NULL;
    Objects *temp =  create_objects(size);
    Object *arr = temp->array;
    for (size_t i = 0; i < size; i++) {
        arr[i].obj_id = i;
    }
    return temp;
}

//int make_random_rate(Users *u, Objects *o, unsigned count){
//    if (count > MAX_RATE)
//        return 1;
//
//    srandom(time(NULL));
//
//    unsigned u_size = u->size;
//    unsigned o_size = o->size;
//    User *u_arr = u->array;
//    Object *o_arr = o->array;
//
//    for (size_t i = 0; i < count; i++) {
//        unsigned user = random() % u_size;
//        unsigned object = random() % o_size;
//        if (add_rate(&o_arr[object], random() % 5 + 1, user))
//            return 1;
//        if (add_marked_obj(&u_arr[user], object))
//            return 1;
//    }
//    return 0;
//}

typedef struct args {
    unsigned count;
    unsigned u_size;
    unsigned o_size;
    unsigned u_offset;
    unsigned o_offset;
    User *u_arr;
    Object *o_arr;
    int result;
} Thr_args;

void* worker(void* args){
    srandom(time(NULL));

    Thr_args *a = args;

    unsigned count = a->count;
    unsigned u_size = a->u_size;
    unsigned o_size = a->o_size;
    unsigned u_off = a->u_offset;
    unsigned o_off = a->o_offset;
    User *u_arr = a->u_arr;
    Object *o_arr = a->o_arr;

    for (size_t i = 0; i < count; i++) {
        unsigned user = random() % u_size + u_off;
        unsigned object = random() % o_size + o_off;
        if (add_rate(&o_arr[object - o_off], random() % 5 + 1, user)) {
            a->result = 1;
            pthread_exit(NULL);
        }
        if (add_marked_obj(&u_arr[user - u_off], object)) {
            a->result = 1;
            pthread_exit(NULL);
        }
    }
    a->result = 0;
    pthread_exit(NULL);
}

int make_random_rate(Users *u, Objects *o, unsigned count, unsigned max_thr) {
    pthread_t thr[max_thr];
    int errflag = 0;
    unsigned u_s = 0, o_s = 0, u_invl = u->size / max_thr, o_invl = o->size / max_thr;
    Thr_args *t = calloc(max_thr, sizeof(Thr_args));

    for (size_t i = 0; i < max_thr; i++) {
        t[i].u_arr = &(u->array[u_s]);
        t[i].o_arr = &(o->array[o_s]);
        t[i].u_offset = u_s;
        t[i].o_offset = o_s;
        if (i < max_thr - 1) {
            t[i].u_size = u_invl;
            u_s += u_invl;
            t[i].o_size = o_invl;
            o_s += o_invl;
            t[i].count = count / max_thr;
        } else {
            t[i].u_size = u->size - u_s;
            t[i].o_size = o->size - o_s;
            t[i].count = count - (count / max_thr) * (max_thr - 1);
        }
        errflag = pthread_create(&(thr[i]), NULL, worker, (void *) &(t[i])) ? 1 : 0;
    }
    if (errflag) {
        for (size_t i = 0; i < max_thr; i++) {
            pthread_cancel(thr[i]);
        }
        return 1;
    }
    errflag = 0;
    for (size_t j = 0; j < max_thr; j++) {
        pthread_join(thr[j], NULL);
        errflag = errflag || t[j].result;
    }
    free(t);
    return errflag;
}

void print_users(Users *u) {
    for (size_t i = 0; i < u->size; i++) {
        printf("user id: %u ", u->array[i].user_id);
        printf("size: %u, pointer: %u\n", u->array[i].mark_size, u->array[i].mark_ptr);
        for (size_t j = 0; j < u->array[i].mark_ptr; j++) {
            printf("\t%u\n", u->array[i].marked_obj[j]);
        }
    }
}

void print_objects(Objects *o) {
    for (size_t i = 0; i < o->size; i++) {
        printf("object id: %u ", o->array[i].obj_id);
        printf("size: %u, pointer: %u\n", o->array[i].rate_size, o->array[i].rate_ptr);
        for (size_t j = 0; j < o->array[i].rate_ptr; j++) {
            printf("rate #%u:\n", j);
            printf("\tuser id: %u\n", o->array[i].rating_array[j].user_id);
            printf("\tmark: %u\n", o->array[i].rating_array[j].mark);
        }
    }
}

//int binSearch(const Vector<int>& arr,
//            size_t first, size_t right,
//            int element) {
//    size_t last = right;
//    for (size_t mid = (first + last)/2;  first < last ; mid = (first + last)/2) {
//        if (arr[mid] < element)
//            first = mid +1;
//        else
//            last = mid;
//    }
//    return (first == right || arr[first] != element ) ? -1 : first;
//}
