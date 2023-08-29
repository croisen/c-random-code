#include "math_funcs.h"

void not_implemented(int_fast64_t problem_num, bool verbose, bool testing) {
    if (!testing) {
        printf("There is no function to solve for problem #%"PRIdFAST64" yet sadly, also verbose is set to: %d\n",
               problem_num, verbose);
    }
}

bool art_thou_prime(int_fast64_t num) {
    int_fast64_t square_root = (long)sqrt(num);

    if (num == 1)                     { return false; }
    if ((num % 2 == 0) && (num != 2)) { return false; }

    for (int_fast64_t i = 3; i <= square_root; i += 2) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}


bool is_divisible_by_one_through_n(int_fast64_t number, int_fast64_t divisors) {
    for (int_fast64_t i = divisors; 2 <= i; i--) {
        if (number % i != 0) {
            return false;
        }
    }
    return true;
}

int_fast64_t collatz_chain(int_fast64_t num) {
    int_fast64_t chain_count = 1;

    while (num != 1) {
        if (num % 2 == 0) {
            num = num / 2;
            chain_count++;
        } else {
            num = (3 * num) + 1;
            chain_count++;
        }
    }
    return chain_count;
}

int_fast64_t compare_num(int_fast64_t left, int_fast64_t right) {
    if (left > right) {
        return 0;
    } else if (left < right) {
        return 1;
    } else {
        return 2; // I sure do hope this does not happen for problem 18 and 67
    }
}

int_fast64_t reverse_an_integer(int_fast64_t num) {
    int_fast64_t remainder = 0, reverse = 0;

    while (num != 0) {
        remainder = num % 10;
        reverse = reverse * 10 + remainder;
        num /= 10;
    }

    return reverse;
}

int_fast64_t combinatorial(int_fast64_t n, int_fast64_t r) {
    mpz_t n1, C, r1;
    mpz_inits(n1, C, r1, NULL);
    mpz_fac_ui(n1, n);
    mpz_fac_ui(r1, r);
    mpz_set_ui(C, n - r);
    mpz_fac_ui(C, mpz_get_si(C));

    mpz_mul(C, C, r1);
    mpz_div(n1, n1, C);
    int_fast64_t result = mpz_get_si(n1);
    mpz_clears(n1, C, r1, NULL);

    return result;
}

char *num_to_char(int_fast64_t num) {
    int_fast64_t m      = num;
    int_fast64_t digits = 0;

    while (m) {
        digits++;
        m /= 10;
    }

    char *arr = calloc((size_t)(digits + 1), sizeof(char));
    if (arr == NULL) {
        fprintf(stderr, "Failed to get memory to convert %"PRIdFAST64" to a string\n", num);
        exit(1);
    }

    int_fast64_t index = digits - 1;
    while (num) {
        arr[index--] = (num % 10) + '0';
        num /= 10;
    }

    return arr;
}

char *sha256_digest(char *number_string) {
    char *raw_hash = malloc((sizeof(char) * EVP_MAX_MD_SIZE));

    EVP_MD_CTX *x = EVP_MD_CTX_new();
    EVP_DigestInit_ex(x, EVP_sha256(), NULL);
    EVP_DigestUpdate(x, number_string, strnlen(number_string, ( sizeof(char) * 256 )));
    EVP_DigestFinal_ex(x, (unsigned char *)raw_hash, NULL);
    EVP_MD_CTX_free(x);

    const char hexlookup[17] = "0123456789abcdef";
    char *hash = malloc((sizeof(char) * (2 * EVP_MAX_MD_SIZE)) + 1);
    if (hash == NULL) {
        fprintf(stderr, "Failed to allocate memory for the output string of sha256 digest\n");
        exit(1);
    }

    size_t i = 0, j = 0, z = EVP_MD_size(EVP_sha256());

    for (i = 0, j = 0; i < z; i++, j += 2) {
        hash[j] = hexlookup[(raw_hash[i] >> 4) & 0x0F];
        hash[j + 1] = hexlookup[raw_hash[i] & 0x0F];
    }

    free(raw_hash); // I did forget about it for a long long time
    hash[j] = '\0';
    return hash;
}
