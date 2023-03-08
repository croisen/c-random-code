#include <gmpxx.h> // Needs to be compiled with -lgmp -lgmpxx flags
#include <iostream>


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

        std::cout << "Current power of 2: " << i << ", Current sum of the digits: " << result << std::endl;
        mpz_set_ui(result, 0);
    }

    return 0;
}
