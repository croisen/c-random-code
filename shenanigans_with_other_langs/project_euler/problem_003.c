#include <stdio.h>
#include <math.h>


int art_thou_prime(long num) {
    long square_root = sqrt(num);

    for (long i = 2; i <= square_root; i++) {
        if (num % i == 0) {
            return 1;
        }
    }

    return 0;
}

int main() {
    long big_number = 600851475143;
    long highest_prime = 0;
    long square_root = sqrt(big_number);

    for (long x = 2; x <= square_root; x++) {
        if (art_thou_prime(x) == 0 && big_number % x == 0) {
            printf("Current highest prime: %ld\n", x);
            highest_prime = x;
        }
    }

    printf("The largest prime factor of %ld is %ld\n", big_number, highest_prime);
    return 0;
}
