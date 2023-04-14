#include <iomanip>
#include <iostream>
#include <mpfr.h> // Must be compiled with the -lgmp -lmpfr flags


void natural_probability_of_x(mpfr_t result, mpfr_t pi, mpfr_t e, mpfr_t x, mpfr_t a) {
    mpfr_mul(a, x, x, MPFR_RNDD);
    mpfr_div_ui(a, a, 2, MPFR_RNDD);
    mpfr_neg(a, a, MPFR_RNDD);
    mpfr_pow(a, e, a, MPFR_RNDD);
    mpfr_mul_ui(result, pi, 2, MPFR_RNDD);
    mpfr_div(result, a, result, MPFR_RNDD);
    mpfr_set_ui(a, 0, MPFR_RNDD);
}

void integral_of_probability_of_x(mpfr_t result, mpfr_t pi, mpfr_t e, mpfr_t x, mpfr_t a, mpfr_t b) {
    mpfr_set_str(a, "-100.00", 10, MPFR_RNDD);
    for (a; mpfr_cmp(a, x) < 1; mpfr_add_d(a, a, 0.0001, MPFR_RNDD)) {
        natural_probability_of_x(result, pi, e, a, b);
        mpfr_mul_d(result, result, 0.0001, MPFR_RNDD);
        mpfr_add(b, b, result, MPFR_RNDD);
    }
    mpfr_set(result, b, MPFR_RNDD);
    mpfr_set_ui(a, 0, MPFR_RNDD);
    mpfr_set_ui(b, 0, MPFR_RNDD);
}

int main() {
    int base = 10;
    mpfr_t result, pi_number, euler_num, a, b, x, y, z;
    mpfr_inits2(512, result, pi_number, euler_num, a, b, x, y, z, (mpfr_ptr) NULL);
    mpfr_set_str(x, "-4.00", base, MPFR_RNDD);
    mpfr_set_str(pi_number, "3.14159265358979323846264338327950288419716939937510", base, MPFR_RNDD);
    mpfr_set_str(euler_num, "2.71828182845904523536028747135266249775724709369995", base, MPFR_RNDD);
    integral_of_probability_of_x(result, pi_number, euler_num, x, a, b);
    mpfr_printf("%.10RNF\n", result);
    mpfr_clears(result, pi_number, euler_num, a, b, x, y, z, (mpfr_ptr) NULL);
}
