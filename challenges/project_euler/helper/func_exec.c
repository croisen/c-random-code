#include <stdio.h>

#include "math_funcs.h"
#include "problem_001_005.h"
#include "problem_006_010.h"
#include "func_exec.h"


void (*function_array[15]) (bool verbose);
#define f(x) function_array[ x - 1 ] = problem_##x

void get_function(int problem_num, bool verbose) {
    f(1); f(2); f(3); f(4); f(5);
    f(6); f(7); f(8); f(9); f(10);

    /*f(11); f(12); f(13); f(14); f(15);*/

    if ((problem_num > 10) | (problem_num == 0)) {
        not_implemented(problem_num);
        return;
    }

    (function_array[problem_num - 1])(verbose);
}
