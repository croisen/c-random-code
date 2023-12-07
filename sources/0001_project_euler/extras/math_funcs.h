#ifndef CROI_MATH_FUNCS
#define CROI_MATH_FUNCS

#include <gmp.h>
#include <inttypes.h>
#include <math.h>
#include <openssl/evp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void not_implemented(int_fast64_t problem_num, bool verbose, bool testing);

bool art_thou_prime(int_fast64_t num);
bool is_divisible_by_one_through_n(int_fast64_t number, int_fast64_t divisors);

int_fast64_t collatz_chain(int_fast64_t num);
int_fast64_t compare_num(int_fast64_t left, int_fast64_t right);
int_fast64_t reverse_an_integer(int_fast64_t num);
int_fast64_t combinatorial(int_fast64_t n, int_fast64_t r);

char *num_to_char(int_fast64_t num);
char *sha256_digest(char *number_string);

#endif
