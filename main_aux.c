#include "include_file.h"



void main_aux_do_game_round(Game *game) {
    /*
     * do one round of game - get command and preform it.
     * Return:
     *     1 - if game should exit after that command.
     *     0 - if should keep playing.
     */
    int EOF_found = 0;
    Command *command;
    printf(">>> STATE: %s\n>>> Please enter a command:\n", game_state_to_string(game->state));
    command = parser_get_command_from_user(&EOF_found);
    if (!command) {
        error_print_memory();
        game->memory_error = 1;
        game->exit_game = 1;
        return;
    }
    do_command(game, command);
    command_free(command);
    if (game->memory_error) {error_print_memory(); game->exit_game = 1;}
    if (game->grb_error && !game->memory_error) {error_print_grb(); game->exit_game = 1;}
    if (EOF_found && !game->exit_game) {error_print_exit(); game->exit_game = 1;}
}

void main_aux_run_game(Game* game){
    while (!game->exit_game) main_aux_do_game_round(game);
}
