#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BOARD_SIZE 5
#define BOARD_MAX_NUM 75

void print_board(int board[BOARD_SIZE][BOARD_SIZE]) {
    if (board == NULL)
        printf("<empty board>\n");

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++)
            printf("%02d ", board[i][j]);
        printf("\n");
    }

    printf("\n");
}

int (*fill_board(int board[BOARD_SIZE][BOARD_SIZE]))[BOARD_SIZE] {
    srand(time(0));
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = (rand() % BOARD_MAX_NUM) + 1;
    
    return board;
}

int main(int argc, char** argv) {
    int board[BOARD_SIZE][BOARD_SIZE] = { 0 };
    print_board(board);
    print_board(fill_board(board));
}