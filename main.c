#include <stdlib.h>
#include <stdio.h>
#include <time.h>
typedef enum { False, True } bool;

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

bool is_duplicit_number(int board[BOARD_SIZE][BOARD_SIZE], int number){
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++){
            if (board[i][j] == number) {
                return True;
            }
        }
    return False;
}

int (*user_fill_board(int board[BOARD_SIZE][BOARD_SIZE]))[BOARD_SIZE] {
    srand(time(0));
    int number;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++){
            printf("Enter %d. number:\n", (5*i+j+1));
            scanf("%d", &number);

            while (is_duplicit_number(board, number)){
                printf("Entered number:%d is already there:\n", number);
                printf("Enter %d. number:\n", (5*i+j+1));
                scanf("%d", &number);
            }
            board[i][j] = number;
        }


    return board;
}


int main(int argc, char** argv) {
    int board[BOARD_SIZE][BOARD_SIZE] = { 0 };
    int user_board[BOARD_SIZE][BOARD_SIZE] = { 0 };
    print_board(user_fill_board(user_board));
    print_board(fill_board(board));
}