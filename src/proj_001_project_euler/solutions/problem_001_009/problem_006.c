#include <inttypes.h>
#include <stdint.h>

#include "003_col_limited_printf.h"
#include "problem_001_009.h"

void problem_006(void)
{
    col_limited_printf(80, 0, "Problem: 006 - Smallest Multiple\n");
    col_limited_printf(
        80, 0,
        "Description: The sum of the squares of the first ten natural numbers "
        "is, 1^2 + 2^2 + ... + 10^2 = 385. The square of the sum of the first "
        "ten natural numbers is,(1 + 2 + ... + 10)^2 = 55^2 = 3025. Hence the "
        "difference between the sum of the squares of the first ten natural "
        "numbers and the square of the sum is 3025 - 385 = 2640.\n"
    );
    col_limited_printf(
        80, 0,
        "Goal: Find the difference between the sum of the squares of the first "
        "one hundred natural numbers and the square of the sum.\n"
    );

    uint64_t res                = 0;
    uint64_t sum_of_the_squares = 0;
    uint64_t squared_sum        = 0;
    for (uint64_t i = 1; i <= 100; i++) {
        squared_sum        += i;
        sum_of_the_squares += (i * i);
    }

    squared_sum *= squared_sum;
    res          = squared_sum - sum_of_the_squares;
    col_limited_printf(80, 0, "Answer: %" PRIu64 "\n\n", res);
}
