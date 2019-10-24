/*
Copyright 2019 Сергей Меликян АПО-12
*/

#ifndef _TOP_MULTI_H
#define _TOP_MULTI_H

#include "utils.h"

typedef struct top {
    double avr_rate;
    unsigned obj_id;
} __attribute__ ((packed)) Top;

Top* get_top(Objects *objs, User *user, unsigned count);

#endif //  _TOP_MULTI_H
