#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "math_funcs.h"

bool art_thou_prime(long num) {
    long square_root = (long)sqrt(num);

    for (long i = 2; i <= square_root; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int reverse_an_integer(int num) {
    int remainder = 0, reverse = 0;

    while (num != 0) {
        remainder = num % 10;
        reverse = reverse * 10 + remainder;
        num /= 10;
    }

    return reverse;
}

bool is_divisible_by_one_through_n(long number, int divisors) {
    for (int i = 1; i <= divisors; i++) {
        if (number % i != 0) {
            return false;
        }
    }

    return true;
}

void not_implemented(int problem_num) {
    printf("There is no function to solve for problem #%d yet sadly\n", problem_num);
}
