#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "primes.h"

#include "001_dyn_sized_array.h"

struct primes_found {
    bool init;

    int used;
    int size;
    uint64_t *data;
};

static struct primes_found found_primes = {
    .init = false,

    .used = 0,
    .size = 0,
    .data = NULL,
};

static void free_primes_found(void)
{
    Dyn_S_Arr_Free(&found_primes);
    found_primes.init = false;
    found_primes.used = 0;
    found_primes.size = 0;
}

static void init_primes_found(void)
{
    Dyn_S_Arr_Init(&found_primes);
    Dyn_S_Arr_Push_Back(&found_primes, 2);
    Dyn_S_Arr_Push_Back(&found_primes, 3);
    found_primes.init = true;
    atexit(free_primes_found);
}

bool is_prime(uint64_t num)
{
    if (num % 2 == 0 || num < 2)
        return false;

    // Welp if it ain't -le and just -lt it returns true for numbers whose
    // square roots are primes
    for (uint64_t i = 3; i <= sqrt(num); i += 2)
        if (num % i == 0)
            return false;

    return true;
}

uint64_t nth_prime(uint64_t n)
{
    if (!found_primes.init)
        init_primes_found();

    uint64_t res = 0;
    if (n > (uint64_t)found_primes.used) {
        uint64_t prime    = nth_prime(found_primes.used);

        bool keep_finding = true;
        do {
            prime += 2;
            if (is_prime(prime)) {
                Dyn_S_Arr_Push_Back(&found_primes, prime);
                keep_finding = (n > (uint64_t)found_primes.used);
                /*printf("%5d: %lu\n", found_primes.used, prime);*/
            }
        } while (keep_finding);

        res = prime;
    } else {
        res = found_primes.data[n - 1];
    }

    return res;
}
