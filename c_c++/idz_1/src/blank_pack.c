/*
Copyright 2019 Сергей Меликян АПО-12
*/
#include "../include/blank_pack.h"

Blank_pack* new_blank_pack(size_t n) {
    Blank_pack *temp = calloc(1, sizeof(Blank_pack));
    temp->blanks = new_blank_array(n);
    return temp;
}

void free_blank_pack(Blank_pack *pack) {
    for (Blank_pack *i = pack, *n = pack->next; i;) {
        free_blank_array_full(i->blanks);
        free(i);
        i = n;
        if (n)
            n = n->next;
    }
}

//  Compare function of 2 blancks for sort algorithm
int is_less(Blank *left, Blank *right) {
    return left->number < right->number;
}

//  Merge sort algorithm adapted for blanks sorting
Blank** merge_sort(Blank **up, Blank **down,
                   size_t left, size_t right,
                   int compare(Blank *, Blank *)) {
    if (left == right) {
        down[left] = up[left];
        return down;
    }

    size_t middle = (left + right) / 2;

    Blank **l_buff = merge_sort(up, down, left, middle, compare);
    Blank **r_buff = merge_sort(up, down, middle + 1, right, compare);

    Blank **target = l_buff == up ? down : up;

    size_t l_cur = left, r_cur = middle + 1;
    for (size_t i = left; i <= right; i++) {
        if (l_cur <= middle && r_cur <= right) {
            if (compare(l_buff[l_cur], r_buff[r_cur])) {
                target[i] = l_buff[l_cur];
                l_cur++;
            } else {
                target[i] = r_buff[r_cur];
                r_cur++;
            }
        } else if (l_cur <= middle) {
            target[i] = l_buff[l_cur];
            l_cur++;
        } else {
            target[i] = r_buff[r_cur];
            r_cur++;
        }
    }
    return target;
}

//  Find right border of pack
size_t find_right(Blank **a, size_t left, size_t size) {
    if (left == size)
        return size + 1;
    size_t i = left + 1;
    while (i < size) {
        if (a[i]->number - a[i-1]->number != 1)
            break;
        if (strcmp(a[i]->storage_place, a[i-1]->storage_place))
            break;
        if (strcmp(a[i]->responsible_name, a[i-1]->responsible_name))
            break;
        if (strcmp(a[i]->responsible_surname, a[i-1]->responsible_surname))
            break;
        i++;
    }
    return i;
}

// Get packs from file in, write data in out if in == stdin
Blank_pack* get_packs(FILE *in, FILE *out) {
    Blank_array *blanks = get_blanks(in, out);
    size_t size = blanks->size;
    Blank **temp = calloc(size, sizeof(Blank *));
    if (!temp) {
        free_blank_array_full(blanks);
        return NULL;
    }
    Blank **result = merge_sort(blanks->array, temp, 0, size - 1, is_less);

    size_t left = 0;
    size_t right = find_right(result, left, size);

    Blank_pack *packs = new_blank_pack(right - left);
    if (!packs) {
        free(temp);
        free_blank_array_full(blanks);
        return NULL;
    }
    Blank_pack *t_pack = packs;

    while (right <= size) {
        if (left > 0)
            t_pack = t_pack->next;
        for (size_t i = left, j = 0; i < right; i++, j++) {
            t_pack->blanks->array[j] = result[i];
        }
        left = right;
        right = find_right(result, left, size);
        Blank_pack *next = new_blank_pack(right - left);
        if (!next) {
            free(temp);
            free_blank_pack(packs);
            free_blank_array_full(blanks);
            return NULL;
        }
        t_pack->next = next;
    }
    Blank_pack *t = t_pack->next;
    t_pack->next = NULL;
    free_blank_pack(t);
    free(temp);
    free_blank_array(blanks);

    return packs;
}

// Print packs in out
void print_packs(FILE *out, Blank_pack *packs) {
    unsigned long p_i = 1;
    for (Blank_pack *i = packs, *n = packs->next; i;) {
        fprintf(out, "Pack number %lu:\n", p_i++);
        for (size_t j = 0; j < i->blanks->size; j++) {
            fprintf(out, "\t");
            print_blank(out, i->blanks->array[j]);
        }
        i = n;
        if (n)
            n = n->next;
    }
}
