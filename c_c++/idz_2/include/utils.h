/*
Copyright 2019 Сергей Меликян АПО-12
*/

#ifndef UTILS_H_
#define UTILS_H_

#include "user.h"
#include "object.h"

Users* gen_users(unsigned size);
Objects* gen_objects(unsigned size);
int make_random_rate(Users *u, Objects *o, unsigned count);
// int make_random_rate(Users *u, Objects *o, unsigned count, unsigned max_thr);

void print_users(const Users *u);
void print_objects(const Objects *o);
int bin_search(const unsigned *arr,
              unsigned first, unsigned right,
              unsigned element);

#endif //  UTILS_H_
