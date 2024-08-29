#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "003_col_limited_printf.h"

void col_limited_printf(int cols, int offset, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    int length  = vsnprintf(NULL, 0, format, ap);
    char *start = calloc(length + 1, sizeof(char));
    char *msg   = start;
    vsprintf(start, format, ap);

    int cols_left = cols - offset;
    while (start + length > msg) {
        /*
         * Kinda sus that we are just reading into memory like this buut it
         * works tho valgrind is complaining
         */
        int wordlen = strcspn(msg, " ");
        if (wordlen >= cols_left) {
            cols_left = cols - offset;
            printf("\n");

            if (offset > 0)
                printf("%*s", offset, "");
        }

        printf("%.*s", wordlen + 1, msg);
        cols_left -= wordlen + 1;
        msg       += wordlen + 1;
    }

    free(start);
    va_end(ap);
}
