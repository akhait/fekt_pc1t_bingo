#include <stdio.h>
#include <time.h>
#include "generator.h"
#include "board.h"


int generator_of_board_numbers(){
    srand(time(0));
    int random_index = (rand() % BOARD_MAX_NUM) + 1;
    while (available_numbers[random_index] == 0){
        random_index = (random_index + 1) % BOARD_MAX_NUM;
    }
    int number = available_numbers[random_index];
    available_numbers[random_index] = 0;
    return number;
}

void change_status(Board *board, int generated_number){
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board->content[i][j]->value == generated_number) {
                board->content[i][j]->status = STATUS_USED;
            }
        }
}