#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "helper/math_funcs.h"
#include "helper/problem_001-005.h"
#include "helper/problem_006-010.h"

// Argp stuff for program name email and version
const char *argp_program_version = "croi_proj_euler_solutions 6.9";
const char *argp_program_bug_address = "absolutenico32@gmail.com";
error_t argp_err_exit_status = 127;

// I dunno what this is but it's in the sample
/*static char doc[] = "Using argparse, I dunno how";*/
/*static char args_doc[] = "arg1 arg2";*/

// Options for argparse
static struct argp_option options[] = {
    {"problem_number",  'p',    "number",   0,  "Specify problem number"},
    {"help",            'h',    0,          0,  "Print help message"},
    { 0 }
};

// Used by argp_parse to set variables used by main
struct arguments {
    char *problem_number;
};

// Parsing a single option
static error_t parse_opts(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch(key) {
        case 'p':
            arguments->problem_number = arg;
            break;
        case 'h':
            argp_state_help(state, stdout, ARGP_HELP_LONG | ARGP_HELP_DOC);
            exit(0);
        case ARGP_KEY_END:
            if(state->arg_num < 1) {
                argp_usage(state);
            }
            break;
        default:
            return argp_err_exit_status;
    }

    return 0;
}

static struct argp argp = { options, parse_opts, 0, 0 };

int main(int argc, char *argv[]) {
    struct arguments arguments;
    arguments.problem_number = "1";

    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    printf("Problem num = %s\n", arguments.problem_number);
    return 0;
}
