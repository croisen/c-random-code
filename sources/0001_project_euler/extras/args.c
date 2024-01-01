#include "args.h"
#include "atoi64.h"

#include <argp.h>
#include <stdlib.h>

const char *argp_program_version = "Croisen's Project Euler Solutions v1.2.0";
const char *argp_program_bug_address = "<absolutenico32@gmail.com>";
static char doc[]                    = "Hello, World";
static char args_doc[]               = "";

struct argp_option option[]          = {
    {
     "problem-number", 'p',
     "<problem number>", 0,
     "Specifies which project euler problem to show the answer of", 0,
     },
    {
     "verbose", 'v',
     0, 0,
     "Makes this program print more stuff", 0,
     },
    {
     "help", 'h',
     0, 0,
     "Shows this help list", -1,
     },
    {
     "version", 'V',
     0, 0,
     "Prints this program's name and version", -1,
     },
    {0},
};

struct argp argp = {option, parse_opt, args_doc, doc, 0, 0, 0};

error_t parse_opt(int key, char *arg, struct argp_state *state) {
    arguments *args = state->input;
    switch (key) {
    case 'p': {
        args->problem_num = atoi64(arg);
        break;
    }
    case 'v': {
        args->verbose = true;
        break;
    }
    case 'h': {
        argp_state_help(state, state->out_stream, ARGP_HELP_STD_HELP);
        exit(0);
    }
    case USAGE: {
        argp_state_help(state, state->out_stream,
                        ARGP_HELP_USAGE | ARGP_HELP_EXIT_OK);
        exit(0);
    }
    case 'V': {
        fprintf(state->out_stream, "%s\n", argp_program_version);
        exit(0);
    }
    case ARGP_KEY_END: {
        if (state->arg_num == 1) {
            argp_state_help(state, state->out_stream, ARGP_HELP_STD_HELP);
            exit(0);
        }
        break;
    }
    default: {
        return ARGP_ERR_UNKNOWN;
    }
    }
    return 0;
}
