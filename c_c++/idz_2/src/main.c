//
// Created by ser on 19.10.2019.
//

#include "utils.h"
#include "top_single.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() {
    Users *users = gen_users(500);
    if (!users) {
        perror("Cant get Users");
        return 1;
    }
    Objects *objects = gen_objects(160);
    if (!objects) {
        perror("Cant get Objects\n");
        free_users(users);
        return 1;
    }

    if (make_random_rate(users, objects, 5000, 2)) {
        free_users(users);
        free_objects(objects);
        return 1;
    }

    void *library;
    Top* (*get_top_multi)(const Objects *o, const User *u, unsigned c);
    library = dlopen("./libtop_multi.so", RTLD_LAZY);
    if (!library) {
        perror("Cant open lib\n");
        return 1;
    }
    get_top_multi = dlsym(library, "get_top");


    Top *top = get_top(objects, &(users->array[0]), 10);
    if (top) {
        free(top);
    } else {
        perror("Error on single get_top\n");
    }

    top = (*get_top_multi) (objects, &(users->array[0]), 10);
    if (top) {
        free(top);
    } else {
        perror("Error on multi get_top\n");
    }

    free_users(users);
    free_objects(objects);
    return 0;
}
