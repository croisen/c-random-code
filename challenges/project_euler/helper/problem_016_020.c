#include <gmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "math_funcs.h"
#include "problem_016_020.h"


long problem_16(bool verbose, bool testing) {
    if (!testing) {
        printf("Currently summing up the digits in 2^1000...\n");
    }

    mpz_t two, result, a;
    mpz_inits(two, result, a, NULL);
    mpz_ui_pow_ui(two, 2, 1000);

    if (verbose) {
        gmp_printf("2^1000 = %Zd\n", two);
    }

    while (mpz_cmp_si(two, 0)) {
        mpz_mod_ui(a, two, 10);
        mpz_add(result, result, a);
        mpz_div_ui(two, two, 10);

        if (verbose) {
            gmp_printf("Current sum of digits: %Zd, two^100 status: %Zd\n", result, two);
        }
    }

    if (!testing) {
        gmp_printf("The sum of all the digits of 2^1000 is: %Zd\n", result);
    }

    long x = (long)mpz_get_ui(result);
    return x;
}

long problem_17(bool verbose, bool testing) {
    char *ones[] = {
        "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
        "sixteen", "seventeen", "eighteen", "nineteen"
    };

    char *tens[] = {
        "", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    char *unit[] = {
        "and", "hundred", "thousand"
    };

    if (!testing) {
        printf("Currently getting the number of letters used by the numbers 1 to 1 thousand.\n");
        printf("Sample: if the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.\n");
    }

    int total_number_of_letters = 0, number_of_letters = 0;

    for (int i = 1; i <= 1000; i++) {
        if (i < 20) {
            number_of_letters = strlen(ones[i]);
            if (verbose) {
                printf("Current number = %4d, number of letters = %3d -> %s\n",
                       i, number_of_letters, ones[i]);
            }

            total_number_of_letters += number_of_letters;
            continue;
        }

        if ((20 <= i) && (i < 100)) {
            number_of_letters = strlen(tens[i / 10]) + strlen(ones[i % 10]);
            if (verbose) {
                printf("Current number = %4d, number of letters = %3d -> %s %s\n",
                       i, number_of_letters, tens[i / 10], ones[i % 10]);
            }

            total_number_of_letters += number_of_letters;
            continue;
        }

        if ((100 <= i) && (i < 1000)) {
            if (i % 100 != 0) {
                if (((i % 100) > 19)) {
                    number_of_letters = 
                        strlen(ones[i / 100]) + strlen(unit[1]) + strlen(unit[0]) +  // x hundred and...
                        strlen(tens[(i % 100) / 10]) + strlen(ones[(i % 100) % 10]); // tens and ones place

                    if (verbose) {
                        printf("Current number = %4d, number of letters = %3d -> %s %s %s %s %s\n",
                               i, number_of_letters, ones[i / 100], unit[1], unit[0],
                               tens[(i % 100) / 10], ones[(i % 100) % 10]);
                    }
                } else {
                    number_of_letters =
                        strlen(ones[i / 100]) + strlen(unit[1]) + strlen(unit[0]) +
                        strlen(ones[(i % 100)]);

                    if (verbose) {
                        printf("Current number = %4d, number of letters = %3d -> %s %s %s %s\n",
                               i, number_of_letters, ones[i / 100], unit[1], unit[0],
                               ones[(i % 100)]);
                    }
                }
                total_number_of_letters += number_of_letters;
                continue;
            } else {
                number_of_letters = strlen(ones[i / 100]) + strlen(unit[1]);
                if (verbose) {
                    printf("Current number = %4d, number of letters = %3d -> %s %s\n",
                           i, number_of_letters, ones[i / 100], unit[1]);
                }

                total_number_of_letters += number_of_letters;
                continue;
            }
        }

        if (i == 1000) {
            number_of_letters = strlen(ones[i / 1000]) + strlen(unit[2]);

            if (verbose) {
                printf("Current number = %4d, number of letters = %3d -> %s %s\n",
                       i, number_of_letters, ones[i / 1000], unit[2]);
            }
            total_number_of_letters += number_of_letters;
        }
    }

    if (!testing) {
        printf("The total number of letters used by the numbers one to one thousand is: %d\n",
            total_number_of_letters);
    }
    return (long)total_number_of_letters;
}

long problem_18(bool verbose, bool testing) {
    not_implemented(18, verbose, testing);
    return 0;
}

long problem_19(bool verbose, bool testing) {
    not_implemented(19, verbose, testing);
    return 0;
}

long problem_20(bool verbose, bool testing) {
    not_implemented(20, verbose, testing);
    return 0;
}
