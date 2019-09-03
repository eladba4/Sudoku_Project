
#ifndef PROJECTFILES_COMMANDS_IMPLEMENTATION_INCLUDE_FILE_H
#define PROJECTFILES_COMMANDS_IMPLEMENTATION_INCLUDE_FILE_H
#include "../include_file.h"
#include "Print_Messages.h"
#include "Commands/Commands_include_file.h"
void do_command(Game* game, Command* command);

/*Shared check functions*/
Board* command_board_load(Game* game, Command* command);
int check_guess_hint_and_hint(Game* game, Command* command);
int check_params_zero_states_solve_board_valid(Game* game, Command* command);
int check_params_zero_states_solve_edit_board_valid(Game* game, Command* command);
int check_params_zero_states_solve_edit(Game* game, Command* command);
void check_if_done_and_print(Game* game);

#endif /*PROJECTFILES_COMMANDS_IMPLEMENTATION_INCLUDE_FILE_H*/
