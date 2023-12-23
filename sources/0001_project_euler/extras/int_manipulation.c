#include "int_manipulation.h"

#include <stdbool.h>
#include <stdint.h>

int64_t i64_reverse(int64_t num) {
    int64_t res = 0;

    while (num) {
        res = (res * 10) + (num % 10);
        num /= 10;
    }

    return res;
}

bool is_divisible_by_1_through_n(int64_t num, int64_t n) {
    if (n == 2 && num % n != 0) {
        return false;
    }

    for (int64_t i = 3; i <= n; i += 1) {
        if (num % i != 0) {
            return false;
        }
    }

    return true;
}
