#include <stdio.h>


void (*function_array[10]) (void);
#define f(x) function_array[ x - 1 ] = problem_##x

void get_function(int problem_num) {
    f(1);
    f(2);
    f(3);
    f(4);
    f(5);
    f(6);
    f(7);
    f(8);
    f(9);
    f(10);

    if (problem_num > 10) {
        printf("Problem number %d is not implemented yet\n", problem_num);
        return;
    } else if (problem_num == 0) {
        printf("I do not have a solution for problem 0 sadly\n");
        return;
    }

    (function_array[problem_num - 1])();
}
