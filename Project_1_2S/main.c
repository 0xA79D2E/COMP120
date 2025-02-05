/*
 * Tic Tac Toe
 * Input: User selects a square (0-8) to place their mark (X).
 * Output: Displays the game board and prompts the user for input.
 *
 * Author: Shygaan Khalili
 * Date: Feb-01-2025
 */

#include <stdio.h>
#include <stdlib.h>

// Checks for a win or a draw
int checkWin(int board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        // Check for horizontal win
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != 0) {
            printf("\nHorizontal win at row %d", i);
            return board[i][0];
        }

        // Check for vertical win
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != 0) {
            printf("\nVertical win at column %d", i);
            return board[0][i];
        }
    }

    // Check for diagonal or anti-diagonal win
    if ((board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != 0) ||
        (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != 0)) {
        printf("\nDiagonal win");
        return board[1][1];
        }


    // Check for a draw
    //currently only checks if all squares are filled and no win has occured
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == 0) return 0; // Game still in progress

    return -1; // Draw
}

// Prints the current state of the board
void printBoard(int board[3][3]) {
    printf("=========\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            switch (board[i][j]) {
                case 1:
                    printf(" ✗ "); // Player's move
                    break;
                case 2:
                    printf(" ◯ "); // CPU's move
                    break;
                default:
                    printf(" %i ", i * 3 + j); // Empty square with its index
                    break;
            }
        }
        printf("\n");
    }
}

// Prompts the user to select a valid move
void userPick(int board[3][3]) {
    int user_pick;
    char buffer[100];
    int esc = 0;

    while (esc == 0) { // Loop until user selects a valid empty square
        printf("Select an empty square (0-8): ");

        // Read user input
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("ERR: Failed to read input.\n");
        } else if (buffer[0] == '\n') {
            printf("ERR: Input cannot be empty.\n");
        } else if (sscanf(buffer, "%d", &user_pick)) {
            // Check if input is within valid range
            if (user_pick < 0 || user_pick > 8) {
                printf("ERR: Square [%i] does not exist.\n", user_pick);
            }
            // Check if the square is empty
            else if (board[user_pick / 3][user_pick % 3] == 0) {
                board[user_pick / 3][user_pick % 3] = 1; // Place user mark
                esc = 1;
            } else {
                printf("ERR: Square [%i] is already occupied.\n", user_pick);
            }
        } else {
            printf("ERR: Input must be an integer.\n");
        }
    }
}

// Randomly selects an empty square for the CPU
void cpuPick(int board[3][3]) {
    int esc = 0;
    while (esc == 0) {
        int row = rand() % 3;
        int col = rand() % 3;

        if (board[row][col] == 0) {
            board[row][col] = 2; // Place CPU mark
            esc = 1;
        }
    }
}

// Checks if the board is full
int isBoardFull(int board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 0) return 0; // Board is not full
        }
    }
    return 1; // Board is full
}

// Resets the board by setting all squares to 0
void clearBoard(int board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = 0;
        }
    }
}

int main(void) {
    int board[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    while (checkWin(board) == 0) { // Continue while there is no winner
        userPick(board);
        printBoard(board);

        if (!isBoardFull(board)) { // Ensure CPU doesn't move if board is full
            cpuPick(board);
            printBoard(board);
        }
    }

    return 0;
}
