#include <stdio.h>
#include <math.h>


int main() {
    int divisors = 0;
    int i = 1;

    while (divisors < 500) {
        int triangular_number = (i * (i + 1))/2;
        int divisors = 0;
        int t_num_root = sqrt(triangular_number);
        
        for (int divisor = 1; divisor <= t_num_root; divisor++) {
            if (triangular_number % divisor == 0) {
                divisors = divisors + 2;
            }
        }

        if (divisors >= 500) {
            printf("The lowest triangular number to have an amount of divisors over 500 is %d\n", triangular_number);
            return 0;
        }

        printf("Triangular number: %7d, No. of divisors: %d\n", triangular_number, divisors);
        i++;
    }
}
