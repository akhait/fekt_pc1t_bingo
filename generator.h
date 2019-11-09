#pragma once
#include "board.h"

int generator_of_board_numbers(void);
void change_status(Board *board, int generated_number);
int available_numbers[BOARD_MAX_NUM];