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
			return 1;
		}
	}

	return 0;
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

	for (x = 100; x <= 999; x++) {
		for (y = 100; y <= 999; y++) {
			x_times_y = x * y;
			reversed_product = reverse_an_integer(x_times_y);

			if (x_times_y == reversed_product) {
				if (x_times_y > highest_palindrome) {
					printf("\rCurrent palindrome: %d", x_times_y);
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

int problem_008() {
	int a, b, c;
	int a_sqared, b_squared, c_squared;

	for (c = 2; c <=999; c++) {
		for (b = 2; b <= 999; b++) {
			for (a = 2; a <= 999; a++) {
				if (a + b + c == 1000){
					printf("\rCurrently trying: a = %3d, b = %3d, c = %3d", a, b, c);

					a_sqared = a * a;
					b_squared = b * b;
					c_squared = c * c;
				}

				if (a + b + c == 1000 && a_sqared + b_squared == c_squared) {
					return a * b * c;
				}
			}
		}
	}
}

long problem_009() {
	int i, x;
	long product = 0; 
	long result = 0;
	int thousand_long_digit[] = {7, 3, 1, 6, 7, 1, 7, 6, 5, 3, 1, 3, 3, 0, 6, 2, 4, 9, 1, 9, 2, 2, 5, 1, 1, 9, 6, 7, 4, 4, 2, 6, 5, 7, 4, 7, 4, 2, 3, 5, 5, 3, 4, 9, 1, 9, 4, 9, 3, 4, 9, 6, 9, 8, 3, 5, 2, 0, 3, 1, 2, 7, 7, 4, 5, 0, 6, 3, 2, 6, 2, 3, 9, 5, 7, 8, 3, 1, 8, 0, 1, 6, 9, 8, 4, 8, 0, 1, 8, 6, 9, 4, 7, 8, 8, 5, 1, 8, 4, 3, 8, 5, 8, 6, 1, 5, 6, 0, 7, 8, 9, 1, 1, 2, 9, 4, 9, 4, 9, 5, 4, 5, 9, 5, 0, 1, 7, 3, 7, 9, 5, 8, 3, 3, 1, 9, 5, 2, 8, 5, 3, 2, 0, 8, 8, 0, 5, 5, 1, 1, 1, 2, 5, 4, 0, 6, 9, 8, 7, 4, 7, 1, 5, 8, 5, 2, 3, 8, 6, 3, 0, 5, 0, 7, 1, 5, 6, 9, 3, 2, 9, 0, 9, 6, 3, 2, 9, 5, 2, 2, 7, 4, 4, 3, 0, 4, 3, 5, 5, 7, 6, 6, 8, 9, 6, 6, 4, 8, 9, 5, 0, 4, 4, 5, 2, 4, 4, 5, 2, 3, 1, 6, 1, 7, 3, 1, 8, 5, 6, 4, 0, 3, 0, 9, 8, 7, 1, 1, 1, 2, 1, 7, 2, 2, 3, 8, 3, 1, 1, 3, 6, 2, 2, 2, 9, 8, 9, 3, 4, 2, 3, 3, 8, 0, 3, 0, 8, 1, 3, 5, 3, 3, 6, 2, 7, 6, 6, 1, 4, 2, 8, 2, 8, 0, 6, 4, 4, 4, 4, 8, 6, 6, 4, 5, 2, 3, 8, 7, 4, 9, 3, 0, 3, 5, 8, 9, 0, 7, 2, 9, 6, 2, 9, 0, 4, 9, 1, 5, 6, 0, 4, 4, 0, 7, 7, 2, 3, 9, 0, 7, 1, 3, 8, 1, 0, 5, 1, 5, 8, 5, 9, 3, 0, 7, 9, 6, 0, 8, 6, 6, 7, 0, 1, 7, 2, 4, 2, 7, 1, 2, 1, 8, 8, 3, 9, 9, 8, 7, 9, 7, 9, 0, 8, 7, 9, 2, 2, 7, 4, 9, 2, 1, 9, 0, 1, 6, 9, 9, 7, 2, 0, 8, 8, 8, 0, 9, 3, 7, 7, 6, 6, 5, 7, 2, 7, 3, 3, 3, 0, 0, 1, 0, 5, 3, 3, 6, 7, 8, 8, 1, 2, 2, 0, 2, 3, 5, 4, 2, 1, 8, 0, 9, 7, 5, 1, 2, 5, 4, 5, 4, 0, 5, 9, 4, 7, 5, 2, 2, 4, 3, 5, 2, 5, 8, 4, 9, 0, 7, 7, 1, 1, 6, 7, 0, 5, 5, 6, 0, 1, 3, 6, 0, 4, 8, 3, 9, 5, 8, 6, 4, 4, 6, 7, 0, 6, 3, 2, 4, 4, 1, 5, 7, 2, 2, 1, 5, 5, 3, 9, 7, 5, 3, 6, 9, 7, 8, 1, 7, 9, 7, 7, 8, 4, 6, 1, 7, 4, 0, 6, 4, 9, 5, 5, 1, 4, 9, 2, 9, 0, 8, 6, 2, 5, 6, 9, 3, 2, 1, 9, 7, 8, 4, 6, 8, 6, 2, 2, 4, 8, 2, 8, 3, 9, 7, 2, 2, 4, 1, 3, 7, 5, 6, 5, 7, 0, 5, 6, 0, 5, 7, 4, 9, 0, 2, 6, 1, 4, 0, 7, 9, 7, 2, 9, 6, 8, 6, 5, 2, 4, 1, 4, 5, 3, 5, 1, 0, 0, 4, 7, 4, 8, 2, 1, 6, 6, 3, 7, 0, 4, 8, 4, 4, 0, 3, 1, 9, 9, 8, 9, 0, 0, 0, 8, 8, 9, 5, 2, 4, 3, 4, 5, 0, 6, 5, 8, 5, 4, 1, 2, 2, 7, 5, 8, 8, 6, 6, 6, 8, 8, 1, 1, 6, 4, 2, 7, 1, 7, 1, 4, 7, 9, 9, 2, 4, 4, 4, 2, 9, 2, 8, 2, 3, 0, 8, 6, 3, 4, 6, 5, 6, 7, 4, 8, 1, 3, 9, 1, 9, 1, 2, 3, 1, 6, 2, 8, 2, 4, 5, 8, 6, 1, 7, 8, 6, 6, 4, 5, 8, 3, 5, 9, 1, 2, 4, 5, 6, 6, 5, 2, 9, 4, 7, 6, 5, 4, 5, 6, 8, 2, 8, 4, 8, 9, 1, 2, 8, 8, 3, 1, 4, 2, 6, 0, 7, 6, 9, 0, 0, 4, 2, 2, 4, 2, 1, 9, 0, 2, 2, 6, 7, 1, 0, 5, 5, 6, 2, 6, 3, 2, 1, 1, 1, 1, 1, 0, 9, 3, 7, 0, 5, 4, 4, 2, 1, 7, 5, 0, 6, 9, 4, 1, 6, 5, 8, 9, 6, 0, 4, 0, 8, 0, 7, 1, 9, 8, 4, 0, 3, 8, 5, 0, 9, 6, 2, 4, 5, 5, 4, 4, 4, 3, 6, 2, 9, 8, 1, 2, 3, 0, 9, 8, 7, 8, 7, 9, 9, 2, 7, 2, 4, 4, 2, 8, 4, 9, 0, 9, 1, 8, 8, 8, 4, 5, 8, 0, 1, 5, 6, 1, 6, 6, 0, 9, 7, 9, 1, 9, 1, 3, 3, 8, 7, 5, 4, 9, 9, 2, 0, 0, 5, 2, 4, 0, 6, 3, 6, 8, 9, 9, 1, 2, 5, 6, 0, 7, 1, 7, 6, 0, 6, 0, 5, 8, 8, 6, 1, 1, 6, 4, 6, 7, 1, 0, 9, 4, 0, 5, 0, 7, 7, 5, 4, 1, 0, 0, 2, 2, 5, 6, 9, 8, 3, 1, 5, 5, 2, 0, 0, 0, 5, 5, 9, 3, 5, 7, 2, 9, 7, 2, 5, 7, 1, 6, 3, 6, 2, 6, 9, 5, 6, 1, 8, 8, 2, 6, 7, 0, 4, 2, 8, 2, 5, 2, 4, 8, 3, 6, 0, 0, 8, 2, 3, 2, 5, 7, 5, 3, 0, 4, 2, 0, 7, 5, 2, 9, 6, 3, 4, 5, 0};

	for (i = 0; i + 12 < 1000; i++ ){
		product = thousand_long_digit[i];
		
		for (x = 1; x <= 12; x++) {
			// printf("%d ", thousand_long_digit[i + x]);
			product *= thousand_long_digit[i + x];
		}

		// printf("= %ld\n", product);

		if (product > result) {
			printf("\rCurrent highest product: %ld",  product);
			result = product;
		}
	}

	return result;
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
			printf("\nHighest Palindrome made by multiplying 3 digit numbers: %d\n", result);
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

		if ( 0 == strcmp(argv[1], "problem_008")) {
			int result = problem_008();
			printf("\nThe product of pythagorean triplet where a + b + c is equal 1000: %d\n", result);
			return 0;
		}

		if ( 0 == strcmp(argv[1], "problem_009")) {
			long result = problem_009();
			printf("\nThe largest product of 13 adjacent digits in a thousand digit number: %ld\n", result);
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