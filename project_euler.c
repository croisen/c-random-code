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
	int square_root = sqrt(num_1);
	int i;
	int test_pass = 0;

	for (i = 2; i <= square_root; i++) {
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
	long big_number = 600851475143;
	int smol_number = 13195, highest_prime = 0, i;
	int square_root = sqrt(big_number);

	for (i = 2; i <= square_root; i++){
		if (art_thou_prime(i) == 0 && big_number % i == 0) {
			printf("Current Highest Prime: %d\n", i);
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

int is_divisible_by_one_through_n(int number, int divisors) {
	int i;

	for (i = 1; i <= divisors; i++) {
		if (number % i != 0) {
			return 1;
		}
	}

	return 0;
}

int problem_005() {
	// Takes a long time, like 43 mins on my laptop
	// Made a function to check if the number is evenly divisible by 
	// 1 through n to check if it's faster, and it took around 12 mins
	// Converted it to a while loop, it took around 11 mins

	int continue_loop = 0;
	int divisors = 20;
	int x = divisors + 1;

	while (continue_loop == 0) {
		printf("\rCurrently testing: %9d", x);
		if (is_divisible_by_one_through_n(x, divisors) == 0) {
			continue_loop = 1;
			return x;
		}

		x++;
	}
}

int problem_006() {
	int i;
	int number_of_natural_numbers = 100;
	int squared_sum = 0;
	int sum_of_squared = 0;
	int result;

	for (i = 1; i <= number_of_natural_numbers; i++) {
		squared_sum += i;
		sum_of_squared += i * i;
	}

	squared_sum = squared_sum * squared_sum;
	result = squared_sum - sum_of_squared;

	return result;
}

int problem_007() {
	int target_prime_count = 10001;
	int prime_count = 1;
	int x = 2;

	while (prime_count < target_prime_count + 1) {
		if (art_thou_prime(x) == 0) {
			printf("\rCurrent prime: %7d", x);
			prime_count++;
			x++;
		} else {
			x++;
		}
	}

	return x - 1;
}

long problem_010() {
	int i;
	long result = 0;

	for (i = 2; i < 2000000; i++) {
		if (art_thou_prime(i) == 0 && i < 2000000) {
			printf("\rCurrent prime: %7d", i);
			result += i;
		}
	}

	return result;
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

		// if ( 0 == strcmp(argv[1], "problem_003")) {
		// 	printf("Highest prime factor of 600851475143: %d\n(I used GNU Utils' Factor)\n", 6857);
		// 	return 0;
		// }

		if ( 0 == strcmp(argv[1], "problem_003")) {
			int result = problem_003();
			printf("Highest prime factor of 600851475143: %d\n", result);
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

		if ( 0 == strcmp(argv[1], "problem_006")) {
			int result = problem_006();
			printf("Difference of the sum of the squares of the first 100 natural numbers and the squared sum of the first 100 natural numbers: %d\n", result);
			return 0;
		}

		if ( 0 == strcmp(argv[1], "problem_007")) {
			int result = problem_007();
			printf("\nThe problem I gave up on solving with bash, the 10001st prime number. Well it's: %d\n", result);
			return 0;
		}

		if ( 0 == strcmp(argv[1], "problem_010")) {
			long result = problem_010();
			printf("\nThe sum of all prime numbers below 2 million is: %ld\n", result);
			return 0;
		}

		printf("%s\n", "The argument you gave, sadly I don't know what to do with it");
		printf("%s%s%s\n", "Usage: ", argv[0], " <<problem_XXX>>");
		return 1;
	}

	if (argc < 2) {
		printf("%s\n", "Expected one argument");
		printf("%s%s%s\n", "Usage: ", argv[0], " <<problem_XXX>>");
		return 1;
	}

	if (argc > 2) {
		printf("%s\n", "Too many arguments, I only need 1");
		printf("%s%s%s\n", "Usage: ", argv[0], " <<problem_XXX>>");
		return 1;
	}
}