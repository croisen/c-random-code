#ifndef PROJECT_EULER_ARGP
#define PROJECT_EULER_ARGP

#include <argp.h>
#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define USAGE 0x123

int_fast64_t ato_fast_i64(char *string_number);
error_t parse_opt(int key, char *arg, struct argp_state *state);

extern struct argp_option option[];

struct __arguments {
    int_fast64_t problem;
    bool         verbose;
    bool         testing;
};
typedef struct __arguments arguments;

#endif
