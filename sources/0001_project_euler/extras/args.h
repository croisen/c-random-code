#ifndef __C_0001_PROJECT_EULER_ARGS__
#define __C_0001_PROJECT_EULER_ARGS__

#include <argp.h>
#include <stdbool.h>
#include <stdint.h>

#define USAGE 0x123


typedef struct __arguments {
    bool verbose;
    int64_t problem_num;
} arguments;

extern struct argp argp;

error_t parse_opt(int key, char *arg, struct argp_state *state);

#endif
