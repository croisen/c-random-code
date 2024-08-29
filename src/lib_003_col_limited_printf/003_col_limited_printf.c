#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "003_col_limited_printf.h"

void col_limited_printf(int cols, int offset, const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    int length = vsnprintf(NULL, 0, format, ap);

    va_end(ap);

    va_start(ap, format);

    /* We aren't even checking if this returns NULL */
    char *start = calloc(length + 1, sizeof(char));
    char *msg   = start;
    vsprintf(start, format, ap);

    va_end(ap);

    int cols_left = cols - offset;
    while (start + length > msg) {
        int wordlen = strcspn(msg, " \n\t");
        if (wordlen >= cols_left) {
            cols_left = cols - offset;
            printf("\n");

            if (offset > 0)
                printf("%*s", offset, "");
        }

        if (wordlen > cols - offset)
            wordlen = cols - offset;

        printf("%.*s", wordlen, msg);
        char next = msg[wordlen];
        if (next == ' ') {
            if (1 > cols_left) {
                printf("\n");

                if (offset > 0)
                    printf("%*s", offset, "");
            }

            printf(" ");
            cols_left -= 1;
        } else if (next == '\t') {
            if (1 > cols_left) {
                printf("\n");

                if (offset > 0)
                    printf("%*s", offset, "");
            }

            printf("        ");
            cols_left -= 1;
        } else if (next == '\n') {
            cols_left = cols - offset;
            printf("\n");
        }

        cols_left -= wordlen;
        msg       += wordlen + 1;
    }

    free(start);
}
