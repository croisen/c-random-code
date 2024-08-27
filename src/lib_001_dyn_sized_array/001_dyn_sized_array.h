#ifndef C_RANDOM_001_DYN_SIZED_ARRAY_H
#define C_RANDOM_001_DYN_SIZED_ARRAY_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
 * By defining a type with typedef struct that contains ints
 * called size and used with any pointer called data;
 * You can use the Dyn_S_Arr_Init and Dyn_S_Arr_Free macros to initialize
 * and free a growable array of any type
 *
 * Side note: The macros takes in pointers to the typedef-ed struct
 */
struct Dyn_Array {
    int size;
    int used;
    int *data;
};

#define Dyn_S_Arr_Init(dyn_arr_ptr)                                            \
    do {                                                                       \
        (dyn_arr_ptr)->size = 8;                                               \
        (dyn_arr_ptr)->used = 0;                                               \
        void *data =                                                           \
            malloc((dyn_arr_ptr)->size * sizeof(*(dyn_arr_ptr)->data));        \
        assert(data != NULL && "Buy more ram?");                               \
        (dyn_arr_ptr)->data = data;                                            \
    } while (false)

#define Dyn_S_Arr_Free(dyn_arr_ptr)                                            \
    do {                                                                       \
        free((dyn_arr_ptr)->data);                                             \
        (dyn_arr_ptr)->size = 0;                                               \
        (dyn_arr_ptr)->used = 0;                                               \
        (dyn_arr_ptr)->data = NULL;                                            \
    } while (false)

/* Welp we made the min compare jumpless, tho does it have an effect? IDK */
#define Dyn_S_Arr_Resize(dyn_arr_ptr, new_size)                                \
    do {                                                                       \
        bool cmp    = ((dyn_arr_ptr)->size < (new_size));                      \
        int smaller = ((dyn_arr_ptr)->size * cmp) + ((new_size) * !cmp);       \
        void *data  = malloc((new_size) * sizeof(*(dyn_arr_ptr)->data));       \
        assert(data != NULL && "Buy more ram?");                               \
        memcpy(                                                                \
            data, (dyn_arr_ptr)->data, smaller * sizeof(*(dyn_arr_ptr)->data)  \
        );                                                                     \
        free((dyn_arr_ptr)->data);                                             \
        (dyn_arr_ptr)->data = data;                                            \
    } while (false)

#define Dyn_S_Arr_Push_Back(dyn_arr_ptr, item)                                 \
    do {                                                                       \
        if ((dyn_arr_ptr)->used + 1 >= (dyn_arr_ptr)->size)                    \
            Dyn_S_Arr_Resize((dyn_arr_ptr), (dyn_arr_ptr)->size * 2);          \
                                                                               \
        (dyn_arr_ptr)->data[(dyn_arr_ptr)->used]  = item;                      \
        (dyn_arr_ptr)->used                      += 1;                         \
    } while (false)

#define Dyn_S_Arr_Pop_Back(dyn_arr_ptr, item_ptr)                              \
    do {                                                                       \
        if ((dyn_arr_ptr)->used - 1 < (dyn_arr_ptr)->size / 2)                 \
            Dyn_S_Arr_Resize((dyn_arr_ptr), (dyn_arr_ptr)->size / 2);          \
                                                                               \
        *(item_ptr)          = (dyn_arr_ptr)->data[(dyn_arr_ptr)->used];       \
        (dyn_arr_ptr)->used -= 1;                                              \
    } while (false)

/*
 * idx will become 0 if cmp is true
 * then the data at idx will be multiplied by the opposite of idx to return 0
 */
#define Dyn_S_Arr_Get(dyn_arr_ptr, item_ptr, index)                            \
    do {                                                                       \
        bool cmp    = (index < 0 || index >= (dyn_arr_ptr)->used);             \
        int idx     = index * !cmp;                                            \
        *(item_ptr) = (dyn_arr_ptr)->data[idx] * !cmp;                         \
    } while (false)

#endif /* C_RANDOM_001_DYN_SIZED_ARRAY_H */
