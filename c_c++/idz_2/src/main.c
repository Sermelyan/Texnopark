//
// Created by ser on 19.10.2019.
//

#include "utils.h"
#include "top_single.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    Users *users = gen_users(5000000);
    Objects *objects = gen_objects(16000);
    if (make_random_rate(users, objects, 500000000)) {
        free_users(users);
        free_objects(objects);
        return 1;
    }
//    print_users(users);
//    print_objects(objects);
    printf("Starting find top\n");
    clock_t start = clock();

    Top *top = get_top(objects, &(users->array[0]), 10);

    double fin = (double)(clock() - start)/CLOCKS_PER_SEC;
    for (size_t i = 0; i < 10; i++) {
        printf("object id: %u\n", top[i].obj_id);
        printf("\taverage: %f\n", top[i].avr_rate);
    }
    printf("Time: %f\n", fin);
    free_users(users);
    free_objects(objects);
    free(top);
    return 0;
}
