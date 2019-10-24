//
// Created by ser on 19.10.2019.
//

#include "utils.h"
// #include "top_single.h"
#include "top_multi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    Users *users = gen_users(5000);
    Objects *objects = gen_objects(1600);

    clock_t start0 = clock();
    if (make_random_rate(users, objects, 500000, 6)) {
        free_users(users);
        free_objects(objects);
        return 1;
    }
    double fin0 = (double)(clock() - start0)/CLOCKS_PER_SEC/6;
//    print_users(users);
//    print_objects(objects);
    printf("Time: %f\n", fin0);
    printf("Starting find top\n");
    clock_t start = clock();

    Top *top = get_top(objects, &(users->array[0]), 100);

    double fin = (double)(clock() - start)/CLOCKS_PER_SEC/8;
    printf("\n");
    for (size_t i = 0; i < 100; i++) {
        printf("object id: %u\n", top[i].obj_id);
        printf("\taverage: %f\n", top[i].avr_rate);
    }
    printf("Time: %f\n", fin);
    free_users(users);
    free_objects(objects);
    free(top);
    return 0;
}
