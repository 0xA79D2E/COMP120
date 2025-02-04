/*
* Tic Tac Toe
* Input: Integer representing square on board parsed from user input with scanf()
* Output: Outputs board and user input prompts to terminal with printf()
*
* Author: Shygaan Khalili
* Date: Feb-01-2025
* Sources: link or credit for any sources you referenced in creating this work.
*/


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int board[9] = {
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
};


int newGame = 0;

int quit = 0;
int win = 0;


void printBoard(int squares[]) {
    printf("===========\n");
    for (int i = 0; i < 3; ++i) {
        //printf("\n");


        for (int j = 0; j < 3; ++j) {
            switch (squares[(i * 3) + j]) {
                case 0:
                    printf(" %i ", (i * 3) + j);
                    break;
                case 1:
                    printf(" ✗ ");
                    break;
                case 2:
                    printf(" ◯ ");
                    break;
                default:
                    break;
            }
        }
        printf("\n");


        /*
        for (int k = 0; k < 3; ++k) {
            printf(" %c%i ", i+97, k+1);
            //if (k != 2) printf("|");
        }*/
        //if (i != 2) printf("\n———————————");
    }
}

void clearBoard() {
    for (int i = 0; i < 9; ++i) {
        board[i] = 0;
    }
}

/*int isTouching(int a, int b) {
    if (board[a + 1] == board[a]);

    if (board[a + 3] == board[a]);

    if (board[a] == board[4]);
}*/

void winMsg(int winner) {
    switch (winner) {
        case 0:
            printf("Draw.\n");
            break;
        case 1:
            printf("User wins!\n");
            break;
        case 2:
            printf("CPU wins!\n");
            break;
        default:
            break;
    }
}


void endGame(int state) {
    winMsg(state);

    clearBoard();


    //char buffer[100];

    /*
    if (buffer[0] == '\n') {
        printf("ERR: Input cannot be empty.\n");
    } else if (sscanf(buffer, "%d", &user_pick)) {
        if (board[user_pick] == 0) {
            board[user_pick] = 1;
            esc = 1;
        } else printf("ERR: Square [%i] filled.\n", user_pick);
    } else printf("ERR: Input must be an integer.\n");
    */


    char choice;

    printf("Start new game? (Y/n) ");
    scanf(" %c", &choice);
    if (choice == 'n') {
        printf("n choice");
        quit = 1;
    } else {
        quit = 0;
    }


    newGame = 1;
}


int checkWin() {
    for (int i = 0; i < 3; ++i) {
        if ((board[i * 3] == board[(i * 3) + 1]) && (board[i * 3] == board[(i * 3) + 2]) && (board[i * 3] != 0)) {
            printf("\nhorizontal @ row %d", i);
            endGame(board[i]);
            clearBoard();
            printBoard(board);
            return board[i];
        }

        if ((board[i] == board[i + 3]) && (board[i] == board[i + 6]) && (board[i] != 0)) {
            printf("\nvertical @ column %d", i);
            endGame(board[i]);
            clearBoard();
            printBoard(board);
            return board[i];
        }
    }

    if (board[0] == board[4] && board[0] == board[8] && board[0] != 0) {
        printf("\ndiagonal @ 0\n");
        endGame(board[0]);
        clearBoard();
        printBoard(board);
        return board[0];
    }

    if (board[2] == board[4] && board[2] == board[6] && board[2] != 0) {
        printf("\ndiagonal @ 2\n");
        endGame(board[0]);
        clearBoard();
        printBoard(board);
        return board[0];
    }

    /*int draw = 1;
    for (int i = 0; i<9; ++i) {
        if (board[i] == 0) {
            draw = 0;
            i = 9;
        }
    } if (draw == 1) {
        endGame(0);
        return 1;
    }*/


    return 0;
}


void userPick(void) {
    int user_pick;
    char buffer[100];


    int esc = 0;

    while (esc == 0) {
        printf("Select an empty square (0-8): ");
        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("ERR: Failed to read input. \n");
        } else if (buffer[0] == '\n') {
            printf("ERR: Input cannot be empty.\n");
            continue; // Ask for input again
        } else if (sscanf(buffer, "%d", &user_pick)) {
            if (user_pick < 0 || user_pick > 8) {
                printf("ERR: Square [%i] does not exist.\n", user_pick);
            } else if (board[user_pick] == 0) {
                board[user_pick] = 1;
                esc = 1;
            } else printf("ERR: Square [%i] filled.\n", user_pick);
        } else printf("ERR: Input must be an integer.\n");
    }


    /*
    do {
        scanf(" %i", &user_pick);

        if (!isdigit(user_pick)) {
            printf("ERR: Input must be an integer");
            scanf(" %i", &user_pick);
        } else if ((user_pick >= 0) && (user_pick <= 8)) {

        } else printf("ERR: Square [%i] does not exist.\n", user_pick);

    } while (esc != 1);*/
}

void cpuPick(void) {
    int esc = 0;
    do {
        int cpu_pick = rand() % 9;

        if (board[cpu_pick] == 0) {
            board[cpu_pick] = 2;
            esc = 1;
        }
    } while (esc != 1);
}

int main(void) {
    printBoard(board);

    while (checkWin() != 1 && quit != 1) {
        userPick();
        printBoard(board);
        cpuPick();
        printBoard(board);
    } //endGame(checkWin());


    return 0;
}
