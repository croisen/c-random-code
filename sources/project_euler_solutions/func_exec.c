#include "func_exec.h"
#include "math_funcs.h"
#include "problem_001_005.h"
#include "problem_006_010.h"
#include "problem_011_015.h"
#include "problem_016_020.h"

#define f(x) function_array[ x - 1 ] = problem_##x
#define array_size 20

char *(*function_array[array_size]) (bool verbose, bool testing);

void get_function(int_fast64_t problem_num, bool verbose, bool testing_mode) {
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
            printf("project_euler_hashes.txt cannot be found\n");
            printf("You have the following options regarding said file\n");
            printf("1. From your current directory the project_euler_hashes.txt\n");
            printf("must reside in sources/project_euler_solutions folder\n");
            printf("2. Edit the source code to change where it finds the file\n");
            printf("It is in sources/project_euler_solutions/func_exec.c line 27\n");
            return;
        }

        int_fast64_t i = 0;
        char *correct_hash = calloc(EVP_MAX_MD_SIZE + 2, sizeof(char)); // hash size, \n, \0
        char *my_ans       = NULL;
        char *hash         = NULL;

        while ( fgets(correct_hash, EVP_MAX_MD_SIZE + 2, fp) ) {
            if (i >= array_size) {
                break;
            }
            correct_hash[strcspn(correct_hash, "\n")] = '\0';

            my_ans = function_array[i](verbose, testing_mode);
            hash = sha256_digest(my_ans);

            if (strncmp(hash, correct_hash, EVP_MAX_MD_SIZE) == 0) {
                printf("Problem #%3ld: \033[1;32mPASSED\033[0;0m\n", i + 1);
            } else {
                printf("Problem #%3ld: \033[1;31mFAILED\033[0;0m, My Ans: %s\n", i + 1, my_ans);
                printf("Current  Hash: %s\nExpected hash: %s\n", hash, correct_hash);
            }

            i++;
            free(my_ans);
            free(hash);
        }

        free(correct_hash);
        fclose(fp);
    }
}
