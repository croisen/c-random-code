#include <stdio.h>
int is_divisible_by_one_through_n(int number, int divisors) {
    for (int i = 1; i <= divisors; i++) {
        if (number % i != 0) {
            return 1;
        }
    }

    return 0;
}

int main() {
    int continue_loop = 0;
    int divisors = 20;
    int x = divisors;
    printf("Currently testing for a number that is evenly divisible by 1 through 20\n");

    while (continue_loop == 0) {
        if (is_divisible_by_one_through_n(x, divisors) == 0) {
            printf("Lowest number that is evenly divisible by 1 through 20 is %d\n", x);
            continue_loop = 1;
        }
        x = x + divisors;
    }

    return 0;
}
