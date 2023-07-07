#include <stdio.h>
#include <math.h>


int art_thou_prime(int num_1) {
    int square_root = sqrt(num_1);

    for (int i = 2; i <= square_root; i++) {
        if (num_1 % i == 0 && num_1 != i) {
            return 1;
        }
    }

    return 0;
}

int main() {
    long result = 0;

    for (int i = 2; i < 2000000; i++) {
        if (art_thou_prime(i) == 0 && i < 2000000) {
            printf("\rCurrent prime: %7d", i);
            result += i;
        }
    }

    printf("\nThe sum of all prime numbers below 2 million is %ld\n", result);
    return 0;
}
