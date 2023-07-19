#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "math_funcs.h"
#include "problem_006_010.h"


long problem_6(bool verbose, bool testing) {
    int number_of_natural_numbers = 100;
    int squared_sum = 0;
    int sum_of_squared = 0;
    int result = 0;

    if (!testing) {
        printf("Currently getting the sum of every natural number below 100, then squaring said sum...\n");
        printf("Currently getting the sum of all natural numbers squared, below 100...\n");
        printf("Now subtracting them together...\n");
    }

    for (int i = 1; i <= number_of_natural_numbers; i++) {
        squared_sum += i;
        sum_of_squared += (i * i);
    }

    squared_sum = squared_sum * squared_sum;
    result = squared_sum - sum_of_squared;

    if (verbose) {
        printf("Sum of natural numbers: %g, Squared: %g^2 = %d\n", sqrt(squared_sum), sqrt(squared_sum), squared_sum);
        printf("Sum of the squared natural numbers: %d\n", sum_of_squared);
        printf("%d - %d =\n", squared_sum, sum_of_squared);
    }
    if (!testing) {
        printf("Answer: %d\n", result);
    }

    return (long)result;
}


long problem_7(bool verbose, bool testing) {
    int target_prime_count = 10001;
    int prime_count = 0;
    int x = 2;

    if (!testing) {
        printf("Currently counting for the 10001st prime number...\n");
    }

    while (prime_count <= target_prime_count) {
        if (art_thou_prime(x)) {
            if (verbose) {
                printf("Current prime number: %d, prime count: %d\n", x, prime_count);
            }

            prime_count++;
        }

        if (prime_count == target_prime_count) {
            if (!testing) {
                printf("The 10001st prime number is: %d\n", x);
            }

            break;
        }

        x++;
    }
    return (long)x;
}

long problem_8(bool verbose, bool testing) {
    char scary_long_num[] = "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450";
    char one_char[2]; one_char[1] = '\0';
    int atoi_out = 0;
    int digit_length = 13;
    long result = 0, highest_result = 0;

    if (!testing) {
        printf("Currently trying to find 13 adjacent digits whose product is the highest,\n");
        printf("from this number %s\n", scary_long_num);
    }

    for (int i = 0; i <= ((int)strlen(scary_long_num) - digit_length); i++) {
        result = 1;

        for (int j = 0; j < digit_length; j++) {
            one_char[0] = scary_long_num[i + j]; // Get one char from the long num
            atoi_out = atoi(one_char); // Turn to int
            result *= atoi_out; // Multiply them together
            
            if (verbose) {
                printf("%s", one_char);
            }
        }

        if (result > highest_result) {
            highest_result = result;

        }

        if (verbose) {
            printf(" -> Product: %11ld, Current highest product: %11ld\n",
                   result, highest_result);
        }

    }

    if (!testing) {
        printf("Biggest product in 13 adjacent numbers in the bignum is: %ld\n", highest_result);
    }

    return highest_result;
}

long problem_9(bool verbose, bool testing) {
    int a_sqared = 0, b_squared = 0, c_squared = 0, ans = 0;

    if (!testing) {
        printf("Looking for a pythagorean triplet where it's sum is 1000, and their product is high\n");
    }

    for (int c = 2; c <=999; c++) {
        for (int b = 2; b <= 999; b++) {
            for (int a = 2; a <= 999; a++) {
                if (a + b + c == 1000){
                    a_sqared = a * a;
                    b_squared = b * b;
                    c_squared = c * c;
                }


                if (a + b + c == 1000 && a_sqared + b_squared == c_squared) {
                    ans = a*b*c;
                    if (!testing) {
                        printf("The Pythagorean triplet where a + b + c is equal to 1000, the product of a, b, and c is: %d\n", ans);
                    }

                    if (verbose) {
                        printf("Said pythagorean triplet is a=%d, b=%d, c=%d\n", a, b, c);
                    }

                }
            }
        }
    }

    return (long)ans;
}

long problem_10(bool verbose, bool testing) {
    long result = 0;

    if (!testing) {
        printf("Currently summing up all the prime numbers below 2 million...\n");
    }

    for (int i = 2; i < 2000000; i++) {
        if (art_thou_prime(i) && i < 2000000) {
            if (verbose) {
                printf("Current prime number: %d\n", i);
            }

            result += i;
        }
    }

    if (!testing) {
        printf("The sum of all prime numbers below 2 million is %ld\n", result);
    }

    return result;
}
