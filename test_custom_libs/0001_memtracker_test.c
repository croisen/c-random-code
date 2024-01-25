#include <stdio.h>

#define CROI_LIB_0001_MEMTRACKER_IMPL_H
#include "../custom_libs/0001_memtracker.h"

int main(void)
{
    for (size_t i = 0; i < 420; i += 1)
    {
        croi_malloc(i * 200);
        croi_calloc(i + 10, i * 20);
        croi_realloc(NULL, i * 300);
    }
}
