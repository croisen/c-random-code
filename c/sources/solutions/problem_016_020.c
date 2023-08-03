#include <gmp.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "math_funcs.h"
#include "problem_016_020.h"


long problem_16(bool verbose, bool testing) {
    // Using gmp to get 2^1000, then taking it's digits and summing it all up

    if (!testing) {
        printf("Currently summing up the digits in 2^1000...\n");
    }

    mpz_t two, result, a;
    mpz_inits(two, result, a, NULL);
    mpz_ui_pow_ui(two, 2, 1000);

    if (verbose) {
        gmp_printf("2^1000 = %Zd\n", two);
    }

    while (mpz_cmp_si(two, 0)) {
        mpz_mod_ui(a, two, 10);
        mpz_add(result, result, a);
        mpz_div_ui(two, two, 10);

        if (verbose) {
            gmp_printf("Current sum of digits: %Zd, two^100 status: %Zd\n", result, two);
        }
    }

    if (!testing) {
        gmp_printf("The sum of all the digits of 2^1000 is: %Zd\n", result);
    }

    long x = (long)mpz_get_ui(result);
    return x;
}

long problem_17(bool verbose, bool testing) {
    // I used strlen after confirming if it's a single digit num, a teen num, 20 above, 100 above
    // and 1000

    char *ones[] = {
        "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
        "sixteen", "seventeen", "eighteen", "nineteen"
    };

    char *tens[] = {
        "", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    char *unit[] = {
        "and", "hundred", "thousand"
    };

    if (!testing) {
        printf("Currently getting the number of letters used by the numbers 1 to 1 thousand.\n");
        printf("Sample: if the numbers 1 to 5 are written out in words: one, two, three, four, five, then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.\n");
    }

    int total_number_of_letters = 0, number_of_letters = 0;

    for (int i = 1; i <= 1000; i++) {
        if (i < 20) {
            number_of_letters = strlen(ones[i]);
            if (verbose) {
                printf("Current number = %4d, number of letters = %3d -> %s\n",
                       i, number_of_letters, ones[i]);
            }

            total_number_of_letters += number_of_letters;
            continue;
        }

        if ((20 <= i) && (i < 100)) {
            number_of_letters = strlen(tens[i / 10]) + strlen(ones[i % 10]);
            if (verbose) {
                printf("Current number = %4d, number of letters = %3d -> %s %s\n",
                       i, number_of_letters, tens[i / 10], ones[i % 10]);
            }

            total_number_of_letters += number_of_letters;
            continue;
        }

        if ((100 <= i) && (i < 1000)) {
            if (i % 100 != 0) {
                if (((i % 100) > 19)) {
                    number_of_letters = 
                        strlen(ones[i / 100]) + strlen(unit[1]) + strlen(unit[0]) +  // x hundred and...
                        strlen(tens[(i % 100) / 10]) + strlen(ones[(i % 100) % 10]); // tens and ones place

                    if (verbose) {
                        printf("Current number = %4d, number of letters = %3d -> %s %s %s %s %s\n",
                               i, number_of_letters, ones[i / 100], unit[1], unit[0],
                               tens[(i % 100) / 10], ones[(i % 100) % 10]);
                    }
                } else {
                    number_of_letters =
                        strlen(ones[i / 100]) + strlen(unit[1]) + strlen(unit[0]) +
                        strlen(ones[(i % 100)]);

                    if (verbose) {
                        printf("Current number = %4d, number of letters = %3d -> %s %s %s %s\n",
                               i, number_of_letters, ones[i / 100], unit[1], unit[0],
                               ones[(i % 100)]);
                    }
                }
                total_number_of_letters += number_of_letters;
                continue;
            } else {
                number_of_letters = strlen(ones[i / 100]) + strlen(unit[1]);
                if (verbose) {
                    printf("Current number = %4d, number of letters = %3d -> %s %s\n",
                           i, number_of_letters, ones[i / 100], unit[1]);
                }

                total_number_of_letters += number_of_letters;
                continue;
            }
        }

        if (i == 1000) {
            number_of_letters = strlen(ones[i / 1000]) + strlen(unit[2]);

            if (verbose) {
                printf("Current number = %4d, number of letters = %3d -> %s %s\n",
                       i, number_of_letters, ones[i / 1000], unit[2]);
            }
            total_number_of_letters += number_of_letters;
        }
    }

    if (!testing) {
        printf("The total number of letters used by the numbers one to one thousand is: %d\n",
            total_number_of_letters);
    }
    return (long)total_number_of_letters;
}

void print_pr18_pyr(int pyramid[][15], int *offsets, int layers) {
    // Well I did have a massive printf statement that has spaces and all indexes to it
    // Then I counted the amount of spaces and I realized it can be predicted so it forms
    // a pyramid aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

    for (int layer = 0; layer < layers; layer++) {
        for (int space = 14 - layer; space > 0; space--) {
            printf("  ");
        }

        for (int index = 0; index < layers; index++) {
            if (pyramid[layer][index] != 0) { // Well I can only do this to check if it ain't empty
                if ((offsets == NULL) || (index != offsets[layer])) {
                    printf("%02d  ", pyramid[layer][index]);
                } else {
                    printf("\033[1;31m%02d\033[0;0m  ", pyramid[layer][index]);
                }
            }
        }

        printf("\n");
    }
    printf("\n\n");
}

long problem_18(bool verbose, bool testing) {
    // Look ma, I built a pyramid
    // Anyways there will be a function that returns 0 or 1 depending on which number
    // is bigger, 0 if left, 1 if right
    // Using the output of that it could be used as an offset if used collectively
    // when going through layer by layer to get the number below the bigger number
    // in the pyramid.
    // Lemme explain (I can already feel that this is gonna be long
    // as I cannot explain things)

    // Sample is:
    //     75
    //    9  20
    //  0   4   6
    //  The one with 75 has an index of 0 so let's add 0 to the offset that is currently 0
    //  then to get the index of the two numbers below 75 you add the offset to 0 and 1 to get
    //  the left number below and right number below 75 respectively.
    //  Let's say the function that compares numbers looks like this:
    //  compare(int left, int right);

    //  Now the compare function will return 1 as the second argument 20 is bigger than 9
    //  This is where the offset will make sense as now we add 1 to it
    //  Using the index 0 and 1 to get the left and right number, when we add the offset to it
    //  we will get the left and right numbers below 20 respectively that being 4 and 6

    //  Does this serve as an explanation? Even I am confused now that I'm trying to do this
    //  Well it doesn't really serve well though since if it ignores a path that starts with
    //  a small number but ends with a large sum. Basically this is just searching at depth 1

    int number_pyramid[15][15] = {
                                        {75},
                                      {95, 64},
                                    {17, 47, 82},
                                  {18, 35, 87, 10},
                                {20,  4, 82, 47, 65},
                              {19,  1, 23, 75,  3, 34},
                            {88,  2, 77, 73,  7, 63, 67},
                          {99, 65,  4, 28,  6, 16, 70, 92},
                        {41, 41, 26, 56, 83, 40, 80, 70, 33},
                      {41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
                    {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
                  {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
                {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
              {63, 66,  4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
            { 4, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23},
    };

    if (!testing) {
        printf("Trying to find the maximum total from top to bottom from this triangle\n");
        printf("By starting at the top of the triangle below and moving to adjacent\n");
        printf("numbers on the row below\n");
    }

    long total = 0;
    
    for (int depth = 1; depth <= 3; depth++) {
        int offsets[15];
        int offset = 0;
        total = 0;

        for (int layer = 0; layer < 15; layer++) {
            int depth_offset = 0;
            int choice1 = number_pyramid[layer][offset];
            int choice2 = number_pyramid[layer][offset + 1];

            // Now it would consider all the choices below the number
            // and would search according to the depth given
            // Well I still do not know what is happening though

            for (int current_depth = 1; current_depth < depth; current_depth++) {
                if (choice1 < choice2) {
                    depth_offset += 1; 
                }

                if (layer + current_depth > 14) {
                    choice1 += number_pyramid[layer][offset - depth_offset] +
                                number_pyramid[layer][offset - depth_offset + 1];
                    choice2 += number_pyramid[layer][offset + 1 - depth_offset] +
                                number_pyramid[layer][offset - depth_offset + 2];
                } else {
                    choice1 += number_pyramid[layer + current_depth][offset - depth_offset] +
                                number_pyramid[layer + current_depth][offset - depth_offset + 1];
                    choice2 += number_pyramid[layer + current_depth][offset + 1 - depth_offset] +
                                number_pyramid[layer + current_depth][offset - depth_offset + 2];
                }

                if (verbose) {
                    printf("Layer: %2d Current depth: %2d Choice1: %3d Choice2: %3d Offset: %d\n",
                           layer, current_depth, choice1, choice2, offset);
                }
            }

            if (choice1 < choice2) {
                offset += 1; 
            }

            offsets[layer] = offset;
            total += number_pyramid[layer][offsets[layer]];

            if (verbose) {
                printf("Layer: %2d Offset: %2d Value: %2d\n", layer, offsets[layer],
                       number_pyramid[layer][offsets[layer]]);
            }
        }

        if (!testing) {
            printf("Depth: %d, Sum of the red numbers: %ld\n", depth, total);
            print_pr18_pyr(number_pyramid, offsets, 15);
        }
    }


    if (!testing) {
        printf("In the triangle by starting at the top of the triangle\nbelow and moving to adjacent numbers on the row below,\nthe maximum total from top to bottom is: %ld\n", total);
    }

    return total;
}

long problem_19(bool verbose, bool testing) {
    not_implemented(19, verbose, testing);
    return 0;
}

long problem_20(bool verbose, bool testing) {
    mpz_t factorial, result, mod10;
    mpz_inits(factorial, result, mod10, NULL);
    mpz_set_ui(result, 0);
    mpz_fac_ui(factorial, 100);

    long sum_of_digits = 0;

    if (!testing) {
        printf("Currently summing up the digits of 100! (100 factorial)...\n");
    }

    while (mpz_cmp_si(factorial, 0)) {
        if (verbose) {
            gmp_printf("Factorial digits: %Zd, Current sum = %Zd\n", factorial, result);
        }

        mpz_mod_ui(mod10, factorial, 10);
        mpz_div_ui(factorial, factorial, 10);
        mpz_add(result, result, mod10);
    }

    sum_of_digits = (long)mpz_get_ui(result);

    if (!testing) {
        gmp_printf("The sum of all the digits of 100! (100 factorial) is %Zd\n", result);
    }

    return sum_of_digits;
}
