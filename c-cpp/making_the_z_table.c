#include <mpfr.h>
#include <stdio.h>

#define eul "2.718281828459045235360287471352662497757247093699959574966967627724076"
#define pie "3.141592653589793238462643383279502884197169399375105820974944592307816"
#define rnd MPFR_RNDD

void natural_pdf_of_x(mpfr_t rop, mpfr_t x, mpfr_t euler_num, mpfr_t a, mpfr_t b, mpfr_t c, mpfr_t d, mpfr_t e) {
    mpfr_set_str(a, "-10.000", 10, rnd);
    mpfr_set_ui(rop, 0, rnd);

    for (a; mpfr_cmp(a, x) < 0; mpfr_add(a, a, e, rnd)) {
        mpfr_pow_ui(c, a, 2, rnd);
        mpfr_div_ui(c, c, 2, rnd);
        mpfr_neg(c, c, rnd);
        mpfr_pow(c, euler_num, c, rnd);
        mpfr_div(d, c, b, rnd);
        mpfr_mul(d, d, e, rnd);
        mpfr_add(rop, rop, d, rnd);
    }
}

int main() {
    mpfr_set_default_prec(512);
    mpfr_t rop, x, a, b, c, d, e, f, g, h, i, j, pi_number, euler_num;
    mpfr_inits(rop, x, a, b, c, d, e, f, g, h, i, j, (mpfr_ptr)NULL);
    mpfr_set_str(x, "-4.000", 10, rnd);
    mpfr_set_str(c, "0.1", 10, rnd);
    mpfr_set_str(d, "0.01", 10, rnd);
    mpfr_set_str(e, "0.09", 10, rnd);
    mpfr_set_str(f, "0.0", 10, rnd);
    mpfr_init_set_str(pi_number, pie, 10, rnd);
    mpfr_init_set_str(euler_num, eul, 10, rnd);
    mpfr_mul_ui(g, pi_number, 2, rnd);
    mpfr_sqrt(g, g, rnd);
    mpfr_set_str(j, "0.0001", 10, rnd);

    for (x; mpfr_cmp_ui(x, 0) < 0; mpfr_add(x, x, c, rnd)) {
        mpfr_set_str(a, "0.000", 10, rnd);
        mpfr_printf("%.1RNf |", x);
        for (a; mpfr_cmp(a, e) < 0; mpfr_add(a, a, d, rnd)) {
                mpfr_sub(b, x, a, rnd);
                natural_pdf_of_x(rop, b, euler_num, f, g, h, i, j);
                mpfr_printf(" %.5RNf |", rop);
        }
        printf("\n");
    }
    mpfr_set_str(x, "0.0", 10, rnd);
    for (x; mpfr_cmp_ui(x, 4) < 0; mpfr_add(x, x, c, rnd)) {
        mpfr_set_str(a, "0.000", 10, rnd);
        mpfr_printf(" %.1RNf |", x);
        for (a; mpfr_cmp(a, e) < 0; mpfr_add(a, a, d, rnd)) {
                mpfr_add(b, x, a, rnd);
                natural_pdf_of_x(rop, b, euler_num, f, g, h, i, j);
                mpfr_printf(" %.5RNf |", rop);
            }
        printf("\n");
    }
    mpfr_clears(rop, x, a, b, c, d, e, f, g, h, i, j, pi_number, euler_num, (mpfr_ptr)NULL);
    return 0;
}
