#include <stdio.h>


void problem_1(void) {
    int result = 0;

    printf("Summing up all numbers below 1000 that is evenly divisble by 3 or 5\n");
    for (int i = 3; i <= 999; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            result =  result + i;            
        }
    }

    printf("The sum of all numbers that are evenly divisible by 3 or 5 that is under 1000 is: %d\n", result);
}

void problem_2(void) {
    int a = 1, b = 2, c = 0, result = 0;

    printf("Currently summing up all the even fibonacci numbers below 4 million...");
    while (a < 4000000) {
        if (a % 2 == 0 && a < 4000000) {
            result = result + a;
        }

        c = a + b;
        a = b;
        b = c;
    }

    printf("The sum of all even fibonacci numbers under 4 million is: %d\n", result);
}

void problem_3(void) {
    long big_number = 600851475143;
    long highest_prime = 0;
    long square_root = sqrt(big_number);

    printf("Currently looking for the largest prime factor of %ld...\n", big_number);
    for (long x = 2; x <= square_root; x++) {
        if (art_thou_prime(x) && big_number % x == 0) {
            highest_prime = x;
        }
    }

    printf("The largest prime factor of %ld is %ld\n", big_number, highest_prime);
}

void problem_4(void) {
    int x_times_y = 0;
    int reversed_product;
    int highest_palindrome = 0;

    printf("Currently finding the highest palindrome product made by multiplying two 3 digit numbers\n");
    printf("Palindrome definition: it is a word, number, phrase, or other sequence of symbols that reads the same backwards as forwards, such as madam or racecar, and the date and time 12/21/33 12:21.\n");

    for (int x = 100; x <= 999; x++) {
        for (int y = 100; y <= 999; y++) {
            x_times_y = x * y;
            reversed_product = reverse_an_integer(x_times_y);

            if (x_times_y == reversed_product) {
                if (x_times_y > highest_palindrome) {
                    highest_palindrome = x_times_y;
                }
            }
        }
    }

    printf("Highest palindrome product by two 3 digit numbers: %d\n", highest_palindrome);
}

void problem_5(void) {
    int continue_loop = 0;
    int divisors = 20;
    long x = divisors;
    printf("Currently testing for a number that is evenly divisible by 1 through 20\n");

    while (continue_loop == 0) {
        if (is_divisible_by_one_through_n(x, divisors)) {
            printf("Lowest number that is evenly divisible by 1 to %d is %ld\n", divisors, x);
            continue_loop = 1;
        }
        x = x + 1;
    }
}
