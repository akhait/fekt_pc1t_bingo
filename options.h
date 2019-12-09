typedef struct optionsT {
    int board_size;
    char *board1_name;
    char *board2_name;
    char *numbers_filename1;
    char *numbers_filename2;
    bool user_mode;

} Options;

int optparse(int argc, char *argv[], Options *options);
