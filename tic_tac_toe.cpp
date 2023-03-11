#include <iostream>
//#include <string>


void print_board(char (*board)[3]) {
    printf("-------------------------\n");
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            printf("|%4c   ", board[row][col]);
        }
        printf("|\n-------------------------\n");
    }
}

bool win_check(char (*board)[3]) {
    // Row and column check
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X') {
            printf("Player 1 wins!\n");
            return true;
        } else if (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O') {
            printf("Player 2 wins!\n");
            return true;
        } else if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X') {
            printf("Player 1 wins!\n");
            return true;
        } else if (board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] == 'O') {
            printf("Player 2 wins!\n");
            return true;
        }
    }
    // Checks if a diagonal has 3 straight Xs or Os
    if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') {
        printf("Player 1 wins!\n");
        return true;
    } else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') {
        printf("Player 2 wins!\n");
        return true;
    } else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') {
        printf("Player 1 wins!\n");
        return true;
    } else if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O') {
        printf("Player 2 wins!\n");
        return true;
    }
    return false;
}

int main() {
    int player_turn = 0, input = 0, col = 3, row = 3;
    char y[64];
    bool did_someone_win = false;
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };

    while (player_turn < 9) {
        print_board(board);
        printf("%s %d%-30s%s", "Player", (player_turn % 2) + 1, "'s turn:  ", "\033[20D");
        std::fgets(y, 64, stdin);

        try {
            input = std::stoi(std::string(y));
        } catch (const std::out_of_range &e) {
            fprintf(stderr, "Boss you trying to buffer overflow this tic tac toe program?\n");
            exit(1);
        }

        row = (input - 1) / 3;
        col = (input - 1) % 3;

        if (row <= 2 && col <= 2 && board[row][col] != 'X' && board[row][col] != 'O') {
            if (player_turn % 2 == 0) {
                board[row][col] = 'X';
            } else {
                board[row][col] = 'O';
            }

            player_turn++;
            did_someone_win = win_check(board);
            std::cout << "\033[8A\r";
        } else {
            printf("\033[8A\rYour number is out of range bud!\n");
        }

        if (did_someone_win) {
            print_board(board);
            exit(0);
        }
    }

    print_board(board);
    printf("%-38s\n", "It's a tie!");
    return 0;
}
