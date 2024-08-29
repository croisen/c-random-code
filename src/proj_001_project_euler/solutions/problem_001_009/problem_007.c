#include <inttypes.h>
#include <stdint.h>

#include "003_col_limited_printf.h"
#include "problem_001_009.h"

#include "../../utils/primes.h"

void problem_007(void)
{
    col_limited_printf(80, 0, "Problem: 007 - 10001st Prime\n");
    col_limited_printf(
        80, 0,
        "Description: By listing the first six prime numbers: 2, 3, 5, 7, 11, "
        "and 13, we can see that the 6th prime is 13.\n"
    );
    col_limited_printf(80, 0, "Goal: What is the 10,001st prime number?\n");

    uint64_t res = nth_prime(10001);
    col_limited_printf(80, 0, "Answer: %" PRIu64 "\n\n", res);
}
