#include <argp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "helper/math_funcs.h"
#include "helper/problem_001-005.h"
#include "helper/problem_006-010.h"

#include "helper/func_exec.h"


// Argp stuff for program name, version, email, and documentation
const char *argp_program_version = "croi_proj_euler_solutions 0.9";
const char *argp_program_bug_address = "<absolutenico32@gmail.com>";
static char doc[] =
    "Echoes solutions for projecteuler.net (only from 1 to 10 right now though)";
static char args_doc[] =
    "<Problem number (default 1)>";

// Error code when parsing fails
error_t argp_err_exit_status = 69;

// Argument options well there's only one custom option 
static struct argp_option option[] = {
    { "problem-number", 'p', "<problem number>", 0, "Specifies which problem to solve (not exactly needed option since you can just add a problem number without this)" },
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

    argp_parse(&argp, argc, argv, 0, 0, &args);
    get_function(args.problem_num);
    return 0;
}
