#include <stdio.h>

#include "math_funcs.h"
#include "problem_001_005.h"
#include "problem_006_010.h"
#include "problem_011_015.h"
#include "problem_016_020.h"
#include "func_exec.h"

/*#define le_case(x) case ##x: problem_##x(verbose); break;*/
#define f(x) function_array[ x - 1 ] = problem_##x


void (*function_array[100]) (bool verbose);
void get_function(int problem_num, bool verbose) {
    /*switch (problem_num) {*/
        /*le_case(  1); le_case(  2); le_case(  3); le_case(  4); le_case(  5);*/
        /*le_case(  6); le_case(  7); le_case(  8); le_case(  9); le_case( 10);*/
        /*le_case( 11); le_case( 12); le_case( 13); le_case( 14); le_case( 15);*/
        /*le_case( 16); le_case( 17); le_case( 18); le_case( 19); le_case( 20);*/
    /*}*/

    f(  1); f(  2); f(  3); f(  4); f(  5);
    f(  6); f(  7); f(  8); f(  9); f( 10);
    f( 11); f( 12); f( 13); f( 14); f( 15);
    f( 16); f( 17); f( 18); f( 19); f( 20);

    if ((problem_num > 20) | (problem_num == 0)) {
        not_implemented(problem_num, verbose);
        return;
    }

    (function_array[problem_num - 1])(verbose);
}
