#include "atoi64.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int64_t atoi64(char *num_string) {
    int64_t x = 0;
    (void)sscanf(num_string, "%" SCNd64, &x);
    return x;
}
