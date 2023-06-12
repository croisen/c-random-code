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
    int target_prime_count = 10001;
    int prime_count = 0;
    int x = 2;

    while (prime_count <= target_prime_count) {
        if (art_thou_prime(x) == 0) {
            printf("Current prime: %7d\n", x);
            prime_count++;
        }

        if (prime_count == target_prime_count) {
            printf("The 10001st prime number is: %d\n", x);
            return 0;
        }

        x++;
    }
}
