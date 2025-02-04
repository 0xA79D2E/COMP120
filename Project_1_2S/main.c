/*
* Tic Tac Toe
* Input: Integer representing square on board parsed from user input with scanf()
* Output: Outputs board and user input prompts to terminal with printf()
*
* Author: Shygaan Khalili
* Date: Feb-01-2025
* Sources: link or credit for any sources you referenced in creating this work.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


void printBoard(int board[3][3]) {
    printf("=========\n");

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            switch (board[i][j]) {
                case 1:
                    printf(" ✗ ");
                    break;
                case 2:
                    printf(" ◯ ");
                    break;
                default:
                    printf(" %i ", i*3 + j);
                    break;
            }
        }

        printf("\n");
    }
}

void userPick(int board[3][3]) {

    int user_pick;
    char buffer[100];

    int esc = 0;

    while (esc == 0) {
        printf("Select an empty square (0-8): ");
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("ERR: Failed to read input. \n");
        } else if (buffer[0] == '\n') {
            printf("ERR: Input cannot be empty. \n");
        } else if (sscanf(buffer, "%d", &user_pick)) {
            if (user_pick < 0 || user_pick > 8) {
                printf("ERR: Square [%i] does not exist.\n", user_pick);
            } else if (board[user_pick/3][user_pick % 3] == 0) {
                board[user_pick/3][user_pick % 3] = 1;
                esc = 1;
            } else printf("ERR: Square [%i] filled.\n", user_pick);
        } else printf("ERR: Input must be an integer.\n");
    }
}


void cpuPick(int board[3][3]) {
    int esc = 0;
    while (esc == 0) {
        int row = rand() % 3;
        int col = rand() % 3;

        if (board[row][col] == 0) {
            board[row][col] = 2;
            esc = 1;
        }
    }
}


void clearBoard(int board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = 0;
        }
    }
}

int checkWin(int board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        // Check for horizontal match
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != 0) {
            //End Game
            //Clear  Board
            // Print New Board
            printf("\nhorizontal @ row %d", i);
            return board[i][0];
        }

        // Check for vertical match
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != 0) {
            //End Game
            //Clear  Board
            // Print New Board
            printf("\nvertical @ column %d", i);
            return board[0][i];
        }
    }

    //Check for diagonal match
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != 0) {
        //End Game
        //Clear  Board
        // Print New Board
        printf("\ndiagonal\n");
        return board[0][0];
    }

    // Check for anti-diagonal match
    if (board[0][2] == board[1][1] && board[0][0] == board[2][0] && board[0][2] != 0) {
        //End Game
        //Clear  Board
        // Print New Board
        printf("\nanti-diagonal\n");
        return board[0][2];
    }
}

int main(void) {
    int board[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    int quit = 0;

    while (checkWin(board) != 1/* && quit != 1*/) {
        userPick(board);
        printBoard(board);
        cpuPick(board);
        printBoard(board);
    }


    return 0;
}
