#include <inttypes.h>
#include <stdint.h>

#include "003_col_limited_printf.h"
#include "problem_010_019.h"

#include "../../utils/primes.h"

void problem_010(void)
{
    col_limited_printf(80, 0, "Problem 010 - Summation of Primes\n");
    col_limited_printf(
        80, 0, "The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.\n"
    );
    col_limited_printf(
        80, 0, "Find the sum of all the primes below two million.\n"
    );

    uint64_t res = 2;
    for (uint64_t i = 3; i < 2000000; i += 2)
        if (is_prime(i))
            res += i;

    col_limited_printf(80, 0, "Answer: %" PRIu64 "\n\n", res);
}
