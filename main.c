#include <stdlib.h>
#include <stdio.h>
#include "board.h"

int main() {
    Board board1, board2;
    init_board(&board1);
    init_board(&board2);
    fill_board(&board1);
    user_fill_board(&board2);
    print_board(&board1);
    print_board(&board2);
    //TODO: generate and match numbers with boards
    //TODO: optparse and reading numbers from file
}