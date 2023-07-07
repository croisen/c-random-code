#include <math.h>
#include <stdbool.h>


inline bool art_thou_prime(long num) {
    long square_root = (long)sqrt(num);

    for (long i = 2; i <= square_root; i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

inline int reverse_an_integer(int num_1) {
    int remainder = 0, reverse = 0;

    while (num_1 != 0) {
        remainder = num_1 % 10;
        reverse = reverse * 10 + remainder;
        num_1 /= 10;
    }

    return reverse;
}

inline bool is_divisible_by_one_through_n(long number, int divisors) {
    for (int i = 1; i <= divisors; i++) {
        if (number % i != 0) {
            return false;
        }
    }

    return true;
}

