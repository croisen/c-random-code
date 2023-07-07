#include <stdio.h>
#include <gmp.h> // Needs to be compiled with -lgmp flags


int main() {
    mpz_t big_pow_of_two, result, quotient, remainder, num;
    mpz_inits(result, quotient, remainder, num, NULL);
    mpz_init_set_ui(big_pow_of_two, 1);

    for (int i = 1; i <= 1000; i++) {
        mpz_mul_si(big_pow_of_two, big_pow_of_two, 2);
        mpz_set(num, big_pow_of_two);
        while (mpz_sgn(num) != 0) {
            mpz_tdiv_qr_ui(quotient, remainder, num, 10);
            mpz_add(result, result, remainder);
            mpz_set(num, quotient);
        }
        gmp_printf("Current power of 2: %04d, Current sum of each digit in the big exponent of two: %5Zd\n", i, result);
        mpz_set_ui(result, 0);
    }

    return 0;
}
