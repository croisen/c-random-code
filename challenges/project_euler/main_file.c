#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "helper/math_funcs.h"
#include "helper/problem_001-005.h"
#include "helper/problem_006-010.h"

#include "helper/func_exec.h"
#define USAGE 0x123


// Argp stuff for program name, version, email, and documentation
const char *argp_program_version = "croi_proj_euler_solutions 0.9";
const char *argp_program_bug_address = "<absolutenico32@gmail.com>";
static char doc[] =
    "Echoes solutions for projecteuler.net (only from 1 to 10 right now though)";
static char args_doc[] =
    "<Problem number (default 1)>";

// Error code when parsing fails
error_t argp_err_exit_status = 69;

// Options for argp.h
static struct argp_option option[] = {
    { "problem-number", 'p', "<problem number>", 0, "Specifies which problem to solve (not exactly needed option since you can just add a problem number without this)" },
    { "help", 'h', 0, 0, "Prints this help list" },
    { "version", 'V', 0, 0, "Prints the program name and version number" },
    { "usage", USAGE, 0, 0, "Shows the usage of this program" },
    { 0 }
};

struct arguments {
    int problem_num;
};


static error_t parse_opt (int key, char *arg, struct argp_state *state) {
    struct arguments *args = state->input;

    switch(key) {
        case 0:
            args->problem_num = atoi(arg);
            break;
        case 'p':
            args->problem_num = atoi(arg);
            break;
        case 'h':
            argp_state_help(state, state->out_stream, ARGP_HELP_STD_HELP);
            exit(0);
        case 'V':
            fprintf(state->out_stream, "%s\n", argp_program_version);
            exit(0);
        case USAGE:
            argp_state_help(state, state->out_stream, ARGP_HELP_USAGE | ARGP_HELP_EXIT_OK);
            exit(0);
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { option, parse_opt, args_doc, doc };

int main(int argc, char **argv) {
    // Default arguments
    struct arguments args;
    args.problem_num = 1;

    argp_parse(&argp, argc, argv, ARGP_NO_HELP, 0, &args);
    get_function(args.problem_num);
    return 0;
}
