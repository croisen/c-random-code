#ifndef ___0003_CROI_C_RANDOM_CODE___
#define ___0003_CROI_C_RANDOM_CODE___

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define LONGESTNAMELEN 747 + 2 // Longest name, newline char, null terminator
#define UINTMAXDIGITS  20 + 2  // Max digits, newline char, null terminator

typedef struct Participant
{
    uint64_t number;
    char *name;
    uint64_t lossCount; // For single and double elimination?
    uint64_t score;     // For round robin
} Participant;

typedef struct TourneyMatch
{
    Participant *p1;
    Participant *p2;
} TourneyMatch;

void mTFree(void *ptr);

// Auto frees all pointers created by this at exit
void *mTMalloc(uint64_t size);

// Auto frees all pointers created by this at exit
void *mTCalloc(uint64_t nmemb, uint64_t size);

// Auto frees all pointers created by this at exit
void *mTRealloc(void *ptr, uint64_t size);

Participant *createTourney(void);
uint64_t getParticipantCount(Participant *ps);
void printParticipants(Participant *ps);
void clearScreen(void);

#endif // ___0003_CROI_C_RANDOM_CODE___

#ifdef ___0003_CROI_C_RANDOM_CODE_IMPL___

#include <inttypes.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MTINFO "[INFO]     "
#define MTWARN "[WARN]     "
#define MTFAIl "[ERROR]    " // This don't seem correct but I'mma go with it
#define MTCRIT "[CRITICAL] "

