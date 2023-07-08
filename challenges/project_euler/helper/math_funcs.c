#include <gmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "math_funcs.h"


void not_implemented(int problem_num) {
    printf("There is no function to solve for problem #%d yet sadly\n", problem_num);
}

bool art_thou_prime(long num) {
    long square_root = (long)sqrt(num);

    for (long i = 2; i <= square_root; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}


bool is_divisible_by_one_through_n(long number, int divisors) {
    for (int i = 1; i <= divisors; i++) {
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
