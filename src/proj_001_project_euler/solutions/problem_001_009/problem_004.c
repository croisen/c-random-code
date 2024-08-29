#include <inttypes.h>
#include <stdint.h>

#include "003_col_limited_printf.h"
#include "problem_001_009.h"

#include "../../utils/numbers.h"

void problem_004(void)
{
    col_limited_printf(80, 0, "Problem: 004 - Largest Palindrome Product\n");
    col_limited_printf(
        80, 0,
        "Description: A palindromic number reads the same both ways. The "
        "largest palindrome made from the product of two 2-digit numbers is "
        "9009 = 91 times 99.\n"
    );
    col_limited_printf(
        80, 0,
        "Goal: Find the largest palindrome made from the product of two "
        "3-digit numbers.\n"
    );

    uint64_t res = 0;
    for (uint64_t i = 900; i < 1000; i++) {
        for (uint64_t j = 900; j < 1000; j++) {
            uint64_t product = i * j;
            uint64_t reverse = reverse_num(product);
            if (product == reverse && product > res)
                res = product;
        }
    }

    col_limited_printf(80, 0, "Answer: %" PRIu64 "\n\n", res);
}
