#include <inttypes.h>
#include <stdint.h>

#include "003_col_limited_printf.h"
#include "problem_001_009.h"

void problem_009(void)
{
    col_limited_printf(80, 0, "Problem: 009 - Special Pythagorean Triplet\n");
    col_limited_printf(
        80, 0,
        "Description: A Pythagorean triplet is a set of three natural numbers, "
        "a < b < c, for which, a^2 + b^2 = c^2. For example, 3^2 + 4^2 = 9 + "
        "16 = 25 = 5^2.\n"
    );
    col_limited_printf(
        80, 0,
        "Goal: There exists exactly one Pythagorean triplet for which a + b + "
        "c = 1000. Find the product abc.\n"
    );

    uint64_t res = 0;
    for (uint64_t c = 100; c < 1000; c++) {
        for (uint64_t b = 100; b < c; b++) {
            for (uint64_t a = 100; a < b; a++) {
                uint64_t a_sq = a * a;
                uint64_t b_sq = b * b;
                uint64_t c_sq = c * c;
                if (a_sq + b_sq == c_sq && a + b + c == 1000) {
                    res = a * b * c;
                    goto end;
                }
            }
        }
    }

end:
    col_limited_printf(80, 0, "Answer: %" PRIu64 "\n\n", res);
}
