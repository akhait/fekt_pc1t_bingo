#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "board.h"
#include "generator.h"
#include "options.h"

int main(int argc, char **argv) {
    initscr();
    cbreak();
    noecho();
    clear();
    keypad(stdscr, TRUE);
    start_color();

    Board board1, board2;
    Options options;
    int ret;
    if ((ret = optparse(argc, argv, &options))) {
        printw("Error when parsing arguments\n");
        return ret;
    }

    init_board(&board1, options.board1_name, options.board_size);
    init_board(&board2, options.board2_name, options.board_size);

    if (options.numbers_filename1 != NULL) {
        if ((ret = fill_from_file(&board1, options.numbers_filename1))) {
            printw("Error when filling board %s from file %s\n", board1.name, options.numbers_filename1);
            refresh();
            cleanup(&board1, &board2);
            return ret;
        }
    }
    else {
        user_fill_board(&board1);
        clear();
    }

    if (options.user_mode) {
        if (options.numbers_filename2 != NULL) {
            if ((ret = fill_from_file(&board2, options.numbers_filename2))) {
                printw("Error when filling board %s from file %s\n", board2.name, options.numbers_filename2);
                refresh();
                cleanup(&board1, &board2);
                return ret;
            }
        }
        else {
            user_fill_board(&board2);
            clear();
        }
    }
    else
        fill_board(&board2);


    curs_set(0);
    refresh();
    // generate numbers from 1 to 75 in random order
    for (int n=0; n<BOARD_MAX_NUM; n++){
        available_numbers[n] = n+1;
    }

    // main game loop
    int number;
    for(int i = 0; i<BOARD_MAX_NUM; i++)
    {
        number = generator_of_board_numbers();
        printw("Drawed number: %d\n", number);
        change_status(&board1, number);
        change_status(&board2, number);
        print_board(&board1);
        print_board(&board2);
        refresh();
        sleep(BOARD_DELAY);
        clear();

        if (is_completed(&board1)) {
            printw("\n\n");
            change_status(&board1, number);
            print_board(&board1);
            printw("%s is a winner!\n", board1.name);
            refresh();
            cleanup(&board1, &board2);
            break;
        }
        if (is_completed(&board2)) {
            printw("\n\n");
            change_status(&board2, number);
            print_board(&board2);
            printw("%s is a winner!\n", board2.name);
            refresh();
            cleanup(&board1, &board2);
            break;
        }

    }
    getch();
    endwin();
}
