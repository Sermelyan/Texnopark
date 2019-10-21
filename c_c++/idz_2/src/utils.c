/*
Copyright 2019 Сергей Меликян АПО-12
*/

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

int make_random_rate(Users *u, Objects *o, unsigned count){
    if (count > MAX_RATE)
        return 1;

    srandom(time(NULL));

    unsigned u_size = u->size;
    unsigned o_size = o->size;
    User *u_arr = u->array;
    Object *o_arr = o->array;

    for (size_t i = 0; i < count; i++) {
        unsigned user = random() % u_size;
        unsigned object = random() % o_size;
        if (add_rate(&o_arr[object], random() % 5 + 1, user))
            return 1;
        if (add_marked_obj(&u_arr[user], object))
            return 1;
    }
    return 0;
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
