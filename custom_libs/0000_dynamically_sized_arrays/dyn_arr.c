#include "dyn_arr.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum __resize {
    DOUBLE,
    HALVED,
};

void __resize_arr(dyn_ptr arr, enum __resize resize) {
    int64_t *x = NULL;
    switch (resize) {
    case DOUBLE: {
        arr->size *= 2;
        x          = realloc(arr->data, arr->size * sizeof(int64_t));
        break;
    }
    case HALVED: {
        arr->size /= 2;
        x          = realloc(arr->data, arr->size * sizeof(int64_t));
        break;
    }
    default: {
        arr->size *= 2;
        x          = realloc(arr->data, arr->size * sizeof(int64_t));
        break;
    }
    }
    if (x == NULL) {
        fprintf(stderr, "Resizing the dynamic array failed\n");
        switch (resize) {
        case DOUBLE: {
            arr->size /= 2;
            break;
        }
        case HALVED: {
            arr->size *= 2;
            break;
        }
        default: {
            arr->size *= 2;
            break;
        }
        }
        return;
    }
    arr->data = x;
}

void printf_array(dyn_ptr arr) {
    for (uint64_t i = 0; i < arr->used; i++) {
        (void)printf("Index: %5" PRIu64 " Item: %5" PRId64 "\n", i,
                     *(arr->data + i));
    }
}

void create_array(dyn_ptr arr) {
    if (arr == NULL) {
        fprintf(stderr, "NULL pointer was passed into create_array\n");
        return;
    }
    arr->used = 0;
    arr->size = 4;

    arr->data = calloc(arr->size, sizeof(int64_t));
    if (arr->data == NULL) {
        fprintf(stderr, "NULL pointer was passed into create_array\n");
        arr->size = 0;
        return;
    }
}

void delete_array(dyn_ptr arr) {
    if (arr == NULL) {
        fprintf(stderr, "NULL pointer was passed into delete_array\n");
        return;
    }
    free(arr->data);
    arr->data = NULL;
    arr->used = 0;
    arr->size = 0;
}

void push_2_array(dyn_ptr arr, int64_t num) {
    if (arr == NULL) {
        fprintf(stderr, "NULL pointer was passed into push_2_array\n");
        return;
    }
    if (arr->size <= (arr->used + 1))
        __resize_arr(arr, DOUBLE);
    if (arr->size <= (arr->used + 1))
        return;

    *(arr->data + arr->used)  = num;
    arr->used                += 1;
}

int64_t pop_from_arr(dyn_ptr arr) {
    if (arr == NULL) {
        fprintf(stderr, "NULL pointer was passed into pop_from_arr\n");
        return 0;
    }
    int64_t x = *(arr->data + (arr->used - 1));
    if ((arr->size / 2) >= (arr->used - 1))
        __resize_arr(arr, DOUBLE);

    arr->used -= 1;
    return x;
}

int64_t get_from_arr(dyn_ptr arr, uint64_t index) {
    if (arr == NULL) {
        fprintf(stderr, "NULL pointer was passed into get_from_arr\n");
        return 0;
    }
    if (index >= arr->used)
        return 0;
    return *(arr->data + index);
}
