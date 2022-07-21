#include <stdio.h>
#include <string.h>
#include <math.h>


int problem_001() {
	int i = 0;
	int result = 0;

	for (i = 3; i < 1000; i++ ) {
		if (i % 3 == 0 || i % 5 == 0) {
			result = result + i;
		}
	}

	return result;
}

int problem_002() {
	int a = 1;
	int b = 2;
	int c = 0;
	int result = 0;

	while (a < 4000000) {
		c = a + b;
		a = b;
		b = c;

		if (a % 2 == 0 && a < 4000000) {
			result = result + a;
		}
	}

	return result;
}

int reverse_an_integer(int num_1) {
	int remainder, reverse = 0;

	while (num_1 != 0) {
		remainder = num_1 % 10;
		reverse = reverse * 10 + remainder;
		num_1 /= 10;
	}

	return reverse;
}

int problem_004() {
	int x;
	int y;
	int x_times_y;
	int reversed_product;
	int highest_palindrome = 0;

	for (x = 850; x <= 999; x++) {
		for (y = 850; y <= 999; y++) {
			x_times_y = x * y;
			reversed_product = reverse_an_integer(x_times_y);

			if (x_times_y == reversed_product) {
				printf("\rCurrent palindrome: %d", x_times_y);

				if (x_times_y > highest_palindrome) {
					printf("\n%d is a new high\n", x_times_y);
					highest_palindrome = x_times_y;
				}
			}
		}
	}

	return highest_palindrome;
}

int main( int argc, char *argv[] ) {
	if (argc == 2) {
		if ( 0 == strcmp(argv[1], "problem_001")) {
			int result = problem_001();
			printf("The sum of the numbers below 1000 that are divisible by 3 or 5: %d\n", result);
			return 0;
		}

		if ( 0 == strcmp(argv[1], "problem_002")) {
			int result = problem_002();
			printf("Sum of the even fibonacci numbers below 4 million: %d\n", result);
			return 0;
		}

		if ( 0 == strcmp(argv[1], "problem_004")) {
			int result = problem_004();
			printf("\nHighest Palindrome: %d\n", result);
			return 0;
		}

		printf("%s\n", "The argument you gave, sadly I don't know what to do with it");
		return 1;
	}

	if (argc < 2) {
		printf("%s\n", "Expected at one argument");
		return 1;
	}

	if (argc > 2) {
		printf("%s\n", "Too many arguments, I only need 1");
		return 1;
	}
}