/**
 * Tic Tac Toe
 * Input: User selects a square (0-8) to place their mark (X).
 * Output: Displays the game board and prompts the user for input.
 *
 * Author: Shygaan Khalili
 * Date: Feb-01-2025
 */

#include <stdio.h>
#include <ctype.h>

// Integer values of positions on board array
#define PLAYER 1
#define CPU 2
#define EMPTY 0

/**
 * Checks if there are any valid moves remaining on the board
 * @param board - game board array
 * @return 1 if moves remain, 0 if board is full
 */
int isMovesLeft(int board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * Evaluates current board state to determine if there's a winner or draw
 * @param board - game board array
 * @param print - flag to control printing of win messages (1=print, 0=silent)
 * @return PLAYER if player wins, CPU if AI wins, -1 for draw, 0 for ongoing game
 */
int checkWinner(int board[3][3], int print) {
    // Iterate through each row and column to check for three-in-a-row
    for (int i = 0; i < 3; ++i) {
        // Check for horizontal match in row i
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != 0) {
            if (print == 1) {
                if (board[i][0] == PLAYER) {
                    printf("\nPlayer win? Impossible!\n");
                } else printf("\nCPU win!\n");
            }
            return board[i][0];
        }
        // Check for vertical match in column i
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != 0) {
            if (print == 1) {
                if (board[0][i] == PLAYER) {
                    printf("\nPlayer win? Impossible!\n");
                } else printf("\nCPU win!\n");
            }
            return board[0][i];
        }
    }

    // Check both diagonal matches
    if ((board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != 0) ||
        (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != 0)) {
        if (print == 1) {
            if (board[1][1] == PLAYER) {
                printf("\nPlayer win? Impossible!\n");
            } else printf("\nCPU win!\n");
        }
        return board[1][1];
    }

    // If there are moves left, game is ongoing
    if (isMovesLeft(board)) {
        return 0;
    }

    // If we get here, no moves left, must be a draw
    if (print == 1) printf("\nDraw.\n");
    return -1;
}

/**
 * Displays the current board state
 * Prints X for player moves, @ for CPU moves, and position numbers (0-8) for empty cells
 * @param board - game board array
 */
void printBoard(int board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == PLAYER) {
                printf(" X ");
            } else if (board[i][j] == CPU) {
                printf(" @ ");
            } else {
                printf(" %d ", i * 3 + j);
            }
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("---+---+---\n");
    }
    printf("\n");
}

void clearBoard(int board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = EMPTY;
        }
    }
}

/**
 * Handles input for player turn with error checking
 * Keeps prompting until a valid move is made
 * @param board - game board array
 */
void userPick(int board[3][3]) {
    int user_pick;
    int esc = 0; // Loop control flag

    while (esc == 0) {
        char buffer[100]; // Buffer for safe input handling
        printf("Select an empty square (0-8): ");

        // Handle various input error cases
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("ERR: Failed to read input.\n");
        } else if (buffer[0] == '\n') {
            printf("ERR: Input cannot be empty.\n");
        } else if (sscanf(buffer, "%d", &user_pick)) {
            // Check if selected position is valid and empty
            if (user_pick < 0 || user_pick > 8) {
                printf("ERR: Square [%i] does not exist.\n", user_pick);
            } else if (board[user_pick / 3][user_pick % 3] == 0) {
                board[user_pick / 3][user_pick % 3] = 1; // Make the move
                printf("Player chooses: %d\n", user_pick);
                esc = 1; // Exit loop after valid move
            } else {
                printf("ERR: Square [%i] is already occupied.\n", user_pick);
            }
        } else {
            printf("ERR: Input must be an integer.\n");
        }
    }
}

/**
 * Evaluates current board state for minimax algorithm
 * @param board - game board array
 * @return 10 for CPU win, -10 for player win, 0 for no winner
 */
int evalBoard(int board[3][3]) {
    int winner = checkWinner(board, 0);
    if (winner == PLAYER) return -10; // Player win is bad for CPU
    if (winner == CPU) return 10; // CPU win is good for CPU
    return 0; // No winner
}

/**
 * Recursively evaluates all possible future game states
 * @param board - game board array
 * @param depth - current recursion depth
 * @param turn - whose turn it is (PLAYER or CPU)
 * @return best possible score from given position
 */
int minimax(int board[3][3], int depth, int turn) {
    int score = evalBoard(board);
    if (score == 10) return 10 - depth; // Fast wins are prioritized
    if (score == -10) return -10 + depth; // Slow losses are forced
    if (!isMovesLeft(board)) return 0; // Draw

    int best;
    if (turn == CPU) {
        best = -1000; // If CPU turn, maximize score
    } else best = 1000; // If player turn, minimize score

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = turn; // Try move

                int nextTurn;
                if (turn == CPU) {
                    nextTurn = PLAYER; //Flip between turns each call
                } else nextTurn = CPU;

                int nextScore = minimax(board, depth + 1, nextTurn);

                board[i][j] = EMPTY; // Undo move

                // Select best score based on turn
                if (turn == CPU) {
                    if (nextScore > best) best = nextScore; // Maximizing
                } else {
                    if (nextScore < best) best = nextScore; // Minimizing
                }
            }
        }
    }
    return best;
}

/**
 * Uses minimax function to determine and execute the best possible move for the CPU
 * @param board - game board array
 */
void cpuPick(int board[3][3]) {
    int bestScore = -1000;
    int moveRow = -1, moveCol = -1;

    // Try all possible movesssss
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = CPU; // Try move
                int moveScore = minimax(board, 0, PLAYER); // Evaluate opponent response
                board[i][j] = EMPTY; // Undo move

                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    moveRow = i; // Store move index
                    moveCol = j;
                }
            }
        }
    }

    // Execute best move
    if (moveRow != -1 && moveCol != -1) {
        board[moveRow][moveCol] = CPU;
        printf("\nCPU chooses: %d\n", moveRow * 3 + moveCol);
    }
}

/**
 * Prompts user to quit or begin new game
 */
int isQuit() {
    char input;

    while (1) {
        char buffer[100];
        printf("Start new game? (Y/n) ");
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("ERR: Failed to read input.\n");
        } else if (sscanf(buffer, "%c", &input)) {
            input = tolower(buffer[0]);
            if (input == 'n') {
                // User wishes to quit
                return 1;
            } else return 0;
        }
    }
}

/**
 * Game loop
 * Alternates between player and CPU moves until game ends. When game ends, prompt to continue or quit.
 */
int main(void) {
    // Initialize empty game board
    int board[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    int quit = 0;

    while (quit == 0) {
        printBoard(board);

        // Continue game until there's a winner or draw
        while (checkWinner(board, 1) == 0) {
            userPick(board);
            printBoard(board);

            // Make CPU move if game isn't over
            if (isMovesLeft(board) && !checkWinner(board, 0)) {
                cpuPick(board);
                printBoard(board);
            }
        }
        clearBoard(board); // Reset board after game
        quit = isQuit(); // Check for quit prompt
    }

    return 0;
}
