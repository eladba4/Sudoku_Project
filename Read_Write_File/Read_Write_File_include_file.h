/*
 * Created by Owner on 8/12/2019.
 */


#ifndef PROJECTFILES_READ_WRITE_FILE_INCLUDE_FILE_H
#define PROJECTFILES_READ_WRITE_FILE_INCLUDE_FILE_H
#include "../include_file.h"

int board_save(Board* board, char* path, game_state state);
Board* board_load(char *path, int *valid_format,int *valid_values,
                  int* valid_mn, int* valid_path, int* valid_close, int *valid_malloc);

#endif

