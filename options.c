#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "options.h"

int optparse(int argc, char *argv[], Options *options) {
    options->board_size = BOARD_SIZE;
    options->board1_name = "board1";
    options->board2_name = "board2";
    options->numbers_filename1 = options->numbers_filename2 = NULL;
    options->user_mode = False;

    int option;
    while((option = getopt(argc, argv, ":s:f:F:n:N:u")) != -1) {
        switch(option){
            case 'u':
                options->user_mode = True;
                break;
            case 's':
                options->board_size = (int)strtol(optarg, NULL, 10);
                if (options->board_size > 8 || options->board_size < 1) {
                    printf("Invalid board size. Board size should be from 1 to 8, you entered %s\n", optarg);
                    return -1;
                }
                break;
            case 'n':
                options->board1_name = optarg;
                break;
            case 'N':
                options->board2_name = optarg;
                break;
            case 'f':
                options->numbers_filename1 = optarg;
                break;
            case 'F':
                options->numbers_filename2 = optarg;
                break;
            case '?':
                printf("unknown option: %c\n", optopt);
                return -1;
        }
   }
   return 0;
}