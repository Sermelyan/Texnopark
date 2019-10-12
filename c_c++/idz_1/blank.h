//
// Created by ser on 10.10.2019.
//

#ifndef BLANK_H_
#define BLANK_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

#define MAXSTR 256
#define check_and_print(out, str)\
        if (out == stdout) {\
            printf("%s", str);\
        }

typedef struct blank_struct {
    unsigned long number;
    char storage_place[MAXSTR];
    char responsible_name[MAXSTR];
    char responsible_surname[MAXSTR];
} Blank;

Blank* new_blank(void) {
    return (Blank *) calloc(1, sizeof(Blank));
}

//  Return 1 if string is broken else 0
int check_string(const char *str) {
    size_t str_len = 0;
    while (str[str_len] != '\0' && str_len < MAXSTR) {
        int c = str[str_len++];
        if (!isprint(c)) {
            return 1;
        }
    }

    if (0 == str_len)
        return 1;
    return  0;
}

//  Return 1 if blank is broken else 0
int check_blank(Blank* blank) {
    if (!blank)
        return 1;
    if (blank->number == ULONG_MAX)
        return 1;
    if (check_string(blank->storage_place))
        return 1;
    if (check_string(blank->responsible_name))
        return 1;
    if (check_string(blank->responsible_surname))
        return 1;
    return 0;
}

//  Get string from file descriptor. Separator is ;
void get_string(FILE* in, char* str) {
    int c = fgetc(in);
    while (isspace(c))
        c = fgetc(in);
    for (size_t i = 0;
         c != ';' && c != '\n' && c != EOF && i < MAXSTR - 1;
         c = fgetc(in), i++) {
        str[i] = (char) c;
    }
}

//  Gen blank from from input. If output is stdout write help messages
Blank* get_blank(FILE* in, FILE* out) {
    Blank* temp = new_blank();
    if (!temp)
        return NULL;

    check_and_print(out, "Enter blank number: ");
    fscanf(in, "%lu;", &(temp->number));
    check_and_print(out, "Enter storage place: ");
    get_string(in, temp->storage_place);
    check_and_print(out, "Enter responsible name: ");
    get_string(in, temp->responsible_name);
    check_and_print(out, "Enter responsible surname: ");
    get_string(in, temp->responsible_surname);

    if (check_blank(temp)) {
        free(temp);
        perror("Wrong input data!\n");
        return NULL;
    }
    return  temp;
}

// Print blank in output
void print_blank(FILE *out, Blank *bl) {
    fprintf(out, "number: %lu, storage: %s, responsible: %s %s\n",
            bl->number, bl->storage_place, bl->responsible_name,
            bl->responsible_surname);
}

#endif //  BLANK_H_
