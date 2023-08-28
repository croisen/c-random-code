#include "args.h"

struct argp_option option[] = {
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
        "Will output more text related to the function solving the projecteuler problem.\
\n\033[1;31mWARNING: it makes the program slower as it outputs it's stuff to stdout\033[0;0m",
        0
    },
    {
        "testing-mode",
        't',
        0, 0,
        "Will set testing mode to true if this option is used. This option expect a file called\
solutions.txt in a directory called hashes.",
        1
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


int_fast64_t ato_fast_i64(char *string_number) {
    int_fast64_t i = 1;
    char c;
    int scanned = sscanf(string_number, "%" SCNd64 "%c", &i, &c);

    if (scanned == 1) return i;
    if (scanned > 1) {
        return i;
    }
    return 0;  
}

error_t parse_opt (int key, char *arg, struct argp_state *state) {
    arguments *args = state->input;
    switch(key) {
        case 'p':
            args->problem = ato_fast_i64(arg);
            break;

        case 't':
            args->testing = true;
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
