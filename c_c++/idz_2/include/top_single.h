/*
Copyright 2019 Сергей Меликян АПО-12
*/

#ifndef _TOP_SINGLE_H
#define _TOP_SINGLE_H

typedef struct top {
    double avr_rate;
    unsigned obj_id;
} __attribute__ ((packed)) Top;

Top* get_top(Objects *objs, User *user, unsigned count);

#endif //  IDZ_2_TOP_SINGLE_H
