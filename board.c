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
        printw("<empty board>\n");

    const char *fmt_str;
    Cell *cell;

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            cell = board->content[i][j];
            fmt_str = " %02d ";
            if(cell->status){
                attron(COLOR_PAIR(1));
                printw(fmt_str, cell->value);
                attroff(COLOR_PAIR(1));
            }else printw(fmt_str, cell->value);
        }
        printw("\n");
    }

    printw("\n");
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
        printw("Error: unable to open %s, check if this file exists and it's permissions\n", filename);
        return -1;
    }

    while ((c = fgetc(fp)) != EOF) {
        if (isspace(c)) {
            number = atoi(buff);
            if (number < 1 || number > 75) {
                printw("Illegal number %d, please only use number from 1 to 75 separated by whitespaces\n", number);
                fclose(fp);
                return -1;
            }

            if (j < board->size) {
                if (board_has_number(board, number)) {
                    printw("Numbers should be unique across one board. Number %d is duplicate\n", number);
                    fclose(fp);
                    return -1;
                }
                board->content[i][j]->value = number;
                buff[0] = buff[1] = '\n';
            }
            else {
                j = 0;
                i++;
                if (i >= board->size) {
                    printw("Error: board overflow. Please use less numbers of bigger board size\n");
                    fclose(fp);
                    return -1;
                }
                if (board_has_number(board, number)) {
                    printw("Numbers should be unique across one board. Number %d is duplicate\n", number);
                    fclose(fp);
                    return -1;
                }
                board->content[i][0]->value = number;
                buff[0] = buff[1] = '\n';
            }
            j++;
        }
        else if (!isdigit(c)) {
            printw("%c is not a numeric character, please use only numbers from 1 to 75 sperated by whitespaces\n", c);
            fclose(fp);
            return -1;
        }
        else {
            if (buff[0] == '\n')
                buff[0] = c;
            else if (buff[1] == '\n')
                buff[1] = c;
            else {
                printw("Number %s%c is wrong, please only use numbers from 1 to 75 separated by whitespaces\n",
                        buff, c);
                fclose(fp);
                return -1;
            }
        }
    }

    if (j < board->size || i < board->size - 1) {
        printw("Error: reached EOF, but board isn't full yet . Please use more numbers of lesser board size\n");
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
bool_ board_has_number(Board *board, int number) {
    for (int i = 0; i < board->size; i++)
        for (int j = 0; j < board->size; j++) {
            if (board->content[i][j]->value == number) {
                return True;
            }
        }
    return False;
}

void highlighted_print_board(Board *board, int y, int x, bool_ game_hint) {
    clear();
    if (board == NULL)
        printw("<empty board>\n");

    const char *fmt_str;
    Cell *cell;

    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            cell = board->content[i][j];
            fmt_str = " %02d ";
            if(i==y && j==x){
                attron(COLOR_PAIR(2));
                printw(fmt_str, cell->value);
                attroff(COLOR_PAIR(2));
            }else printw(fmt_str, cell->value);
        }
        printw("\n");
    }

    printw("\n");

    if(game_hint){
        move(40, 0);
        printw("i: insert number\n");
        printw("s: save board");
    }
    curs_set(0);
    refresh();
}

bool_ board_number_out_of_range(int number){
    if(number < 1 || number > 75){
        return True;
    }
    return False;
}

void getting_number(Board *board, int y, int x ){
    highlighted_print_board(board, y, x, False);
    int number;
    bool_ number_ok = False;
    do {
        printw("Enter number: ");
        curs_set(1);
        refresh();
        echo();
        scanw("%d", &number);

        if(board_has_number(board, number)) {
            printw("This number is already set.\n");
            continue;
        }
        else if (board_number_out_of_range(number)) {
            printw("Number is not in range <1-75>.\n");
            continue;
        }
        else
            number_ok = True;
    } while(!number_ok);
    noecho();
    board->content[y][x]->value = number;
}

bool_ is_filled(Board *board){
    Cell *cell;
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            cell = board->content[i][j];
            if(cell->value == 0){
                return False;
            }
        }
    }
    return True;
}
// Fill board with numbers from 1 to 75
// Numbers are read from standart input and checked
void user_fill_board(Board *board) {
    int ch;
    int y = 0;
    int x = 0;

    highlighted_print_board(board, y, x, True);

    for (;;) {
        ch = getch();
        switch (ch) {
            case KEY_BACKSPACE: /* user pressed backspace */
                break;
            case KEY_UP:  /* user pressed up arrow key */
                if(y == 0) {y = board->size -1;}
                else{y--;}
                highlighted_print_board(board, y, x, True);
                break;
            case KEY_DOWN:  /* user pressed up arrow key */
                y = (y+1)% board->size;
                highlighted_print_board(board, y, x, True);
                break;
            case KEY_RIGHT:   /* user pressed key 'A' */
                x = (x+1) % board->size;
                highlighted_print_board(board, y, x, True);
                break;
            case KEY_LEFT:
                if(x == 0){x = board->size - 1;}
                else{x = (x-1) % board->size;}
                highlighted_print_board(board, y, x, True);
                break;
            case 'i':
                getting_number(board , y, x);
                if (x < board->size - 1)
                    x++;
                else {
                    x = 0;
                    y++;
                }
                highlighted_print_board(board, y, x, True);
                break;
            case 's':
                if(!is_filled(board)) {
                    highlighted_print_board(board, y, x, True);
                    printw("\nBoard is not yet filled.\n");
                }
                else{return;}
        }

    }
}

// Check if given board id completed
// Check every row
bool_ is_completed_row(Board * board, int row) {
    for (int i = 0; i < board->size; i++)
        if (!board->content[row][i]->status)
            return False;

    return True;
}

// Check every column
bool_ is_completed_col(Board *board, int col) {
    for (int i = 0; i < board->size; i++)
        if (!board->content[i][col]->status)
            return False;

    return True;
}

// Check first diagonale
bool_ is_completed_first_diag(Board *board) {
    for (int i = 0; i < board->size; i++)
        if (!board->content[i][i]->status)
            return False;
    return True;
}

// Check second diagonale
bool_ is_completed_second_diag(Board *board) {
    for (int i = 0, j = board->size-1; i < board->size || j >= 0; i++, j--)
        if (!board->content[i][j]->status)
            return False;
    return True;
}

//Check if board is complete
bool_ is_completed(Board *board) {
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
