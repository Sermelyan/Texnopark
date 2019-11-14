/*
Copyright 2019 Сергей Меликян АПО-12
*/

#ifndef USER_H_
#define USER_H_

typedef struct user {
    unsigned user_id;
    unsigned mark_size;
    unsigned mark_ptr;
    unsigned *marked_obj;
} __attribute__ ((packed)) User;

void free_user(User* user);
int add_marked_obj(User* usr,unsigned obj_id);

typedef struct user_array {
    User *array;
    unsigned size;
} Users;

Users *create_users(unsigned size);
void free_users(Users *users);

#endif //  USER_H_
