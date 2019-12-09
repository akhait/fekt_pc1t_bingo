#pragma once
#include <stdlib.h>
#include <ncurses.h>

#define MAX_BOARD_SIZE 8
#define BOARD_SIZE 5
#define BOARD_MAX_NUM 75
#define BOARD_DELAY 1

typedef enum status_t {STATUS_EMPTY, STATUS_USED} Status;
typedef enum bool_t { False, True } bool_;

typedef struct cellT {
    int value;
    Status status;
} Cell;

typedef struct boardT {
    Cell *content[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    char *name;
    int size;
} Board;

void init_board(Board *board, char *board_name, int board_size);
void print_board(Board *board);
void fill_board(Board *board);
int fill_from_file(Board *board, char *filename);
bool_ board_has_number(Board *board, int number);
void user_fill_board(Board *board);
void debug_fill_board(Board *board);
bool_ is_completed(Board *board);
void cleanup(Board *board1, Board *board2);
