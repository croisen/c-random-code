#include <inttypes.h>
#include <stdint.h>

#include "003_col_limited_printf.h"
#include "problem_001_009.h"

#include "../../utils/numbers.h"

void problem_005(void)
{
    col_limited_printf(80, 0, "Problem: 005 - Smallest Multiple\n");
    col_limited_printf(
        80, 0,
        "Description: 2520 is the smallest number that can be divided by each "
        "of the numbers from 1 to 10 without any remainder.\n"
    );
    col_limited_printf(
        80, 0,
        "Goal: What is the smallest positive number that is evenly divisible "
        "with no remainder by all of the numbers from 1 to 20?\n"
    );

    uint64_t divisors = 20; // 1 to 20
    uint64_t res      = divisors;
    while (true) {
        if (is_evenly_divisible_from_1_to_n(res, divisors))
            break;

        res += divisors;
    }

    col_limited_printf(80, 0, "Answer: %" PRIu64 "\n\n", res);
}
