#include <argp.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "helper/func_exec.h"
#define USAGE 0x123


// Argp stuff for program name, version, email, and documentation
const char *argp_program_version = "croi_proj_euler_solutions 6.9";
const char *argp_program_bug_address = "<absolutenico32@gmail.com>";
static char doc[] =
    "Echoes solutions for projecteuler.net (only from 1 to 15 right now though)";
static char args_doc[] = "";

// Error code when parsing fails
error_t argp_err_exit_status = 69;

// Options for argp.h
static struct argp_option option[] = {
    {
        "problem-number",
        'p',
        "<problem number>",
        0,
        "Specifies which problem to solve",
        0
    },
    {
        "verbose",
        'v',
        0, 0,
        "Will output more text related to the function solving the projecteuler problem",
        0
    },
    {
        "help",
        'h',
        0, 0,
        "Prints this help list",
        -1
    },
    {
        "usage",
        USAGE,
        0, 0, 
        "Shows the usage of this program",
        -1
    },
    {
        "version",
        'V',
        0, 0,
        "Prints the program name and version number",
        -1
    },
    { 0 }
};

struct arguments {
    int problem_num;
    bool verbose;
};


static error_t parse_opt (int key, char *arg, struct argp_state *state) {
    struct arguments *args = state->input;

    switch(key) {
        case 'p':
            if (isdigit((unsigned char)*arg)) {
                args->problem_num = atoi(arg);
            } else {
                fprintf(state->err_stream, "The argument passed to the -p option %s is not valid\n", arg);
                exit(1);
            }
            break;
        case 'v':
            args->verbose = true;
            break;
        case 'h':
            argp_state_help(state, state->out_stream, ARGP_HELP_STD_HELP);
            exit(0);
        case USAGE:
            argp_state_help(state, state->out_stream, ARGP_HELP_USAGE | ARGP_HELP_EXIT_OK);
            exit(0);
        case 'V':
            fprintf(state->out_stream, "%s\n", argp_program_version);
            exit(0);
        case ARGP_KEY_END:
            if (state->arg_num == 1) {
                argp_state_help(state, state->out_stream, ARGP_HELP_STD_HELP);
                exit(0);
            }
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = { option, parse_opt, args_doc, doc, 0, 0, 0 };

int main(int argc, char **argv) {
    // Default arguments
    struct arguments args;
    args.problem_num = 1;
    args.verbose = false;

    argp_parse(&argp, argc, argv, ARGP_NO_HELP, 0, &args);
    printf("Trying to get the function to solve projecteuler's problem #%d...\n", args.problem_num);
    get_function(args.problem_num, args.verbose);
    return 0;
}
