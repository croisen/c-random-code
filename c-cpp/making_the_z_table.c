#include <mpfr.h>
#include <stdio.h>

#define rnd MPFR_RNDD

void natural_pdf_of_x(mpfr_t rop, mpfr_t x) {
    mpfr_t a, b, c, d, e, pi_number, euler_num;
    mpfr_inits(a, b, c, d, e, (mpfr_ptr)NULL);
    mpfr_init_set_str(pi_number, "3.141592653589793238462643383279502884197169399375105820974944592307816", 10, rnd);
    mpfr_init_set_str(euler_num, "2.718281828459045235360287471352662497757247093699959574966967627724076", 10, rnd);
    mpfr_set_str(a, "-10.000", 10, rnd);
    mpfr_set_str(b, "0.000", 10, rnd);
    mpfr_set_str(c, "0.000", 10, rnd);
    mpfr_set_str(d, "0.0001", 10, rnd);
    mpfr_set_ui(rop, 0, rnd);

    for (a; mpfr_cmp(a, x) < 0; mpfr_add(a, a, d, rnd)) {
        mpfr_mul_ui(b, pi_number, 2, rnd);
        mpfr_sqrt(b, b, rnd);
        mpfr_pow_ui(c, a, 2, rnd);
        mpfr_div_ui(c, c, 2, rnd);
        mpfr_neg(c, c, rnd);
        mpfr_pow(c, euler_num, c, rnd);
        mpfr_div(e, c, b, rnd);
        mpfr_mul(e, e, d, rnd);
        mpfr_add(rop, rop, e, rnd);
    }
    mpfr_clears(a, b, c, d, e, pi_number, euler_num, (mpfr_ptr)NULL);
}

int main() {
    mpfr_set_default_prec(512);
    mpfr_t rop, x, a, b, c, d, e;
    mpfr_inits(rop, x, a, b, c, d, e, (mpfr_ptr)NULL);
    mpfr_set_str(x, "-4.000", 10, rnd);
    mpfr_set_str(c, "0.1", 10, rnd);
    mpfr_set_str(d, "0.01", 10, rnd);
    mpfr_set_str(e, "0.09", 10, rnd);

    for (x; mpfr_cmp_ui(x, 4) < 0; mpfr_add(x, x, c, rnd)) {
        mpfr_printf("%.1RNf|", x);
        mpfr_set_str(a, "0.000", 10, rnd);
        if (mpfr_sgn(x) == 0) {
            for (a; mpfr_cmp(a, e) < 0; mpfr_add(a, a, d, rnd)) {
                mpfr_sub(b, x, a, rnd);
                natural_pdf_of_x(rop, b);
                mpfr_printf("%.5RNf|", rop);
            }
            mpfr_printf("\n%.1RNf|", x);
            for (a; mpfr_cmp(a, e) < 0; mpfr_add(a, a, d, rnd)) {
                mpfr_add(b, x, a, rnd);
                natural_pdf_of_x(rop, b);
                mpfr_printf("%.5RNf|", rop);
            }
        }

        for (a; mpfr_cmp(a, e) < 0; mpfr_add(a, a, d, rnd)) {
            if (mpfr_sgn(x) < 0) {
                mpfr_sub(b, x, a, rnd);
                natural_pdf_of_x(rop, b);
                mpfr_printf("%.5RNf|", rop);
            } else if (mpfr_sgn(x) > 0) {
                mpfr_add(b, x, a, rnd);
                natural_pdf_of_x(rop, b);
                mpfr_printf("%.5RNf|", rop);
            }
        }
        printf("\n");
    }

    mpfr_clears(rop, x, a, b, c, d, e, (mpfr_ptr)NULL);
    return 0;
}
