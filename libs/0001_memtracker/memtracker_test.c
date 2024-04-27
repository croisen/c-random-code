#include <stdint.h>
#include <stdlib.h>

#include "memtracker.h"

int main(void)
{
    void *x = NULL;
    for (uint64_t i = 0; i < 69420; i += 1)
    {
        x = mTCalloc(10, 200);
        (void)x;
    }

    for (uint64_t i = 0; i < 69420; i += 1)
    {
        x = mTMalloc(200);
        (void)x;
    }

    return 0;
}
