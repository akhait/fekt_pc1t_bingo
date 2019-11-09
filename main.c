#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "board.h"
#include "generator.h"


int main() {
    Board board1, board2;
    init_board(&board1);
    init_board(&board2);
    fill_board(&board1);
    user_fill_board(&board2);
    print_board(&board1);
    print_board(&board2);

    for (int n=0; n<BOARD_MAX_NUM; n++){
        available_numbers[n] = n+1;
    }
    int number;
    for(int i = 0; i<BOARD_MAX_NUM; i++)
    {
        number = generator_of_board_numbers();
        change_status(&board1, number);
        change_status(&board2, number);
        print_board(&board1);
        print_board(&board2);
        sleep(BOARD_DELAY);
        //printf("\e[1;1H\e[2J");
    }

    //TODO: generate and match numbers with boards
    //TODO: optparse and reading numbers from file
}