#include <mpfr.h>
#include <stdio.h>

#define rndd MPFR_RNDD

void mpfr_init_pi(mpfr_t pi_number) {
    mpfr_const_pi(pi_number, rndd);
}

void cdf(mpfr_t dem) {
    printf("I currently have no idea what to do\n");
}

int main() {
    mpfr_t probability, x, pi_number, a, b, c;
    mpfr_inits2((mpfr_prec_t)1024, probability, x, pi_number, a, b, c, (mpfr_t*)NULL);
    mpfr_init_pi(pi_number);

    mpfr_clears(probability, x, pi_number, a, b, c, (mpfr_t*)NULL);
    return 0;
}
