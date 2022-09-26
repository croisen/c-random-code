#include <stdio.h>


int main() {
    int result = 0;

    for (int i = 3; i <= 999; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            result =  result + i;            
        }
    }

    printf("The sum of all numbers that are evenly divisible by 3 or 5 that is under 1000 is: %d\n", result);
    return 0;
}
