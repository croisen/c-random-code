#include <cassert>
#include <iomanip>
#include <iostream>
#include <mpfr.h> // Must be compiled with the -lgmp -lmpfr flags


void integral_of_probability_of_x(mpfr_t result, mpfr_t pi, mpfr_t euler_num, mpfr_t x) {
    mpfr_t a, b;
    mpfr_inits2(512, a, b, (mpfr_ptr) NULL);
    mpfr_set_str(a, "-4.50", 10, MPFR_RNDD);

    mpfr_mul(result, x, x, MPFR_RNDD); // x^2
    mpfr_div_ui(result, result, 2, MPFR_RNDD); // x^2 / 2
    mpfr_neg(result, result, MPFR_RNDZ); // -(x^2/2)
    mpfr_pow(result, euler_num, result, MPFR_RNDD); // e ^ (previous line)
    mpfr_abs(b, x, MPFR_RNDD);
    mpfr_log(b, b, MPFR_RNDD); // ln(|x|)
    mpfr_mul(b, b, result, MPFR_RNDD); // the natural log times line 14's result

    mpfr_mul(result, a, a, MPFR_RNDD); // a^2
    mpfr_div_ui(result, result, 2, MPFR_RNDD); // a^2 / 2
    mpfr_neg(result, result, MPFR_RNDD); // multiply the result to -1
    mpfr_pow(result, euler_num, result, MPFR_RNDD); // e ^ (previous line)
    mpfr_abs(a, a, MPFR_RNDD);
    mpfr_log(a, a, MPFR_RNDD); // ln(|a|)
    mpfr_mul(a, a, result, MPFR_RNDD); // previous line times line 22

    mpfr_mul_ui(result, pi, 2, MPFR_RNDD); // 2pi
    mpfr_sqrt(result, result, MPFR_RNDD); // sqrt(2pi)
    mpfr_ui_div(result, 1, result, MPFR_RNDD); // 1 / previous line
    mpfr_mul_ui(result, result, 2, MPFR_RNDD); // 2 times the previous line
    mpfr_sub(b, b, a, MPFR_RNDD); // b - a
    mpfr_mul(result, result, b, MPFR_RNDD); // previous line times line 30

    mpfr_clears(a, b, (mpfr_ptr) NULL);
}

int main() {
    int base = 10;
    mpfr_t result, pi_number, euler_num, x, y, z;
    mpfr_inits2(512, result, pi_number, euler_num, x, y, z, (mpfr_ptr) NULL);
    mpfr_set_str(x, "0.010", base, MPFR_RNDD);
    mpfr_set_str(pi_number, "3.14159265358979323846264338327950288419716939937510", base, MPFR_RNDD);
    mpfr_set_str(euler_num, "2.71828182845904523536028747135266249775724709369995", base, MPFR_RNDD);
    integral_of_probability_of_x(result, pi_number, euler_num, x);
    mpfr_printf("%.4RNF\n", result);
    mpfr_clears(result, pi_number, euler_num, x, y, z, (mpfr_ptr) NULL);
}
