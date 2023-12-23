#include "extras/args.h"
#include "extras/caller.h"

#include <argp.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>


arguments args = {
    .verbose = false,
    .problem_num = 0
};

int main(int argc, char **argv) {
    argp_parse(&argp, argc, argv, ARGP_NO_HELP, 0, &args);

    printf("Trying to call the function for the problem from\n");
    printf("https://projecteuler.net/problem=%"PRId64"\n\n", args.problem_num);
    call_func(args.problem_num, args.verbose);
    return EXIT_SUCCESS;
}
