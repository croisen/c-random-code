#include <stdio.h>


int main() {
    int a = 1, b = 2, c = 0, result = 0;

    while (a < 4000000) {
        if (a % 2 == 0 && a < 4000000) {
            result = result + a;
        }

        c = a + b;
        a = b;
        b = c;
    }

    printf("The sum of all even fibonacci numbers under 4 million is: %d\n", result);
    return 0;
}
