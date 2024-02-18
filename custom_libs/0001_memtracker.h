#ifndef CROI_LIB_0001_MEMTRACKER_H
#define CROI_LIB_0001_MEMTRACKER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct __mt_darr_for_ptr
{
    bool init;
    size_t size;
    size_t used;
    void **ptrs;
};

typedef struct __mt_darr_for_ptr MT_DA[1];

#define memtracker_panic(message, ...)       \
    fprintf(stderr, message, ##__VA_ARGS__); \
    exit(EXIT_FAILURE)

extern void croi_free(void *ptr);
extern void *croi_calloc(size_t nmemb, size_t size);
extern void *croi_malloc(size_t size);
extern void *croi_realloc(void *ptr, size_t size);

#endif

#ifdef CROI_LIB_0001_MEMTRACKER_IMPL_H

MT_DA alloced_ptrs = {0};

extern int __memtracker_sort(const void *a, const void *b);
extern void __memtracker_init(void);
extern void __memtracker_free_void(void);
extern void __memtracker_free_sig(int dummy);

int __memtracker_sort(const void *a, const void *b)
{
    void *c = *(void **)a;
    void *d = *(void **)b;

    // Sorted from highest to lowest
    return (uint64_t)d - (uint64_t)c;
}

void __memtracker_init(void)
{
    atexit(__memtracker_free_void);
    signal(SIGINT, __memtracker_free_sig);
    signal(SIGSEGV, __memtracker_free_sig);

    alloced_ptrs->init = true;
    alloced_ptrs->size = 4;
    alloced_ptrs->used = 0;

    alloced_ptrs->ptrs = calloc(alloced_ptrs->size, sizeof(void *));
    if (alloced_ptrs->ptrs == NULL)
    {
        __bread_panic("Cannot initialize memory tracker, calloc "
                      "returned NULL\n");
    }
}

void __memtracker_free_void(void)
{
    for (uint64_t i = 0; i < alloced_ptrs->size; i += 1)
    {
#ifdef ___MEMTRACKER_DEBUG
        printf("Freeing alloced_ptrs: 0x%016" PRIx64 "\n",
               (uint64_t)alloced_ptrs->ptrs[i]);
#endif
        free(alloced_ptrs->ptrs[i]);
    }

#ifdef ___MEMTRACKER_DEBUG
    printf("Freeing alloced_ptrs: 0x%016" PRIx64 "\n",
           (uint64_t)alloced_ptrs->ptrs);
#endif
    free(alloced_ptrs->ptrs);
}

void __memtracker_free_sig(int dummy)
{
    fprintf(stderr, "Signal %s caught, now exiting...\n", strsignal(dummy));
    exit(dummy);
}

void *croi_calloc(uint64_t nmemb, uint64_t size)
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
            __bread_panic("Cannot track new memory given by croi_calloc, "
                          "realloc return NULL\n");
        }

        for (uint64_t i                       = (alloced_ptrs->size - 1);
             i < (alloced_ptrs->size * 2); i += 1)
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

void *croi_malloc(uint64_t size)
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
            __bread_panic("Cannot track new memory given by croi_malloc, "
                          "realloc return NULL\n");
        }

        for (uint64_t i                       = (alloced_ptrs->size - 1);
             i < (alloced_ptrs->size * 2); i += 1)
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

void *croi_realloc(void *ptr, uint64_t size)
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
            __bread_panic("Cannot track new memory given by croi_realloc, "
                          "realloc return NULL\n");
        }

        for (uint64_t i                       = (alloced_ptrs->size - 1);
             i < (alloced_ptrs->size * 2); i += 1)
        {
            new_arr[i] = NULL;
        }

        alloced_ptrs->ptrs  = new_arr;
        alloced_ptrs->size *= 2;
    }

    for (uint64_t i = 0; i < alloced_ptrs->used; i += 1)
    {
        if (res != NULL && alloced_ptrs->ptrs[i] == ptr)
        {
            alloced_ptrs->ptrs[i] = res;
            goto bread_realloc_ret;
        }
    }

    alloced_ptrs->ptrs[alloced_ptrs->used]  = res;
    alloced_ptrs->used                     += 1;

bread_realloc_ret:
    return res;
}

void croi_free(void *ptr)
{
    qsort(alloced_ptrs->ptrs, alloced_ptrs->used, sizeof(void *),
          __memtracker_sort);
    uint64_t key = (uint64_t)ptr;
    void **item  = bsearch(&key, alloced_ptrs->ptrs, alloced_ptrs->used,
                           sizeof(void *), __memtracker_sort);
    if (item != NULL)
    {
        *item = NULL;
        qsort(alloced_ptrs->ptrs, alloced_ptrs->used, sizeof(void *),
              __memtracker_sort);
    }

    free(ptr);
    alloced_ptrs->used -= 1;
}

#endif
