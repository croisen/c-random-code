#include <stdbool.h>

#ifndef CROI_MATH_FUNCS
#define CROI_MATH_FUNCS

void not_implemented(int problem_num);

bool art_thou_prime(long num);
bool is_divisible_by_one_through_n(long number, int divisors);

int collatz_chain(long num);
int reverse_an_integer(int num);

long combinatorial(long n, long r);

#endif
