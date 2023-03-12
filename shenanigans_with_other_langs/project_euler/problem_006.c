#include <stdio.h>


int main() {
    int number_of_natural_numbers = 100;
    int squared_sum = 0;
    int sum_of_squared = 0;
    int result = 0;

    for (int i = 1; i <= number_of_natural_numbers; i++) {
        squared_sum += i;
        sum_of_squared += i * i;
    }

    squared_sum = squared_sum * squared_sum;
    result = squared_sum - sum_of_squared;
    printf("The difference between the sum of every squared natural number below 100, and the sum of every natural number below 100 is %d\n", result);
    return 0;
}
