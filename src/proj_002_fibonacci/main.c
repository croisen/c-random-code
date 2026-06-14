#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <wchar.h>

#include "001_dyn_sized_array.h"

#define U128_MIN       0
#define U128_MAX       (uint128)(~U128_MIN)
#define U128_MAX_DIV10 (U128_MAX / 10)
#define U128_MAX_MOD10 (U128_MAX % 10)

#define I128_MAX       ((U128_MAX >> 1))
#define I128_MAX_DIV10 (I128_MAX / 10)
#define I128_MAX_MOD10 (I128_MAX % 10)
#define I128_MIN       (~I128_MAX)
#define I128_MIN_DIV10 (int128) I128_MIN / 10
#define I128_MIN_MOD10 (int128) I128_MIN % 10

typedef __int128 int128;
typedef unsigned __int128 uint128;
typedef unsigned int uint;
typedef unsigned long ulong;

size_t fib(ssize_t n);
uint128 fib2(ssize_t n);
uint128 asctou128(const char *s);
int128 asctoi128(const char *s);
char *u128toasc(char *s, int len, uint128 x);
char *i128toasc(char *s, int len, int128 x);

struct arr {
    int size;
    int used;
    __uint128_t *data;
} arr;

int main(void)
{
    char buffer[49] = {0};
    Dyn_S_Arr_Init(&arr);
    Dyn_S_Arr_Push_Back(&arr, 0);
    Dyn_S_Arr_Push_Back(&arr, 1);
    for (ssize_t i = 0; i <= 128; i++) {
        uint128 f = fib2(i);
        char *r   = u128toasc(buffer, 49, f);
        printf("fib(%3lu) = %48s\n", i, r);
        memset(buffer, 0, sizeof(buffer));
    }

    Dyn_S_Arr_Free(&arr);
    return 0;
}

size_t fib(ssize_t n)
{
    if (n < 0)
        return 0;

    if (n < 2)
        return n;

    return fib(n - 1) + fib(n - 2);
}

__uint128_t fib2(ssize_t n)
{
    if (n < 0)
        return 0;

    if (n < 2)
        return n;

    __uint128_t ret = 0, a = 0, b = 0;
    Dyn_S_Arr_Get(&arr, &a, arr.used - 1);
    Dyn_S_Arr_Get(&arr, &b, arr.used - 2);
    ret = a + b;
    Dyn_S_Arr_Push_Back(&arr, ret);

    return ret;
}

uint128 asctou128(const char *s)
{
    const char *p = s;
    uint128 val   = 0;
    bool neg      = 0;

    while (isspace(*p))
        p++;

    while ((*p == '-') || (*p == '+')) {
        if (*p == '-')
            neg = !neg;
        p++;
    }

    if (!isdigit(*p)) {
        errno = ERANGE;
        perror("invalid input, result set to zero");
        return 0;
    }

    while (*p >= '0' && *p <= '9') {
        if (val >= U128_MAX_DIV10 &&
            (val > U128_MAX_DIV10 || (*p - '0' > U128_MAX_MOD10))) {
            errno = ERANGE;
            perror("error, uint128 overflow, returning MAX");
            return U128_MAX;
        }

        if (neg && *p > '0') {
            errno = ERANGE;
            perror("invalid input, result set to zero");
            return 0;
        }

        val = (10 * val) + (*p - '0');
        p++;
    }

    return val;
}

int128 asctoi128(const char *s)
{
    const char *p = s;
    int128 val    = 0;
    bool neg      = 0;

    while (isspace(*p))
        p++;

    while ((*p == '-') || (*p == '+')) {
        if (*p == '-')
            neg = !neg;
        p++;
    }

    if (!isdigit(*p)) {
        errno = ERANGE;
        perror("invalid input, result set to zero");
        return 0;
    }

    while (*p >= '0' && *p <= '9') {
        if (val <= I128_MIN_DIV10 &&
            (val < I128_MIN_DIV10 || (*p - '0' > -(I128_MIN_MOD10)))) {
            errno = ERANGE;
            if (neg) {
                perror("error, int128 underflow, returning MIN");
                return I128_MIN;
            } else {
                perror("error, int128 overflow, returning MAX");
                return I128_MAX;
            }
        }
        val = (10 * val) - (*p - '0');
        p++;
    }

    if (!neg) {
        if (val == I128_MIN) {
            errno = ERANGE;
            perror("error, int128 overflow, returning MAX");
            return I128_MAX;
        } else {
            val = -val;
        }
    }

    return val;
}

char *u128toasc(char *str, int len, uint128 x)
{
    int j    = len;
    str[--j] = '\0';
    while (x > 9) {
        str[--j]  = (x % 10 + '0');
        x        /= 10;
    }
    str[--j] = (x + '0');
    memmove(str, str + j, len - j);

    return str;
}

char *i128toasc(char *str, int len, int128 x)
{
    int j     = len;
    str[--j]  = '\0';
    int128 an = x < 0 ? x : -x;

    do {
        str[--j]  = '0' - (an % 10);
        an       /= 10;
    } while (an);

    if (x < 0) {
        str[--j] = '-';
    }

    memmove(str, str + j, len - j);

    return str;
}
