#include <stdio.h>

int reverse_an_integer(int num_1) {
    int remainder = 0, reverse = 0;

    while (num_1 != 0) {
        remainder = num_1 % 10;
        reverse = reverse * 10 + remainder;
        num_1 /= 10;
    }

    return reverse;
}

int main() {
    int x_times_y = 0;
    int reversed_product;
    int highest_palindrome = 0;

    for (int x = 100; x <= 999; x++) {
        for (int y = 100; y <= 999; y++) {
            x_times_y = x * y;
            reversed_product = reverse_an_integer(x_times_y);

            if (x_times_y == reversed_product) {
                if (x_times_y > highest_palindrome) {
                    printf("Current palindrome: %d\n", x_times_y);
                    highest_palindrome = x_times_y;
                }
            }
        }
    }

    printf("Highest palindrome product by two 3 digit numbers: %d\n", highest_palindrome);
    return 0;
}
