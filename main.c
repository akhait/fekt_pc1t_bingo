#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "board.h"
#include "generator.h"


int main() {
    Board board1, board2;
    board1.name = "comp";  // TODO: read from stdin or optparse
    board2.name = "user";  // TODO: read from stdin or optparse
    init_board(&board1);
    init_board(&board2);
    fill_board(&board1);
//    user_fill_board(&board2);
    debug_fill_board(&board2);
    print_board(&board1);
    print_board(&board2);

    for (int n=0; n<BOARD_MAX_NUM; n++){
        available_numbers[n] = n+1;
    }

    int number;
    for(int i = 0; i<BOARD_MAX_NUM; i++)
    {
        number = generator_of_board_numbers();
        printf("Drawed number: %d\n", number);
        change_status(&board1, number);
        change_status(&board2, number);
        print_board(&board1);
        print_board(&board2);
        sleep(BOARD_DELAY);
        printf("\e[1;1H\e[2J");
        if (is_completed(&board1)) {
            printf("\n\n");
            print_board(&board1);
            printf("%s is a winner!\n", board1.name);
            return 0;
        }
        if (is_completed(&board2)) {
            printf("\n\n");
            print_board(&board2);
            printf("%s is a winner!\n", board2.name);
            return 0;
        }

    }

    //TODO: optparse and reading numbers from file
    //TODO: tests, better UI
}