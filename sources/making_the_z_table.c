#include <mpfr.h>
#include <stdio.h>

#define rndd MPFR_RNDD


mpfr_t pi_number, euler_num, a, b, c;

void pdf(mpfr_ptr rop, mpfr_srcptr x);
void cdf(mpfr_ptr rop, mpfr_srcptr x);

int main() {
    mpfr_t probability, x;
    mpfr_inits2((mpfr_prec_t)1024, probability, x, pi_number, euler_num, a, b, c, (mpfr_t*)NULL);

    mpfr_const_pi(pi_number, rndd);
    mpfr_mul_ui(pi_number, pi_number, 2, rndd);
    mpfr_sqrt(pi_number, pi_number, rndd);  // sqrt(2pi);

    mpfr_set_str(euler_num,
                 "2.7182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274", // e
                 10, rndd);
    mpfr_set_ui(probability, 0, rndd);

    mpfr_set_str(x, "0.000", 10, rndd);
    cdf(probability, x);
    mpfr_printf("%6.RNF %RNF %RNF\n", probability, pi_number, euler_num);

    mpfr_clears(probability, x, pi_number, euler_num, a, b, c, (mpfr_t*)NULL);
    return 0;
}

void pdf(mpfr_ptr rop, mpfr_srcptr x) {
    mpfr_sqr(b, x, rndd); // (-x)^2
    mpfr_neg(b, b, rndd); // -(x^2)
    mpfr_div_ui(b, b, 2, rndd);


    mpfr_pow(b, euler_num, b, rndd); //e^(x^2 / 2)
    mpfr_div(rop, b, pi_number, rndd); // previous / sqrt(2pi)

}

void cdf(mpfr_ptr rop, mpfr_srcptr x) {
    mpfr_set_str(a, "-10.000", 10, rndd);

    for (; mpfr_cmp(x, a) < 1;) {
        pdf(c, x);
        mpfr_add(rop, rop, c, rndd);
        mpfr_add_d(a, a, 0.001F, rndd);
    }
}
