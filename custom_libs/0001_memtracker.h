#ifndef CROI_LIB_0001_MEMTRACKER_H
#define CROI_LIB_0001_MEMTRACKER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct __darr_for_ptr
{
    bool init;
    size_t size;
    size_t used;
    void **ptrs;
};

typedef struct __darr_for_ptr DA[1];

#define memtracker_panic(message, ...)       \
    fprintf(stderr, message, ##__VA_ARGS__); \
    exit(EXIT_FAILURE)

void __memtracker_init();
void __memtracker_free();

void croi_free(void *ptr);
void *croi_calloc(size_t nmemb, size_t size);
void *croi_malloc(size_t size);
void *croi_realloc(void *ptr, size_t size);

#endif

#ifdef CROI_LIB_0001_MEMTRACKER_IMPL_H

DA alloced_ptrs = {0};

void __memtracker_init()
{
    atexit(__memtracker_free);
    alloced_ptrs->init = true;
    alloced_ptrs->size = 4;
    alloced_ptrs->used = 0;

    alloced_ptrs->ptrs = calloc(alloced_ptrs->size, sizeof(void *));
    if (alloced_ptrs->ptrs == NULL)
    {
        bread_panic(
            "Cannot initialize memory tracker for the bread parser, calloc "
            "returned NULL\n");
    }
}

void __memtracker_free()
{
    for (size_t i = 0; i < alloced_ptrs->used; i += 1)
    {
        free(alloced_ptrs->ptrs[i]);
    }

    free(alloced_ptrs->ptrs);
}

void *croi_calloc(size_t nmemb, size_t size)
{
    if (!alloced_ptrs->init)
    {
        __memtracker_init();
    }

    void *res = calloc(nmemb, size);
    if (alloced_ptrs->size <= (alloced_ptrs->used + 1))
    {
        void **new_arr = realloc(alloced_ptrs->ptrs,
                                 sizeof(void *) * (alloced_ptrs->size * 2));
        if (new_arr == NULL)
        {
            free(res);
            memtracker_panic("Cannot track new memory given by croi_calloc, "
                             "realloc return NULL\n");
        }

        for (size_t i  = (alloced_ptrs->size - 1); i < (alloced_ptrs->size * 2);
             i        += 1)
        {
            new_arr[i] = NULL;
        }

        alloced_ptrs->ptrs  = new_arr;
        alloced_ptrs->size *= 2;
    }

    if (res != NULL)
    {
        alloced_ptrs->ptrs[alloced_ptrs->used]  = res;
        alloced_ptrs->used                     += 1;
    }

    return res;
}

void *croi_malloc(size_t size)
{
    if (!alloced_ptrs->init)
    {
        __memtracker_init();
    }

    void *res = malloc(size);
    if (alloced_ptrs->size <= (alloced_ptrs->used + 1))
    {
        void **new_arr = realloc(alloced_ptrs->ptrs,
                                 sizeof(void *) * (alloced_ptrs->size * 2));
        if (new_arr == NULL)
        {
            free(res);
            memtracker_panic("Cannot track new memory given by croi_malloc, "
                             "realloc return NULL\n");
        }

        for (size_t i  = (alloced_ptrs->size - 1); i < (alloced_ptrs->size * 2);
             i        += 1)
        {
            new_arr[i] = NULL;
        }

        alloced_ptrs->ptrs  = new_arr;
        alloced_ptrs->size *= 2;
    }

    if (res != NULL)
    {
        alloced_ptrs->ptrs[alloced_ptrs->used]  = res;
        alloced_ptrs->used                     += 1;
    }

    return res;
}

void *croi_realloc(void *ptr, size_t size)
{
    if (!alloced_ptrs->init)
    {
        __memtracker_init();
    }

    void *res = realloc(ptr, size);
    if (alloced_ptrs->size <= (alloced_ptrs->used + 1))
    {
        void **new_arr = realloc(alloced_ptrs->ptrs,
                                 sizeof(void *) * (alloced_ptrs->size * 2));
        if (new_arr == NULL)
        {
            free(res);
            memtracker_panic("Cannot track new memory given by croi_realloc, "
                             "realloc return NULL\n");
        }

        for (size_t i  = (alloced_ptrs->size - 1); i < (alloced_ptrs->size * 2);
             i        += 1)
        {
            new_arr[i] = NULL;
        }

        alloced_ptrs->ptrs  = new_arr;
        alloced_ptrs->size *= 2;
    }

    for (size_t i = 0; i < alloced_ptrs->used; i += 1)
    {
        if (res != NULL && alloced_ptrs->ptrs[i] == ptr)
        {
            alloced_ptrs->ptrs[i] = res;
            goto croi_realloc_ret;
        }
    }

    alloced_ptrs->ptrs[alloced_ptrs->used]  = res;
    alloced_ptrs->used                     += 1;

croi_realloc_ret:
    return res;
}

#endif
