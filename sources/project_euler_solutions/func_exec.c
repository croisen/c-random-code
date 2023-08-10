#include <openssl/evp.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "math_funcs.h"
#include "problem_001_005.h"
#include "problem_006_010.h"
#include "problem_011_015.h"
#include "problem_016_020.h"
#include "func_exec.h"

#define f(x) function_array[ x - 1 ] = problem_##x
#define array_size 20


long (*function_array[array_size]) (bool verbose, bool testing);

char *sha256(unsigned char *message) {
    unsigned char *raw_hash = NULL;

    EVP_MD_CTX *x;
    x = EVP_MD_CTX_new();
    EVP_DigestInit_ex(x, EVP_sha256(), NULL);
    EVP_DigestUpdate(x, message, strlen((const char *)message));

    raw_hash = (unsigned char*)OPENSSL_malloc(EVP_MD_size(EVP_sha256()));

    EVP_DigestFinal_ex(x, raw_hash, NULL);

    EVP_MD_CTX_free(x);

    const char hexlookup[17] = "0123456789abcdef";
    char *hash = (char*)malloc((2 * EVP_MAX_MD_SIZE) + 1);
    size_t i, j, z = EVP_MD_size(EVP_sha256());

    for (i = 0, j = 0; i < z; i++, j += 2) {
        hash[j] = hexlookup[(raw_hash[i] >> 4) & 0x0F];
        hash[j + 1] = hexlookup[raw_hash[i] & 0x0F];
    }

    hash[j] = '\0';

    return hash;
}

void get_function(int problem_num, bool verbose, bool testing_mode) {
    f(  1); f(  2); f(  3); f(  4); f(  5);
    f(  6); f(  7); f(  8); f(  9); f( 10);
    f( 11); f( 12); f( 13); f( 14); f( 15);
    f( 16); f( 17); f( 18); f( 19); f( 20);

    if ((problem_num > array_size) | (problem_num == 0)) {
        not_implemented(problem_num, verbose, testing_mode);
        return;
    }

    if (!testing_mode) {
        (void)function_array[problem_num - 1](verbose, testing_mode);
    } else {
        FILE *fp = fopen("./sources/project_euler_solutions/project_euler_hashes.txt", "r");
        if (fp == NULL) {
            fp = fopen("./project_euler_hashes.txt", "r");
        }

        if (fp == NULL) {
            printf("project_euler_hashes.txt cannot be found\n");
            printf("It should be in the same directory as this executable\n");
            printf("Or it should be in your current working directory as you run this executable\n");
            return;
        }

        int i = 0;
        char correct_hash[66];
        while ( fgets(correct_hash, sizeof(correct_hash), fp) ) {
            if (i >= array_size) {
                break;
            }

            long x = function_array[i](verbose, testing_mode);
            unsigned char *y = num_to_char(x);
            char *hash = sha256(y);
            correct_hash[strcspn(correct_hash, "\n")] = '\0';

            if (strcmp((const char*)hash, correct_hash) == 0) {
                printf("Problem #%3d: \033[1;32mPASSED\033[0;0m\n", i + 1);
            } else {
                printf("Problem #%3d: \033[1;31mFAILED\033[0;0m, My Ans: %ld\nCurrent  Hash: %s\nExpected hash: %s\n",
                       i + 1, x, hash, correct_hash);
            }

            i++;
        }
        fclose(fp);
    }
}
