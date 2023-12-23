#include "prime_check.h"

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

bool is_prime(int64_t num) {
    if (num % 2 == 0) {
        return false;
    }

    for (int64_t i = 3; i < sqrt(num); i += 2) {
        if (num % i == 0) {
            return false;
        }
    }

    return true;
}

int64_t highest_prime_factor(int64_t num) {
    int64_t res = 2;

    for (int64_t i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0 && is_prime(i)) {
            res = i;
        }
    }

    return res;
}
