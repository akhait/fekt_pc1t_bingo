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
    int random_number;

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            do {
                random_number = (rand() % BOARD_MAX_NUM) + 1;
            } while (board_has_number(board, random_number));  
            board->content[i][j]->value = random_number;
        }
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

// Check if given board id completed
// Check every row
bool is_completed_row(Board * board, int row) {
    for (int i = 0; i < BOARD_SIZE; i++)
        if (!board->content[row][i]->status)
            return False;

    return True;
}

// Check every column
bool is_completed_col(Board *board, int col) {
    for (int i = 0; i < BOARD_SIZE; i++)
        if (!board->content[i][col]->status)
            return False;

    return True;
}

// Check first diagonale
bool is_completed_first_diag(Board *board) {
    for (int i = 0; i < BOARD_SIZE; i++)
        if (!board->content[i][i]->status)
            return False;
    return True;
}

// Check second diagonale
bool is_completed_second_diag(Board *board) {
    for (int i = 0, j = BOARD_SIZE-1; i < BOARD_SIZE || j >= 0; i++, j--)
        if (!board->content[i][j]->status)
            return False;
    return True;
}

//Check if board is complete
bool is_completed(Board *board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (is_completed_row(board, i))
            return True;
        if (is_completed_col(board, i))
            return True;
    }
    return is_completed_first_diag(board) || is_completed_second_diag(board);
}