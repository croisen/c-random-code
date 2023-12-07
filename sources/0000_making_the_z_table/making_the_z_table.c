#include <mpfr.h>
#include <stdio.h>

mpfr_t pie, eul;

void init_constants(void);
void clr__constants(void);

int main(void) {
    init_constants();

    mpfr_printf("pi: %.80RNF\ne: %.80RNF\n", pie, eul);
    (void)printf("Hello, World!\n");

    clr__constants();
    return 0;
}

void init_constants(void) {
    mpfr_t a;
    (void)mpfr_inits2(1024, pie, eul, a, (mpfr_ptr)NULL);
    (void)mpfr_const_pi(pie, MPFR_RNDN);
    (void)mpfr_set_ui(eul, 0, MPFR_RNDN);

    // Since e is not a constant in mpfr.h well I'mma use this instead of a string
    // e ≈ 1 + 1/1! + 1/2! + 1/3! + ... + 1/1000!
    for (unsigned long i = 0; i < 1000; i++) {
        (void)mpfr_fac_ui(a, i, MPFR_RNDN);
        (void)mpfr_ui_div(a, 1, a, MPFR_RNDN);
        (void)mpfr_add(eul, eul, a, MPFR_RNDN);
    }
    mpfr_clear(a);
}

void clr__constants(void) {
    // Better pay respects and clear the memory
    mpfr_clears(pie, eul, (mpfr_ptr)NULL);
}
