//
// Created by Admin on 2/5/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PLAYER_X 1  // Human
#define PLAYER_O 2  // AI
#define EMPTY 0

// Function prototypes
void printBoard(int board[3][3]);
int checkWin(int board[3][3], int print);
int isMovesLeft(int board[3][3]);
int evalBoard(int board[3][3]);
int minimaxAI(int board[3][3], int depth, int isMaximizing);
void bestMove(int board[3][3]);
void userPick(int board[3][3]);

int main(void) {
    int board[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

    printBoard(board);

    while (checkWin(board, 1) == 0 && isMovesLeft(board)) {
        userPick(board);
        printBoard(board);

        if (checkWin(board, 0) == 0 && isMovesLeft(board)) {
            bestMove(board);
            printBoard(board);
        }
    }

    int winner = checkWin(board, 1);
    if (winner == PLAYER_X) {
        printf("\nYou win!\n");
    } else if (winner == PLAYER_O) {
        printf("\nAI wins!\n");
    } else {
        printf("\nIt's a draw!\n");
    }

    return 0;
}

// Function to print the board
void printBoard(int board[3][3]) {
    printf("\n=========\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == PLAYER_X) {
                printf(" X ");
            } else if (board[i][j] == PLAYER_O) {
                printf(" O ");
            } else {
                printf(" %d ", i * 3 + j);  // Show available positions
            }
        }
        printf("\n");
    }
}

// Checks for win/draw
int checkWin(int board[3][3], int print) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != EMPTY)
            return board[i][0]; // Row win
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != EMPTY)
            return board[0][i]; // Column win
    }

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != EMPTY)
        return board[0][0]; // Main diagonal win
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != EMPTY)
        return board[0][2]; // Anti-diagonal win

    return (isMovesLeft(board)) ? 0 : -1; // 0 = ongoing, -1 = draw
}

// Checks if there are moves left
int isMovesLeft(int board[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == EMPTY)
                return 1;
    return 0;
}

// Evaluates board state
int evalBoard(int board[3][3]) {
    int winner = checkWin(board, 0);
    if (winner == PLAYER_X) return -10; // Human wins → bad for AI
    if (winner == PLAYER_O) return +10; // AI wins → good for AI
    return 0; // Draw
}

// Minimax function
int minimaxAI(int board[3][3], int depth, int isMaximizing) {
    int score = evalBoard(board);

    if (score == 10 || score == -10 || !isMovesLeft(board))
        return score;

    if (isMaximizing) {
        int best = INT_MIN;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    best = (best > minimaxAI(board, depth + 1, 0)) ? best : minimaxAI(board, depth + 1, 0);
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = INT_MAX;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X;
                    best = (best < minimaxAI(board, depth + 1, 1)) ? best : minimaxAI(board, depth + 1, 1);
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

// AI selects the best move
void bestMove(int board[3][3]) {
    int bestScore = INT_MIN;
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER_O;
                int moveScore = minimaxAI(board, 0, 0);
                board[i][j] = EMPTY;

                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }

    if (moveRow != -1 && moveCol != -1) {
        board[moveRow][moveCol] = PLAYER_O;
        printf("\nAI chooses: %d\n", moveRow * 3 + moveCol);
    }
}

// Prompts the user for a valid move
void userPick(int board[3][3]) {
    int user_pick;
    char buffer[100];

    while (1) {
        printf("\nSelect an empty square (0-8): ");
        if (!fgets(buffer, sizeof(buffer), stdin)) continue;

        if (sscanf(buffer, "%d", &user_pick) != 1 || user_pick < 0 || user_pick > 8) {
            printf("ERR: Invalid input. Enter a number between 0-8.\n");
            continue;
        }

        int row = user_pick / 3, col = user_pick % 3;
        if (board[row][col] == EMPTY) {
            board[row][col] = PLAYER_X;
            break;
        } else {
            printf("ERR: Square [%d] is occupied.\n", user_pick);
        }
    }
}
