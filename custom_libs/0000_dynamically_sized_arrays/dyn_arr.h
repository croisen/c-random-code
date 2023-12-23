#ifndef __C_0000_SIMPLE_IMPL_DYN_ARR__
#define __C_0000_SIMPLE_IMPL_DYN_ARR__

#include <stdint.h>
#include <stdlib.h>

struct __dyn_arr {
    uint64_t used;
    uint64_t size;
    int64_t *data;
};

typedef struct __dyn_arr *dyn_ptr;
typedef struct __dyn_arr dyn_t[1];

void create_array(dyn_ptr arr);
void delete_array(dyn_ptr arr);
void printf_array(dyn_ptr arr);

void push_2_array(dyn_ptr arr, int64_t num);
int64_t pop_from_arr(dyn_ptr arr);
int64_t get_from_arr(dyn_ptr arr, uint64_t index);

#endif
