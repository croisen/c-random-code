#include <inttypes.h>
#include <math.h>
#include <stdint.h>

#include "003_col_limited_printf.h"
#include "problem_001_009.h"

#include "../../utils/primes.h"

void problem_003(void)
{
    col_limited_printf(80, 0, "Problem: 003 - Largest Prime Factor\n");
    col_limited_printf(
        80, 0, "Description: The prime factors of 13195 are 5, 7, 13 and 29.\n"
    );
    col_limited_printf(
        80, 0,
        "Goal: What is the largest prime factor of the number 600851475143?\n"
    );

    uint64_t big_evil = 600851475143;
    uint64_t res      = 0;
    for (uint64_t i = 3; i < sqrt(big_evil); i += 2)
        if (is_prime(i) && big_evil % i == 0)
            res = i;

    col_limited_printf(80, 0, "Answer: %" PRIu64 "\n\n", res);
}
