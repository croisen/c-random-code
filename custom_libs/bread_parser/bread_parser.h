#ifndef __CROI_CMD_ARGS_BREAD_PARSER__
#define __CROI_CMD_ARGS_BREAD_PARSER__

#include <stdint.h>

#define is_used(short_opt) (\
    (__is_used(short_opt) == COOL) || \
    (__is_used(short_opt) == ARGS)\
)
#define get_arg(short_opt) __get_args(short_opt)


typedef enum __option {
    NONE,
    COOL,
    ARGS,
} Option_T;

void bread_parse(int argc, char **argv);

void bread_parser_add_option(char short_opt, char *long_opt,
                             int64_t arg_count, int64_t group);
void bread_parser_add_descr(char short_opt, char *description);

Option_T __is_used(char short_opt);
char **__get_args(char short_opt);

#endif
