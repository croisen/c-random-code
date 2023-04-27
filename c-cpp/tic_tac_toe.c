#include <stdio.h>


#define cols 3
#define rows 3

void print_board(char (*board)[cols]) {
    printf("-------------------------\n");
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            printf("|%4c   ", board[row][col]);
        }
        printf("|\n-------------------------\n");
    }
}

int win_check(char (*board)[cols]) {
    for (int i = 0; i < rows; i++) {
        if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X') {
            printf("Player 1 wins!           \n");
            return 1;
        } else if (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O') {
            printf("Player 2 wins!           \n");
            return 1;
        } else if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X') {
            printf("Player 1 wins!           \n");
            return 1;
        } else if (board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] == 'O') {
            printf("Player 2 wins!           \n");
            return 1;
        }
    }

    if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') {
        printf("Player 1 wins!           \n");
        return 1;
    } else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') {
        printf("Player 2 wins!           \n");
        return 1;
    } else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') {
        printf("Player 1 wins!           \n");
        return 1;
    } else if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O') {
        printf("Player 2 wins!           \n");
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
        print_board(board);
        printf("%s %d%-30s%s", "Player", (player_turn % 2) + 1, "'s turn:  ", "\033[20D");

        if (fgets(input_char, 64, stdin) != NULL) {
            input_int = atoi(input_char);
        } else {
            input_int = 10;
        }

        if (input_int <= 9 && input_int >= 1) {
            row = (input_int - 1) / 3;
            col = (input_int - 1) % 3;
        } else {
            printf("\033[8A\rYour number is out of range bud!\n");
            continue;
        }

        if (board[row][col] != 'X' && board[row][col] != 'O') {
            if (player_turn % 2 == 0) {
                board[row][col] = 'X';
            } else {
                board[row][col] = 'O';
            }

            player_turn++;
            printf("\033[8A\r");
        } else if (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("\033[8A\rThat space is already occupied.\n");
            continue;
        } else {
            printf("\033[8A\rYour number is out of range bud!\n");
            continue;
        }

        if (win_check(board) == 1) {
            print_board(board);
            return 0;
        }
    }

    print_board(board);
    printf("%-38s\n", "It's a tie!");
    return 0;
}
