#include <assert.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*#include "001_dyn_sized_array.h"*/
#include "002_memtracker.h"

struct mem_tracker_s {
    bool init;

    int size;
    int used;
    void **data;
};

static struct mem_tracker_s mem_tracker = {
    .init = false,
    .size = 0,
    .used = 0,
    .data = NULL,
};

// Better to not have cross dependencies between libs?
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

/*
 * Welp we made the min compare jumpless, tho does it have an effect? IDK
 * On the previous commit well I forgot that the size have changed...
 */
#define Dyn_S_Arr_Resize(dyn_arr_ptr, new_size)                                \
    do {                                                                       \
        void *data = realloc(                                                  \
            (dyn_arr_ptr)->data, (new_size) * sizeof(*(dyn_arr_ptr)->data)     \
        );                                                                     \
        assert(data != NULL && "Buy more ram?");                               \
        (dyn_arr_ptr)->data = data;                                            \
        (dyn_arr_ptr)->size = new_size;                                        \
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

static void Mem_Tracker_Free(void)
{
    for (int i = 0; i < mem_tracker.used; i++)
        free(mem_tracker.data[i]);

    Dyn_S_Arr_Free(&mem_tracker);
    mem_tracker.init = false;
}

static void Mem_Tracker_Init(void)
{
    Dyn_S_Arr_Init(&mem_tracker);
    atexit(Mem_Tracker_Free);
    signal(SIGINT, exit);
    signal(SIGSEGV, exit);
}

void *MT_Malloc(size_t size)
{
    if (!mem_tracker.init)
        Mem_Tracker_Init();

    void *res = malloc(size);
    Dyn_S_Arr_Push_Back(&mem_tracker, res);
    return res;
}

void *MT_Calloc(size_t nmemb, size_t size)
{
    if (!mem_tracker.init)
        Mem_Tracker_Init();

    void *res = calloc(nmemb, size);
    Dyn_S_Arr_Push_Back(&mem_tracker, res);
    return res;
}

void *MT_Realloc(void *ptr, size_t size)
{
    if (!mem_tracker.init)
        Mem_Tracker_Init();

    int idx = -1;
    for (int i = 0; i < mem_tracker.used; i++)
        if (ptr == mem_tracker.data[i]) {
            idx = i;
            break;
        }

    if (idx != -1) {
        memmove(
            mem_tracker.data + idx, mem_tracker.data + idx + 1,
            (mem_tracker.used - idx + 1) * sizeof(*mem_tracker.data)
        );
        mem_tracker.used -= 1;
    }

    void *res = realloc(ptr, size);
    Dyn_S_Arr_Push_Back(&mem_tracker, res);
    return res;
}

void MT_Free(void *ptr)
{
    int idx = -1;
    for (int i = 0; i < mem_tracker.used; i++) {
        if (ptr == mem_tracker.data[i]) {
            idx = i;
            break;
        }
    }

    if (idx != -1) {
        memmove(
            mem_tracker.data + idx, mem_tracker.data + idx + 1,
            (mem_tracker.used - idx - 1) * sizeof(*mem_tracker.data)
        );
        mem_tracker.used -= 1;
    }

    free(ptr);
}
