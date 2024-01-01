#include "../int_manipulation.h"

#include "problem_006_010.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

void problem_6(bool verbose) {
    printf("The sum of the squares of the first ten natural numbers is,\n");
    printf(
        "1^2 + 2^2 + ... + 10^2 = 385. The square of the sum of the first\n");
    printf("ten natural numbers is, (1 + 2 + ... + 10)^2 = 55^2 = 3025\n");
    printf("Hence the difference between the sum of the squares of the\n");
    printf("first ten natural numbers and the square of the sum is 3025 - 385 "
           "= 2640.\n");
    printf("Find the difference between the sum of the squares of the first\n");
    printf("one hundred natural numbers and the square of the sum.\n\n");

    if (verbose) {
        printf("Sum of consecutive numbers 1 to n: (n * (n + 1)) / 2\n");
        printf("Summing the squares of consecutive numbers 1 to n:\n");
        printf("(n * (n + 1) * (2n + 1)) / 2\n\n");
    }

    int64_t res               = 0;
    int64_t square_of_the_sum = i64_pow((100 * 101) / 2, 2);
    int64_t sum_of_squares    = (100 * 101 * 201) / 6;

    res                       = square_of_the_sum - sum_of_squares;

    printf("The difference betweem the sum of the squares of the first one\n");
    printf("hundred natural numbers and the square of the sum is %" PRId64 "\n",
           res);
}

void problem_7(bool verbose) { (void)verbose; }
void problem_8(bool verbose) { (void)verbose; }
void problem_9(bool verbose) { (void)verbose; }
void problem_10(bool verbose) { (void)verbose; }
