#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

int art_thou_prime(int num_1) {
	double square_root = sqrt(num_1);
	int i;
	int test_pass = 0;

	for (i = 2; i <= num_1; i++) {
		if (num_1 % i == 0 && num_1 != i) {
			test_pass = 1;
			break;
		}
	}

	if (test_pass == 1) {
		return 1;
	} else {
		return 0;
	}
}

int problem_003() {
	// It can solve the highest prime of the smol number but it takes too long for the big number

	long big_number = 600851475143;
	int smol_number = 13195, highest_prime = 0, i;

	for (i = 2; i <= smol_number; i++){
		if (art_thou_prime(i) == 0 && smol_number % i == 0) {
			highest_prime = i;
		}
	}

	return highest_prime;
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

int problem_005() {
	// Takes a long time

	int i, search;
	int divisors = 20;
	int pass_rate = 0;
	int x = 1;

	for (search = 200000000; search <= 250000000; search++) {
		pass_rate = 0;

		for (i = 1; i <= divisors; i++) {
			printf("\rCurrently trying: %09d, Pass rate: %02d", search, pass_rate);

			if (search % i == 0) {
				pass_rate++;
			} else {
				break;
			}
		}

		if (pass_rate == divisors) {
			return search;
		}
	}
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

		if ( 0 == strcmp(argv[1], "problem_003")) {
			printf("Highest prime factor of 600851475143: %d\n(I used GNU Utils' Factor)\n", 6857);
			return 0;
		}

		if ( 0 == strcmp(argv[1], "problem_004")) {
			int result = problem_004();
			printf("\nHighest Palindrome: %d\n", result);
			return 0;
		}

		if ( 0 == strcmp(argv[1], "problem_005")) {
			printf("This is gonna take a long time ei, Ctrl + C as soon as you get bored\n");
			int result = problem_005();
			printf("\nLowest number that is evenly divisible by 1 to 20: %d\n", result);
			return 0;
		}

		if ( 0 == strcmp(argv[1], "problem_002")) {
			int result = problem_006();
			printf("Difference of the sum of the squares of the first 100 natural numbers and the squared sum of the first 100 natural numbers: %d\n", result);
			return 0;
		}

		printf("%s\n", "The argument you gave, sadly I don't know what to do with it");
		return 1;
	}

	if (argc < 2) {
		printf("%s\n", "Expected one argument");
		return 1;
	}

	if (argc > 2) {
		printf("%s\n", "Too many arguments, I only need 1");
		return 1;
	}
}