//
// Created by ser on 19.10.2019.
//

#include "utils.h"

int main() {
    Users *users = gen_users(5000000);
    Objects *objects = gen_objects(16000);
    if (make_random_rate(users, objects, 500000000, 1)) {
        free_users(users);
        free_objects(objects);
        return 1;
    }
//    print_users(users);
//    print_objects(objects);
    free_users(users);
    free_objects(objects);
    return 0;
}
