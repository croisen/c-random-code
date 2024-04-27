#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memtracker_pair.h"

typedef struct MemTrackerArr {
    bool init;
    uint64_t size;
    uint64_t used;
    void **ptrs;
} MemTrackerArr;

static MemTrackerArr memTracker = {
    false,
    0,
    0,
    NULL,
};

static void memTrackerInit(void);
static void memTrackerFree(void);
static void memTrackerFreeSignal(int sig);
static void memTrackerExpand(void);
static int64_t memTrackerFindPtr(void *ptr);

static void memTrackerInit(void)
{
    memTracker.init = true;
    memTracker.size = 8;
    memTracker.used = 0;
    memTracker.ptrs = calloc(memTracker.size, sizeof(void *));
    if (memTracker.ptrs == NULL)
        memTrackerPanic(
            EXIT_FAILURE, MTCRIT,
            "Failed to initialize memtracker for bread parser :(\n"
        );

    atexit(memTrackerFree);
    signal(SIGINT, memTrackerFreeSignal);
}

static void memTrackerFreeSignal(int sig)
{
    exit(sig);
}

static void memTrackerFree(void)
{
    for (uint64_t i = 0; i < memTracker.used; i += 1) {
        free(memTracker.ptrs[i]);
    }
    memTracker.size = 0;
    memTracker.used = 0;
    memTracker.init = 0;
    free(memTracker.ptrs);
}

static void memTrackerExpand(void)
{
    if (memTracker.size == (memTracker.used + 1)) {
        void **newTracker =
            realloc(memTracker.ptrs, memTracker.size * sizeof(void *) * 2);
        if (newTracker == NULL)
            memTrackerPanic(
                EXIT_FAILURE, MTCRIT,
                "Failed to expand list of pointers for the mem "
                "tracker of bread parser...\n"
            );

        for (uint64_t i = memTracker.size; i < memTracker.size * 2; i += 1) {
            newTracker[i] = NULL;
        }

        memTracker.size *= 2;
        memTracker.ptrs  = newTracker;
    }
}

static int64_t memTrackerFindPtr(void *ptr)
{
    for (uint64_t i = 0; i < memTracker.used; i += 1) {
        if (memTracker.ptrs[i] == ptr)
            return i;
    }

    return -1;
}

void mTFree(void *ptr)
{
    int64_t ptrIndex = -1;
    for (uint64_t i = 0; i < memTracker.used; i += 1) {
        if (memTracker.ptrs[i] == ptr) {
            ptrIndex = i;
            break;
        }
    }

    if (ptrIndex != -1) {
        // Did I use memmove correctly to do this?
        // [0, 1, 2] pop(1)
        // [0, gone, 2]
        // [0, 2]
        memmove(
            memTracker.ptrs + ptrIndex, memTracker.ptrs + ptrIndex + 1,
            (memTracker.used - 1 - ptrIndex) * sizeof(void *)
        );
        memTracker.used                  -= 1;
        memTracker.ptrs[memTracker.used]  = NULL;
    }

    // Holy crap I forgot to call free from this (I did it again...)
    free(ptr);
}

void *mTMalloc(uint64_t size)
{
    if (!memTracker.init)
        memTrackerInit();

    void *res = malloc((size_t)size);
    if (res == NULL)
        memTrackerPanic(
            EXIT_FAILURE, MTCRIT,
            "Malloc returned null when trying to allocate memory for\n"
        );

    memTrackerExpand();

    memTracker.ptrs[memTracker.used]  = res;
    memTracker.used                  += 1;

    return res;
}

void *mTCalloc(uint64_t nmemb, uint64_t size)
{
    if (!memTracker.init)
        memTrackerInit();

    void *res = calloc((size_t)nmemb, (size_t)size);
    if (res == NULL)
        memTrackerPanic(
            EXIT_FAILURE, MTCRIT,
            "Calloc returned null when trying to allocate memory\n"
        );

    memTrackerExpand();
    memTracker.ptrs[memTracker.used]  = res;
    memTracker.used                  += 1;
    return res;
}

void *mTRealloc(void *ptr, uint64_t size)
{
    if (!memTracker.init)
        memTrackerInit();

    int64_t ptrIndex = memTrackerFindPtr(ptr);
    void *res        = realloc(ptr, (size_t)size);
    if (res == NULL)
        memTrackerPanic(
            EXIT_FAILURE, MTCRIT,
            "Realloc returned null when trying to allocate memory\n"
        );

    memTrackerExpand();
    if (ptrIndex != -1)
        memTracker.ptrs[ptrIndex] = res;
    else {
        memTracker.ptrs[memTracker.used]  = res;
        memTracker.used                  += 1;
    }

    return res;
}

#ifdef __cplusplus
}
#endif // __cplusplus
