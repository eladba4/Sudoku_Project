/*
 * main.c
 *
 *  Created on: Aug 7, 2019
 *      Author: Owner
 */
#include "include_file.h"

int main() {
    Game *game;
    game = game_generate();
    if (!game) {
        error_print_memory();
        exit(EXIT_FAILURE);
    }
    printf("------------- Sudoku -------------\n");
    main_aux_run_game(game);
    if (game->memory_error) exit(EXIT_FAILURE);
    if (game->grb_error) {
        game_free(game);
        exit(EXIT_FAILURE);
    }
    else {
        game_free(game);
        exit(EXIT_SUCCESS);
    }
}

