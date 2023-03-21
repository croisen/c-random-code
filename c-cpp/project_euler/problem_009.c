#include <stdio.h>


int main() {
    int a_sqared = 0, b_squared = 0, c_squared = 0;

    for (int c = 2; c <=999; c++) {
        for (int b = 2; b <= 999; b++) {
            for (int a = 2; a <= 999; a++) {
                if (a + b + c == 1000){
                    printf("Currently trying: a = %3d, b = %3d, c = %3d\n", a, b, c);

                    a_sqared = a * a;
                    b_squared = b * b;
                    c_squared = c * c;
                }

                if (a + b + c == 1000 && a_sqared + b_squared == c_squared) {
                    printf("The Pythagorean triplet where a + b + c is equal to 1000, the product of a, b, and c is: %d\n", a*b*c);
                    return 0;
                }
            }
        }
    }
}
