#include <stdio.h>
#include <time.h>
#include "board.h"

//Initialize a board with empty cells
void init_board(Board *board) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            board->content[i][j] = (Cell*) malloc(sizeof(Cell));
            board->content[i][j]->value = 0;
            board->content[i][j]->status = STATUS_EMPTY;
        }
}

// Print a board
// Shows '!' character if the number on a cell has already been used
// Otherwise, the number wasn't used yet
void print_board(Board *board) {
    if (board == NULL)
        printf("<empty board>\n");

    const char *fmt_str;
    Cell *cell;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            cell = board->content[i][j];
            fmt_str = cell->status ? "!%02d " : " %02d ";
            printf(fmt_str, cell->value);
        }
        printf("\n");
    }

    printf("\n");
}

// Fill board with random numbers from 1 to 75
void fill_board(Board *board) {
    srand(time(0));
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board->content[i][j]->value = (rand() % BOARD_MAX_NUM) + 1;
}

void debug_fill_board(Board *board) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board->content[i][j]->value = j + i*5 + 1;
}

// Returns true if number is present in a board
bool board_has_number(Board *board, int number) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board->content[i][j]->value == number) {
                return True;
            }
        }
    return False;
}

// Fill board with numbers from 1 to 75
// Numbers are read from standart input and checked
void user_fill_board(Board *board) {
    srand(time(0));
    int number;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++){
            printf("Enter %d. number:\n", (5*i+j+1));
            scanf("%d", &number);
            while (number < 1 || number > 75) {
                printf("Entered number:%d is not in 1-75 range:\n", number);
                printf("Enter %d. number:\n", (5*i+j+1));
                scanf("%d", &number);
            }
            while (board_has_number(board, number)){
                printf("Entered number:%d is already there:\n", number);
                printf("Enter %d. number:\n", (5*i+j+1));
                scanf("%d", &number);
            }
            board->content[i][j]->value = number;
        }
}