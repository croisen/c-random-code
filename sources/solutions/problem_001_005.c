#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#include "math_funcs.h"
#include "problem_001_005.h"


long problem_1(bool verbose, bool testing) {
    // Just an if else statement to check if a number is divisible by  3 or 5
    // Then summing it all up

    int result = 0;

    if (!testing){
        printf("Summing up all numbers below 1000 that is evenly divisble by 3 or 5\n");
    }

    for (int i = 3; i <= 999; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            result =  result + i;

            if (verbose) {
                printf("%d = %d + %d\n", result, (result - i), i);
            }
        }
    }

    if (!testing) {
        printf("The sum of all numbers that are evenly divisible by 3 or 5 that is under 1000 is: %d\n", result);
    }

    return (long)result;
}

long problem_2(bool verbose, bool testing) {
    // The fibonacci sequence, then checking if the number from said sequence is even
    // Then summing it all up

    int a = 1, b = 2, c = 0, result = 0;

    if (!testing) {
        printf("Currently summing up all the even fibonacci numbers below 4 million...\n");
    }

    while (a < 4000000) {
        if (a % 2 == 0 && a < 4000000) {
            result = result + a;

            if (verbose) {
                printf("result=%7d, even_fib=%7d\n", result, a);
            }
        }

        c = a + b;
        a = b;
        b = c;
    }

    if (!testing) {
        printf("The sum of all even fibonacci numbers under 4 million is: %d\n", result);
    }

    return (long)result;
}

long problem_3(bool verbose, bool testing) {
    // Have a function that checks if a number is prime, after that we try to divide it to the
    // Big number, if there's no remainder then it's a prime factor.
    // We just have an iterator that goes from two (cause everything's divisible by 1) up to
    // the square root of the big number

    long big_number = 600851475143;
    long highest_prime = 0;
    long square_root = sqrt(big_number);

    if (!testing) {
        printf("Currently looking for the largest prime factor of %ld...\n", big_number);
    }

    for (long x = 2; x <= square_root; x++) {
        if (art_thou_prime(x) && big_number % x == 0) {
            if (verbose) {
                printf("Current highest prime: %ld\n", x);
            }

            highest_prime = x;
        }
    }
    if (!testing) {
        printf("The largest prime factor of %ld is %ld\n", big_number, highest_prime);
    }

    return highest_prime;
}

long problem_4(bool verbose, bool testing) {
    // Testing for palindrome products by iterating two numbers from 100 to 999
    // then checking if it's higher than the previous palindrome product

    int x_times_y = 0;
    int reversed_product;
    int highest_palindrome = 0;

    if (!testing) {
        printf("Currently finding the highest palindrome product made by multiplying two 3 digit numbers\n");
        printf("Palindrome definition: it is a word, number, phrase, or other sequence of symbols that\nreads the same backwards as forwards, such as madam or racecar, and the date and time\n12/21/33 12:21.\n");
    }

    for (int x = 100; x <= 999; x++) {
        for (int y = 100; y <= 999; y++) {
            x_times_y = x * y;
            reversed_product = reverse_an_integer(x_times_y);

            if (x_times_y == reversed_product) {
                if (x_times_y > highest_palindrome) {
                    highest_palindrome = x_times_y;

                    if (verbose) {
                        printf("Current highest palindrome: %d\n", highest_palindrome);
                    }
                }
            }
        }
    }

    if (!testing) {
        printf("Highest palindrome product by two 3 digit numbers: %d\n", highest_palindrome);
    }

    return (long)highest_palindrome;
}

long problem_5(bool verbose, bool testing) {
    // Has a while loop that stops if the function that checks if a number is divisible
    // by 1 through 20 returns true

    bool continue_loop = true;
    int divisors = 20;
    long x = divisors;

    if (!testing) {
        printf("Currently testing for a number that is evenly divisible by 1 through 20\n");
    }

    if (verbose) {
        printf("You've set verbose to true, this is gonna take some time so I'mma give the answer first then start brute forcing for it: 232792560\n");
    }

    while (continue_loop) {
        if (verbose) {
            printf("\rCurrent number: %ld", x);
        }

        if (is_divisible_by_one_through_n(x, divisors) && !testing) {
            printf("\nLowest number that is evenly divisible by 1 to %d is %ld\n", divisors, x);
            continue_loop = false;
        } else if (is_divisible_by_one_through_n(x, divisors)) {
            continue_loop = false;
        } else {
            x += divisors;
        }
    }

    return (long)x;
}
