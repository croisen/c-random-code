#include "init_constants.h"

#include <mpfr.h>
#include <stdlib.h>

char *euler = "2.71828182845904523536028747135266249775724709369995957496696"
              "762772407663035354759";
mpfr_ptr pie, eul;

void create_constants(void) {
    pie = malloc(sizeof(__mpfr_struct));
    eul = malloc(sizeof(__mpfr_struct));

    mpfr_inits2(1024, pie, eul, NULL);
    mpfr_const_pi(pie, MPFR_RNDN);
    mpfr_set_str(eul, euler, 10, MPFR_RNDN);
}

void delete_constants(void) {
    mpfr_clear(pie);
    mpfr_clear(eul);

    free(pie);
    free(eul);
}
