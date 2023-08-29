#include <inttypes.h>
#include <stdio.h>

#include "project_euler_solutions/args.h"
#include "project_euler_solutions/func_exec.h"

// Argp stuff for program name, version, email, and documentation
const char *argp_program_version = "croi_proj_euler_solutions v0.1.9";
const char *argp_program_bug_address = "<absolutenico32@gmail.com>";

// Error code when parsing fails
error_t argp_err_exit_status = 69;

static char doc[] =
    "Echoes solutions for projecteuler.net (only from 1 to 17 and 20 right now though)";
static char args_doc[] = "";

static struct argp argp = { option, parse_opt, args_doc, doc, 0, 0, 0 };

int main(int argc, char **argv) {
    // Default arguments
    arguments args;
    args.problem = 1;
    args.verbose = false;
    args.testing = false;

    argp_parse(&argp, argc, argv, ARGP_NO_HELP, 0, &args);

    if (args.testing) {
        printf("Currently testing the sha256 sum of my answers to the sha256 sum of the correct answers...\n");
        args.verbose = false;
    } else {
        printf("Trying to get the function to solve projecteuler's problem #%"PRIdFAST64 "...\n" ,
               args.problem);
    }

    get_function(args.problem, args.verbose, args.testing);
    return 0;
}
