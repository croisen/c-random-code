#include <stdint.h>
#include <stdbool.h>

#include "numbers.h"

uint64_t reverse_num(uint64_t num)
{
    uint64_t res = 0;
    do {
        res *= 10;
        res += num % 10;
        num /= 10;
    } while (num);

    return res;
}

bool is_evenly_divisible_from_1_to_n(uint64_t num, uint64_t n) {
    for (uint64_t i = 1; i <= n; i ++) {
        if (num % i != 0)
            return false;
    }

    return true;
}
