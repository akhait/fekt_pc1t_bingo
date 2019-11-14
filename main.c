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
        //sleep(BOARD_DELAY);
        //printf("\e[1;1H\e[2J");
    }

    //testing winning conditions
    Board board3;
    init_board(&board3);
    debug_fill_board(&board3);

    board3.content[0][0]->status = STATUS_USED;
    board3.content[0][1]->status = STATUS_USED;
    board3.content[0][2]->status = STATUS_USED;
    board3.content[0][3]->status = STATUS_USED;
    board3.content[0][4]->status = STATUS_USED;

    printf("result of check function: %d\n", has_won(&board3));
    //TODO: generate and match numbers with boards
    //TODO: optparse and reading numbers from file
}