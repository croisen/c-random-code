#include <inttypes.h>
#include <stdint.h>

#include "003_col_limited_printf.h"
#include "problem_001_009.h"

void problem_001(void)
{
    col_limited_printf(80, 0, "Problem: 001 - Multiples of 3 or 5\n");
    col_limited_printf(
        80, 0,
        "Description: If we list all the natural numbers below 10 that are "
        "multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these "
        "multiples is 23\n"
    );
    col_limited_printf(
        80, 0, "Goal: Find the sum of all the multiples of 3 or 5 below 1000.\n"
    );

    uint64_t res = 0;
    for (int i = 3; i < 1000; i++)
        res += i * (i % 3 == 0 || i % 5 == 0);

    col_limited_printf(80, 0, "Answer: %" PRIu64 "\n\n", res);
}
