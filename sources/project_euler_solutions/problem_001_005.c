#include "math_funcs.h"
#include "problem_001_005.h"

char *problem_1(bool verbose, bool testing) {
    // Just an if else statement to check if a number is divisible by  3 or 5
    // Then summing it all up

    int_fast64_t result = 0;

    if (!testing){
        printf("Summing up all numbers below 1000 that is evenly divisble by 3 or 5\n");
    }

    for (int_fast64_t i = 3; i <= 999; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            result =  result + i;

            if (verbose) {
                printf("%"PRIdFAST64" = %"PRIdFAST64" + %"PRIdFAST64"\n", result, (result - i), i);
            }
        }
    }

    if (!testing) {
        printf("The sum of all numbers that are evenly divisible by 3 or 5 that is under 1000 is: %"PRIdFAST64"\n",
               result);
    }

    return num_to_char(result);
}

char *problem_2(bool verbose, bool testing) {
    // The fibonacci sequence, then checking if the number from said sequence is even
    // Then summing it all up

    int_fast64_t a = 1, b = 2, c = 0, result = 0;

    if (!testing) {
        printf("Currently summing up all the even fibonacci numbers below 4 million...\n");
    }

    while (a < 4000000) {
        if (a % 2 == 0 && a < 4000000) {
            result = result + a;

            if (verbose) {
                printf("result=%7ld, even_fib=%7ld\n", result, a);
            }
        }

        c = a + b;
        a = b;
        b = c;
    }

    if (!testing) {
        printf("The sum of all even fibonacci numbers under 4 million is: %"PRIdFAST64"\n", result);
    }

    return num_to_char(result);
}

char *problem_3(bool verbose, bool testing) {
    // Have a function that checks if a number is prime, after that we try to divide it to the
    // Big number, if there's no remainder then it's a prime factor.
    // We just have an iterator that goes from two (cause everything's divisible by 1) up to
    // the square root of the big number

    int_fast64_t big_number = 600851475143;
    int_fast64_t highest_prime = 0;
    int_fast64_t square_root = sqrt(big_number);

    if (!testing) {
        printf("Currently looking for the largest prime factor of %"PRIdFAST64"...\n", big_number);
    }

    for (int_fast64_t x = 2; x <= square_root; x++) {
        if (art_thou_prime(x) && big_number % x == 0) {
            if (verbose) {
                printf("Current highest prime: %"PRIdFAST64"\n", x);
            }

            highest_prime = x;
        }
    }
    if (!testing) {
        printf("The largest prime factor of %"PRIdFAST64" is %"PRIdFAST64"\n", big_number, highest_prime);
    }

    return num_to_char(highest_prime);
}

char *problem_4(bool verbose, bool testing) {
    // Testing for palindrome products by iterating two numbers from 100 to 999
    // then checking if it's higher than the previous palindrome product

    int_fast64_t x_times_y = 0, reversed_product = 0, highest_palindrome = 0;

    if (!testing) {
        printf("Currently finding the highest palindrome product made by multiplying two 3 digit numbers\n");
        printf("Palindrome definition: it is a word, number, phrase, or other sequence of symbols that\nreads the same backwards as forwards, such as madam or racecar, and the date and time\n12/21/33 12:21.\n");
    }

    for (int_fast64_t x = 100; x <= 999; x++) {
    for (int_fast64_t y = 100; y <= 999; y++) {
        x_times_y = x * y;
        reversed_product = reverse_an_integer(x_times_y);

        if (x_times_y == reversed_product) {
            if (x_times_y > highest_palindrome) {
                highest_palindrome = x_times_y;

                if (verbose) {
                    printf("Current highest palindrome: %"PRIdFAST64"\n", highest_palindrome);
                }
            }
        }
    }
    }

    if (!testing) {
        printf("Highest palindrome product by two 3 digit numbers: %"PRIdFAST64"\n", highest_palindrome);
    }

    return num_to_char(highest_palindrome);
}

char *problem_5(bool verbose, bool testing) {
    // Has a while loop that stops if the function that checks if a number is divisible
    // by 1 through 20 returns true

    int_fast64_t divisors = 20;
    int_fast64_t i = divisors;

    if (!testing) {
        printf("Currently testing for a number that is evenly divisible by 1 through 20\n");
    }

    while (true) {
        if (verbose && i % 1000 == 0) {
            printf("\rCurrent number: %"PRIdFAST64"", i);
        }
        if (is_divisible_by_one_through_n(i, divisors)) {
            if (!testing) {
                printf("\nLowest number that is evenly divisible by 1 to %"PRIdFAST64" is %"PRIdFAST64"\n",
                       divisors, i);
            }
            break;
        }
        i += divisors;
    }
    return num_to_char(i);
}
