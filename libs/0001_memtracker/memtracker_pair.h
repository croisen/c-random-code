#ifndef ___0001_CROI_C_RANDOM_HEADER_CODE___
#define ___0001_CROI_C_RANDOM_HEADER_CODE___

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mTFree(void *ptr);
void *mTMalloc(uint64_t size);
void *mTCalloc(uint64_t nmemb, uint64_t size);
void *mTRealloc(void *ptr, uint64_t size);

#define MTMaxLineWidth 80
#define MTINFO         "[INFO]     "
#define MTWARN         "[WARN]     "
#define MTFAIL         "[ERROR]    " // This don't seem correct but I'mma go with it
#define MTCRIT         "[CRITICAL] "

#define memTrackerFprintf(columnWidth, stream, fmt, ...)                       \
    do {                                                                       \
        int printLen = columnWidth;                                            \
        uint64_t neededSize =                                                  \
            snprintf(NULL, 0, fmt __VA_OPT__(, ) __VA_ARGS__) + 1;             \
        char *_CL_printBuf = (char *)malloc(neededSize * sizeof(char));        \
        if (_CL_printBuf == NULL) {                                            \
            fprintf(stream, "Cannot initialize columned fprintf\n");           \
            fprintf(stream, fmt __VA_OPT__(, ) __VA_ARGS__);                   \
            exit(EXIT_FAILURE);                                                \
        }                                                                      \
                                                                               \
        sprintf(_CL_printBuf, fmt __VA_OPT__(, ) __VA_ARGS__);                 \
        char *_CL_copy = _CL_printBuf;                                         \
        while ((_CL_printBuf + neededSize - 1) >= _CL_copy) {                  \
            int wordLen = strcspn(_CL_copy, " ");                              \
            if (wordLen > printLen) {                                          \
                printf("\n");                                                  \
                printLen = columnWidth;                                        \
            }                                                                  \
                                                                               \
            if (_CL_copy[wordLen - 1] == '\n') {                               \
                printf("%.*s", wordLen, _CL_copy);                             \
                printLen  = columnWidth;                                       \
                _CL_copy += wordLen;                                           \
                _CL_copy += strcspn(_CL_copy, " ") + 1;                        \
            } else {                                                           \
                printf("%.*s ", wordLen, _CL_copy);                            \
                _CL_copy += wordLen;                                           \
                _CL_copy += strcspn(_CL_copy, " ") + 1;                        \
                printLen -= wordLen + 1;                                       \
            }                                                                  \
        }                                                                      \
        free(_CL_printBuf);                                                    \
    } while (false)

#define memTrackerLog(msgPrefix, fmtMessage, ...)                              \
    memTrackerFprintf(                                                         \
        80, stdout, msgPrefix fmtMessage __VA_OPT__(, ) __VA_ARGS__            \
    )

#define memTrackerPanic(exitCode, msgPrefix, fmtMessage, ...)                  \
    do {                                                                       \
        memTrackerFprintf(                                                     \
            80, stdout, "(%s: %" PRIu64 ") " msgPrefix fmtMessage, __FILE__,   \
            (uint64_t)__LINE__ __VA_OPT__(, ) __VA_ARGS__                      \
        );                                                                     \
        exit(exitCode);                                                        \
    } while (false)

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // ___0001_CROI_C_RANDOM_HEADER_CODE___
