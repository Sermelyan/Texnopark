/*
Copyright 2019 Сергей Меликян АПО-12
*/

#ifndef UTILS_H_
#define UTILS_H_

#include "user.h"
#include "object.h"

Users* gen_users(unsigned size);
Objects* gen_objects(unsigned size);
int make_random_rate(Users *u, Objects *o, unsigned count, unsigned max_thr);

void print_users(Users *u);
void print_objects(Objects *o);

#endif //  UTILS_H_
