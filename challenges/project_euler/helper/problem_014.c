#include <stdio.h>

int collatz_chain(long int num) {
    int chain_count = 1;

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

int main() {
    int highest_chain_count = 3;
    int num_with_highest_chain_count = 2;

    for (int i = 2; i < 1000000; i++) {
        int current_chain_count = collatz_chain(i);
        printf("\rCurrent number = %7d, Current Chain Count = %6d", i, current_chain_count);

        if (current_chain_count > highest_chain_count) {
            highest_chain_count = current_chain_count;
            num_with_highest_chain_count = i;
            printf("\nNEW! Number = %7d, Chain count = %6d\n", i, highest_chain_count);
        }
    }

    printf("\nThe number with the highest Collatz(?) chain number is %d\n", num_with_highest_chain_count);
    return 0;
}
