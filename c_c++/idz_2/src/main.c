//
// Created by ser on 19.10.2019.
//

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    User* u = calloc(1, sizeof(User));
    set_user(u, 1);
    printf("%lu\n", sizeof(User));
    for (unsigned k = 0; k < 10; k++) {
        add_marked_obj(u, k);
    }
    printf("size: %u, pointer: %u\n", u->mark_size, u->mark_ptr);
    for (size_t l = 0; l < u->mark_ptr; l++) {
        printf("\t%u\n", u->marked_obj[l]);
    }
    Object* o = create_object(0);
    Mark m;
    for (size_t i = 0; i < 100; i++) {
        m = i % 5 + 1;
        if (add_rate(o, m, i)) {
            perror("Adding error!\n");
            free_object(o);
            free_user(u);
            return 1;
        }
    }
    printf("size: %u, pointer: %u\n", o->rate_size, o->rate_ptr);
    for (size_t j = 0; j < o->rate_ptr; j++) {
        printf("rate #%u:\n", j);
        printf("\tuser id: %u\n", o->rating_array[j].user_id);
        printf("\tmark: %u\n", o->rating_array[j].mark);
    }
    free_object(o);
    free_user(u);
    free(u);
    return 0;
}
