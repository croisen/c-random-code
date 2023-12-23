#include "caller.h"
#include "solutions/problem_001_005.h"

#include <inttypes.h>
#include <stdio.h>

#define call(x)                                                                \
    case x: {                                                                  \
        problem_##x(verbose);                                                  \
        break;                                                                 \
    }

void call_func(int64_t problem_num, bool verbose) {
    switch (problem_num) {
        call(1) call(2) call(3) call(4) call(5)

            default : {
            (void)printf("Currently I have no solution for problem #%" PRId64
                         "\n",
                         problem_num);
        }
    }
}
