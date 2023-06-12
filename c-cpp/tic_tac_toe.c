#include <stdio.h>
#include <stdlib.h>


#define cols 3
#define rows 3

void print_board(char (*board)[cols]) {
    (void) printf("-------------------------\n");
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (atoi(&board[row][col])) {
                (void) printf("|%4c   ", board[row][col]);
            } else if (board[row][col] == 'X') {
                (void) printf("|   \033[1;31m%c\033[1;0m   ", board[row][col]);
            } else {
                (void) printf("|   \033[1;32m%c\033[1;0m   ", board[row][col]);
            }
        }
        (void) printf("|\n-------------------------\n");
    }
}

int win_check(char (*board)[cols]) {
    for (int i = 0; i < rows; i++) {
        if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X') {
            (void) printf("Player 1 wins!           \n");
            return 1;
        } else if (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O') {
            (void) printf("Player 2 wins!           \n");
            return 1;
        } else if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X') {
            (void) printf("Player 1 wins!           \n");
            return 1;
        } else if (board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] == 'O') {
            (void) printf("Player 2 wins!           \n");
            return 1;
        }
    }

    if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') {
        (void) printf("Player 1 wins!           \n");
        return 1;
    } else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') {
        (void) printf("Player 2 wins!           \n");
        return 1;
    } else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') {
        (void) printf("Player 1 wins!           \n");
        return 1;
    } else if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O') {
        (void) printf("Player 2 wins!           \n");
        return 1;
    }
    return 0;
}

int main() {
    int player_turn = 0, input_int = 0, row = 0, col = 0;
    char input_char[16];
    char board[rows][cols] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    while (player_turn < 9) {
        (void) print_board(board);
        (void) printf("%s %d%-30s%s", "Player", (player_turn % 2) + 1, "'s turn:  ", "\033[20D");

        if (fgets(input_char, 16, stdin) != NULL) {
            input_int = atoi(input_char);
        } else {
            input_int = 10;
        }

        if (input_int <= 9 && input_int >= 1) {
            row = (input_int - 1) / 3;
            col = (input_int - 1) % 3;
        } else {
            (void) printf("\033[8A\rYour number is out of range bud!\n");
            continue;
        }

        if (board[row][col] != 'X' && board[row][col] != 'O') {
            if (player_turn % 2 == 0) {
                board[row][col] = 'X';
            } else {
                board[row][col] = 'O';
            }

            player_turn++;
            (void) printf("\033[8A\r");
        } else if (board[row][col] == 'X' || board[row][col] == 'O') {
            (void) printf("\033[8A\rThat space is already occupied.\n");
            continue;
        } else {
            (void) printf("\033[8A\rYour number is out of range bud!\n");
            continue;
        }

        if ((int) win_check(board) == 1) {
            (void) print_board(board);
            return 0;
        }
    }

    (void) print_board(board);
    (void) printf("%-38s\n", "It's a tie!");
    return 0;
}
