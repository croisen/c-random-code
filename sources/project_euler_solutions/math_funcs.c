#include <gmp.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "math_funcs.h"


void not_implemented(int problem_num, bool verbose, bool testing) {
    if (!testing) {
        printf("There is no function to solve for problem #%d yet sadly, also verbose is set to: %d\n", problem_num, verbose);
    }
}

bool art_thou_prime(long num) {
    long square_root = (long)sqrt(num);

    if (num == 1)                     { return false; }
    if ((num % 2 == 0) && (num != 2)) { return false; }

    for (long i = 3; i <= square_root; i += 2) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}


bool is_divisible_by_one_through_n(long number, long divisors) {
    for (long i = 2; i <= divisors; i++) {
        if (number % i != 0) {
            return false;
        }
    }

    return true;
}

int collatz_chain(long num) {
    int chain_count = 1;

    while (num != 1) {
        if (num % 2 == 0) {
            num = num / 2;
            chain_count++;
        } else {
            num = (3 * num) + 1;
            chain_count++;
        }
    }
    return chain_count;
}

int compare_num(int left, int right) {
    if (left > right) {
        return 0;
    } else if (left < right) {
        return 1;
    } else {
        return 2; // I sure do hope this does not happen for problem 18 and 67
    }
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

long combinatorial(long n, long r) {
    mpz_t n1, C, r1;
    mpz_inits(n1, C, r1, NULL);
    mpz_fac_ui(n1, n);
    mpz_fac_ui(r1, r);
    mpz_set_ui(C, n - r);
    mpz_fac_ui(C, mpz_get_si(C));

    mpz_mul(C, C, r1);
    mpz_div(n1, n1, C);
    long result = mpz_get_si(n1);
    mpz_clears(n1, C, r1, NULL);

    return result;
}

unsigned char *num_to_char(long num) {
    long m = num, digits = 0;

    while (m) {
        digits++;
        m /= 10;
    }

    unsigned char *arr = (unsigned char *)malloc(digits + 1);
    int index = digits - 1;

    while (num) {
        arr[index--] = (num % 10) + '0';
        num /= 10;
    }

    return arr;
}