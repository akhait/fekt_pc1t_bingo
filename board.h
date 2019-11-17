#pragma once
#include <stdlib.h>

#define BOARD_SIZE 5
#define BOARD_MAX_NUM 75
#define BOARD_DELAY 3

typedef enum status_t {STATUS_EMPTY, STATUS_USED} Status;
typedef enum bool_t { False, True } bool;

typedef struct cellT {
    int value;
    Status status;
} Cell;

typedef struct boardT {
    Cell *content[BOARD_SIZE][BOARD_SIZE];
    char *name;
} Board;

void init_board(Board *board);
void print_board(Board *board);
void fill_board(Board *board);
bool board_has_number(Board *board, int number);
void user_fill_board(Board *board);
void debug_fill_board(Board *board);
bool is_completed(Board *board);
