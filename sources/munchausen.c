/* Welp 0^0 is considered as 0 here though I think*/

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define _base  10L
#define lbound 0L
#define ubound _base * lpow(_base - 1L, _base - 1L)


long lpow(long base, unsigned long exp) {
    long b = 1L;

    if (exp & 1L) { b = base; }
    exp >>= 1L;

    for (;;)
    {
        base = (base * base);
        if (exp & 1L) { b *= base; }
        exp >>= 1L;
        if (!exp) { break; }
    }
    return b;
}


bool is_munchausen(long num)
{
    long x = num;
    long sum = 0;
    while (x > 0)
    {
        long digit = x % 10;
        sum += lpow(digit, (unsigned long)digit);
        x /= 10;
    }
    return (sum == num);
}

int main(void) {
    printf("Base: %ld LBound: %ld UBound: %ld\n", _base, lbound, ubound);
    clock_t begin = clock();
    for (long i = lbound ; i < ubound; i++) {
        if (is_munchausen(i)) {
            clock_t lap = clock();
            (void)printf("Munchausen number: %10ld - Time: %F seconds\n",
                         i, ((double)(lap - begin) / CLOCKS_PER_SEC));
        }
    }

    return 0;
}
