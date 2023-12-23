#include "other_stuff/init_constants.h"
#include "other_stuff/the_z.h"

#include <mpfr.h>
#include <stdio.h>


int main(void) {
    create_constants();

    mpfr_printf("pi: %.80RNF\ne:  %.80RNF\n", pie, eul);
    (void)printf("Hello, World!\n");

    delete_constants();
    return 0;
}

