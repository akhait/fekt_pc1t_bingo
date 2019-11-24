#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "board.h"

//Initialize a board with empty cells
void init_board(Board *board, char *board_name, int board_size) {
    board->name = board_name;
    board->size = board_size;
    for (int i = 0; i < board->size; i++)
        for (int j = 0; j < board->size; j++) {
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

    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
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

    for (int i = 0; i < board->size; i++)
        for (int j = 0; j < board->size; j++) {
            do {
                random_number = (rand() % BOARD_MAX_NUM) + 1;
            } while (board_has_number(board, random_number));  
            board->content[i][j]->value = random_number;
        }
}

int fill_from_file(Board *board, char *filename) {
    FILE *fp;
    char c;
    char buff[2] = { '\n' };
    int number, i = 0, j = 0;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: unable to open %s, check if this file exists and it's permissions\n", filename);
        return -1;
    }

    while ((c = fgetc(fp)) != EOF) {
        if (isspace(c)) {
            number = atoi(buff);
            if (number < 1 || number > 75) {
                printf("Illegal number %d, please only use number from 1 to 75 separated by whitespaces\n", number);
                fclose(fp);
                return -1;
            }

            if (j < board->size) {
                if (board_has_number(board, number)) {
                    printf("Numbers should be unique across one board. Number %d is duplicate\n", number);
                    fclose(fp);
                    return -1;
                }
                board->content[i][j]->value = number;
                buff[0] = buff[1] = '\n';
            }
            else {
                j = 0;
                i++;
                if (i > board->size) {
                    printf("Error: board overflow. Please use less numbers of bigger board size\n");
                    fclose(fp);
                    return -1;
                }
                if (board_has_number(board, number)) {
                    printf("Numbers should be unique across one board. Number %d is duplicate\n", number);
                    fclose(fp);
                    return -1;
                }
                board->content[i][0]->value = number;
                buff[0] = buff[1] = '\n';
            }
            j++;
        }
        else if (!isdigit(c)) {
            printf("%c is not a numeric character, please use only numbers from 1 to 75 sperated by whitespaces\n", c);
            fclose(fp);
            return -1;
        }
        else {
            if (buff[0] == '\n')
                buff[0] = c;
            else if (buff[1] == '\n')
                buff[1] = c;
            else {
                printf("Number %s%c is wrong, please only use numbers from 1 to 75 separated by whitespaces\n",
                        buff, c);
                fclose(fp);
                return -1;
            }
        }
    }

    if (j < board->size || i < board->size - 1) {
        printf("Error: reached EOF, but board isn't full yet . Please use more numbers of lesser board size\n");
        fclose(fp);
        return -1;

    }
    fclose(fp);
    return 0;
}

void debug_fill_board(Board *board) {
    for (int i = 0; i < board->size; i++)
        for (int j = 0; j < board->size; j++)
            board->content[i][j]->value = j + i*5 + 1;
}

// Returns true if number is present in a board
bool board_has_number(Board *board, int number) {
    for (int i = 0; i < board->size; i++)
        for (int j = 0; j < board->size; j++) {
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
    for (int i = 0; i < board->size; i++)
        for (int j = 0; j < board->size; j++){
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
    for (int i = 0; i < board->size; i++)
        if (!board->content[row][i]->status)
            return False;

    return True;
}

// Check every column
bool is_completed_col(Board *board, int col) {
    for (int i = 0; i < board->size; i++)
        if (!board->content[i][col]->status)
            return False;

    return True;
}

// Check first diagonale
bool is_completed_first_diag(Board *board) {
    for (int i = 0; i < board->size; i++)
        if (!board->content[i][i]->status)
            return False;
    return True;
}

// Check second diagonale
bool is_completed_second_diag(Board *board) {
    for (int i = 0, j = board->size-1; i < board->size || j >= 0; i++, j--)
        if (!board->content[i][j]->status)
            return False;
    return True;
}

//Check if board is complete
bool is_completed(Board *board) {
    for (int i = 0; i < board->size; i++) {
        if (is_completed_row(board, i))
            return True;
        if (is_completed_col(board, i))
            return True;
    }
    return is_completed_first_diag(board) || is_completed_second_diag(board);
}

void cleanup(Board *board1, Board *board2) {
    for (int i = 0; i < board1->size; i++)
        for (int j = 0; j < board1->size; j++)
            free(board1->content[i][j]);

    for (int i = 0; i < board2->size; i++)
        for (int j = 0; j < board2->size; j++)
            free(board2->content[i][j]);
}