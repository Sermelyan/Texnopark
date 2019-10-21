/*
Copyright 2019 Сергей Меликян АПО-12
*/

#include "user.h"
#include <stdlib.h>
#include <stdio.h>

void set_user(User* u, unsigned id) {
    u->user_id = id;
}

void free_user(User* user) {
    if (!user)
        return;
    if (user->marked_obj)
        free(user->marked_obj);
}

int add_marked_obj(User* usr,unsigned obj_id) {
    unsigned size = usr->mark_size;
    unsigned pointer = usr->mark_ptr;
    unsigned *array = usr->marked_obj;

    if (!size) {
        size = 2;
        unsigned *temp = calloc(size, sizeof(unsigned));
        if (!temp) {
            return 1;
        }
        array = temp;
    }

    if (size == pointer) {
        size = size * 2;
        unsigned *temp = realloc(array, size*sizeof(unsigned));
        if (!temp) {
            return 1;
        }
        array = temp;
    }

    array[pointer] = obj_id;

    usr->mark_ptr = pointer + 1;
    usr->mark_size = size;
    usr->marked_obj = array;
    return 0;
}

Users *create_users(unsigned size) {
    Users* temp = calloc(1, sizeof(Users));
    if (!temp)
        return NULL;
    temp->size = size;
    User *t_arr = calloc(size, sizeof(User));
    if (!t_arr){
        free(temp);
        return NULL;
    }
    temp->array = t_arr;
    return temp;
}

void print_users(Users *u) {
    for (size_t i = 0; i < u->size; i++) {
        printf("user id: %u ", u->array[i].user_id)
        printf("size: %u, pointer: %u\n", u->array[i].mark_size, u->array[i].mark_ptr);
        for (size_t j = 0; j < u->array[i].mark_ptr; j++) {
            printf("\t%u\n", u->array[i].marked_obj[j]);
        }
    }
}

void free_users(Users *users) {
    unsigned size = users->size;
    User *arr = users->array;
    for (size_t i = 0; i < size; i++) {
        free_user(&arr[i]);
    }
    free(arr);
    free(users);
}