typedef struct MemTrackerArr
{
    bool init;
    uint64_t size;
    uint64_t used;
    void **ptrs;
} MemTrackerArr;

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#define memTrackerLog(msgPrefix, fmtMessage, ...)                              \
    fprintf(stdout, "(%s Line: %3" PRIu64 ") " msgPrefix fmtMessage, __FILE__, \
            (uint64_t)__LINE__, ##__VA_ARGS__)

#define memTrackerPanic(exitCode, msgPrefix, fmtMessage, ...)                  \
    fprintf(stderr, "(%s Line: %3" PRIu64 ") " msgPrefix fmtMessage, __FILE__, \
            (uint64_t)__LINE__, ##__VA_ARGS__),                                \
        exit(EXIT_FAILURE)

    void memTrackerInit(void);
    void memTrackerFree(void);
    void memTrackerFreeSignal(int sig);
    void memTrackerExpand(void);

    MemTrackerArr memTracker = {
        false,
        0,
        0,
        NULL,
    };

    void memTrackerInit(void)
    {
        memTracker.init = true;
        memTracker.size = 8;
        memTracker.used = 0;
        memTracker.ptrs = calloc(memTracker.size, sizeof(void *));
        if (memTracker.ptrs == NULL)
            memTrackerPanic(
                1, MTCRIT,
                "Failed to initialize memtracker for bread parser :(\n");

        atexit(memTrackerFree);
        signal(SIGINT, memTrackerFreeSignal);
    }

    void memTrackerFreeSignal(int sig)
    {
        exit(sig);
    }

    void memTrackerFree(void)
    {
        for (uint64_t i = 0; i < memTracker.used; i += 1)
        {
            free(memTracker.ptrs[i]);
        }
        memTracker.size = 0;
        memTracker.used = 0;
        memTracker.init = 0;
        free(memTracker.ptrs);
    }

    void memTrackerExpand(void)
    {
        if (memTracker.size == (memTracker.used + 1))
        {
            void **newTracker =
                realloc(memTracker.ptrs, memTracker.size * sizeof(void *) * 2);
            if (newTracker == NULL)
                memTrackerPanic(EXIT_FAILURE, MTCRIT,
                                "Failed to expand list of pointers for the mem "
                                "tracker of bread parser...\n");

            for (uint64_t i = memTracker.size; i < memTracker.size * 2; i += 1)
            {
                newTracker[i] = NULL;
            }

            memTracker.size *= 2;
            memTracker.ptrs  = newTracker;
        }
    }

    int64_t memTrackerFindPtr(void *ptr)
    {
        for (uint64_t i = 0; i < memTracker.used; i += 1)
        {
            if (memTracker.ptrs[i] == ptr)
                return i;
        }

        return -1;
    }

    void mTFree(void *ptr)
    {
        int64_t ptrIndex = -1;
        for (uint64_t i = 0; i < memTracker.used; i += 1)
        {
            if (memTracker.ptrs[i] == ptr)
            {
                ptrIndex = i;
                break;
            }
        }

        if (ptrIndex != -1)
        {
            // Did I use memmove correctly to do this?
            // [0, 1, 2] pop(1)
            // [0, gone, 2]
            // [0, 2]
            memmove(memTracker.ptrs + ptrIndex, memTracker.ptrs + ptrIndex + 1,
                    (memTracker.used - 1 - ptrIndex) * sizeof(void *));
            memTracker.used -= 1;
        }
    }

    void *mTMalloc(uint64_t size)
    {
        if (!memTracker.init)
            memTrackerInit();

        void *res = malloc((size_t)size);
        if (res == NULL)
            memTrackerPanic(
                EXIT_FAILURE, MTCRIT,
                "Malloc returned null when trying to allocate memory for\n");

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
                "Calloc returned null when trying to allocate memory\n");

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
                "Realloc returned null when trying to allocate memory\n");

        if (ptrIndex != -1)
        {
            memTrackerExpand();
            memTracker.ptrs[ptrIndex]  = res;
            memTracker.used           += 1;
        }

        return res;
    }

    uint64_t countCommas(char *str)
    {
        uint64_t res = 0;
        if (str == NULL)
            return res;

        while (*str != '\0')
        {
            if (*str == ',')
                res += 1;

            str += 1;
        }

        return res;
    }

    Participant *participantCreate(uint64_t number, char *names)
    {
        Participant *res  = mTCalloc(number + 1, sizeof(Participant));
        char *copiedNames = mTCalloc(strlen(names) + 1, sizeof(char));

        strcpy(copiedNames, names);
        char *splitNames = strtok(names, ",");
        uint64_t count   = 1;
        while (splitNames != NULL)
        {
            res[count - 1].name       = splitNames;
            res[count - 1].number     = count;
            res[count - 1].lossCount  = 0;

            splitNames                = strtok(NULL, ",");
            count                    += 1;
        }

        return res;
    }

    Participant *createTourney(void)
    {
        char participantCount[UINTMAXDIGITS] = {0};
        uint64_t participantNum              = 0;

        char *strtoulPtr                     = NULL;
        char *names                          = NULL;

        printf("Input the number of participants below\n> ");
        fgets(participantCount, UINTMAXDIGITS, stdin);

        participantNum = strtoul(participantCount, &strtoulPtr, 10);
        names = mTCalloc(participantNum * LONGESTNAMELEN, sizeof(char));

        printf(
            "Input the names of the participants in order of their numbers "
            "below (Must be separated by commas or 'entered' name by name)\n");
        while (countCommas(names) < participantNum)
        {
            printf("(%3" PRIu64 ")> ", countCommas(names) + 1);
            fgets(names + strlen(names), participantNum * LONGESTNAMELEN,
                  stdin);
            names[strlen(names) - 1] = '\0'; // Replace 'em newlines
            strcat(names, ",");
        }

        printf("\n");
        return participantCreate(participantNum, names);
    }

    uint64_t getParticipantCount(Participant *ps)
    {
        uint64_t res = 0;
        while (ps->name != NULL)
        {
            res += 1;
            ps  += 1;
        }

        return res;
    }

    void printParticipants(Participant *ps)
    {
        uint64_t res = 1;
        while (ps->name != NULL)
        {
            printf("Participant #%3" PRIu64 ": %s\n", res, ps->name);
            ps  += 1;
            res += 1;
        }
    }

    void clearScreen(void)
    {
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
        HANDLE hStdOut;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD count;
        DWORD cellCount;
        COORD homeCoords = {0, 0};

        hStdOut          = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hStdOut == INVALID_HANDLE_VALUE)
            return;

        /* Get the number of cells in the current buffer */
        if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
            return;
        cellCount = csbi.dwSize.X * csbi.dwSize.Y;

        /* Fill the entire buffer with spaces */
        if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount,
                                        homeCoords, &count))
            return;

        /* Fill the entire buffer with the current colors and attributes */
        if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount,
                                        homeCoords, &count))
            return;

        /* Move the cursor home */
        SetConsoleCursorPosition(hStdOut, homeCoords);
#else
    printf("\033[1;1H\033[2J");
#endif
    }

#ifdef __cplusplus
}
#endif

#endif // ___0003_CROI_C_RANDOM_CODE_IMPL___
