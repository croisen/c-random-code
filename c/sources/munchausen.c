#include <math.h>
#include <stdio.h>

#define limit 5000

int main() {
    for (int i = 1; i < limit; i++) {
        int sum = 0;
        for (int number = i; number > 0; number /= 10) {
            int digit = number % 10;
            sum += (int)pow(digit, digit);
        }
        if (sum == i) {
            (void)printf("%d\n", i);
        }
    }
    return 0;
}
