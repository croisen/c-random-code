#ifndef CROI_LIB_BREAD_PARSER_H
#define CROI_LIB_BREAD_PARSER_H

#include <assert.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct __arg
{
    size_t arg_count;
    char short_opt;
    char *long_opt;
    char *descr;
    void **args;
} Arg;

struct __darr_for_ptr
{
    bool init;
    size_t size;
    size_t used;
    void **ptrs;
};

typedef enum __option
{
    NONE,
    COOL,
    ARGS,
} Bread_Option_T;

typedef struct __darr_for_ptr DA[1];

#define bread_panic(message, ...)            \
    fprintf(stderr, message, ##__VA_ARGS__); \
    exit(EXIT_FAILURE)

#define is_used(short_opt) \
    ((__is_used(short_opt) == COOL) || (__is_used(short_opt) == ARGS))
#define get_arg(short_opt) __get_args(short_opt)

void __memtracker_init();
void __memtracker_free();

void *bread_calloc(size_t nmemb, size_t size);
void *bread_malloc(size_t size);
void *bread_realloc(void *ptr, size_t size);

void bread_parse(int argc, char **argv);
void bread_parser_add_option(char short_opt, char *long_opt, int64_t arg_count,
                             int64_t group);
void bread_parser_add_descr(char short_opt, char *description);

Bread_Option_T __is_used(char short_opt);
char **__get_args(char short_opt);

#endif

#ifdef CROI_LIB_BREAD_PARSER_IMPL_H

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

void *bread_calloc(size_t nmemb, size_t size)
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
            bread_panic("Cannot track new memory given by bread_calloc, "
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

void *bread_malloc(size_t size)
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
            bread_panic("Cannot track new memory given by bread_malloc, "
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

void *bread_realloc(void *ptr, size_t size)
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
            bread_panic("Cannot track new memory given by bread_malloc, "
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
            goto bread_realloc_ret;
        }
    }

    alloced_ptrs->ptrs[alloced_ptrs->used]  = res;
    alloced_ptrs->used                     += 1;

bread_realloc_ret:
    return res;
}

#endif
