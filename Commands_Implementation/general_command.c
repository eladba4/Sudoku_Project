#include "../include_file.h"
void check_if_done(Game* game) {
    Board *board = game->board;
    if (game->state != game_state_solve) return;
    if (game->exit_game || game->memory_error || game->grb_error) return;
    if (board_is_full(board)){
        if (!board_has_errors(board)) {
            printf("Congratulations! You won the game!\n");
            game_print(game);
            if (!game_change_state(game, game_state_init)) game->memory_error = 1;
        }
        else {
            printf("Solution is erroneous!\n");
            game_print(game);
        }
    }
    else game_print(game);
}

void do_command(Game* game, Command* command) {
    Command_Type ctype = command->type;
#ifdef _GRB_
    if (ctype == cmd_type_guess) do_guess(game, command);
    if (ctype == cmd_type_guess_hint) do_guess_hint(game, command);
    if (ctype == cmd_type_validate) do_validate(game, command);
    if (ctype == cmd_type_hint) do_hint(game, command);
    if (ctype == cmd_type_save) do_save(game, command);
    if (ctype == cmd_type_generate) do_generate(game, command);
#endif
    if (ctype == cmd_type_mark_errors) do_mark_errors(game, command);
    if (ctype == cmd_type_print_board) do_print_board(game, command);
    if (ctype == cmd_type_solve) do_solve(game, command);
    if (ctype == cmd_type_edit) do_edit(game, command);
    if (ctype == cmd_type_autofill) do_autofill(game, command);
    if (ctype == cmd_type_num_sols) do_num_solutions(game, command);
    if (ctype == cmd_type_set) do_set(game, command);
    if (ctype == cmd_type_redo) do_redo(game, command);
    if (ctype == cmd_type_undo) do_undo(game, command);
    if (ctype == cmd_type_reset) do_reset(game, command);
    if (ctype == cmd_type_exit) do_exit(game, command);
    if (ctype == cmd_type_invalid_len) error_print_len();
    if (ctype == cmd_type_invalid_command_name) error_print_cmd_name();
}

/*common check function for guess_hint an hint */
int check_params_guess_hint_and_hint(Game* game, Command *command) {
    int i, val, N = board_get_N(game->board);
    for (i = 0; i<=1; i++){
        val = command->params[i];
        if ((command->param_order[i] != 'i') || ((val<1 || val>N)))
            {error_print_param_range(i+1, 1, N); return 0;}
    }
    return 1;
}
int check_guess_hint_and_hint(Game* game, Command* command){
    int i,j;
    if (game->state != game_state_solve)
    {error_print_invalid_state(); return 0;}
    if (!check_number_of_params(command)) return 0;
    if (!check_params_guess_hint_and_hint(game, command)) return 0;
    i = command->params[1]; j = command->params[0];
    if (board_has_errors(game->board))
    {error_print_board_erroneuos(); return 0;}
    if (board_is_fixed(game->board, i, j))
    {error_print_cell_fixed(); return 0;}
    if (!board_is_empty(game->board, i, j))
    {error_print_cell_not_empty(); return 0;}
    return 1;
}

int check_params_zero_states_solve_edit_board_valid(Game* game, Command* command){
    if (game->state == game_state_init){
        error_print_invalid_state();
        error_print_correct_state_solve();
        error_print_correct_state_edit();
        return 0;
    }
    if (!check_number_of_params(command)) return 0;
    if (board_has_errors(game->board))
    {error_print_board_erroneuos(); return 0;}
    return 1;
}
int check_params_zero_states_solve_board_valid(Game* game, Command* command){
    if (game->state != game_state_solve)
    {error_print_invalid_state();error_print_correct_state_solve(); return 0;}
    if (!check_number_of_params(command)) return 0;
    if (board_has_errors(game->board))
    {error_print_board_erroneuos(); return 0;}
    return 1;
}
int check_params_zero_states_solve_edit(Game* game, Command* command){
    if (game->state == game_state_init){
        error_print_invalid_state();
        error_print_correct_state_solve();
        error_print_correct_state_edit();
        return 0;
    }
    if (!check_number_of_params(command)) return 0;
    return 1;
}

Board* command_board_load(Game *game, Command *command){
    /*
     * load board, use in solve and edit command.
     */
    int vformat, vvalues, vmn, vpath, vclose, vmemory;
    Board* new_board = board_load(command->path, &vformat, &vvalues, &vmn, &vpath, &vclose, &vmemory);
    if (!new_board)
    {
        if (!vmn) printf("Error: invalid block size,\nBlock size should be: m >= 0, n >= 0 and m*n<100\n");
        if (!vvalues) printf("Error: board values not in range!\n");
        if (!vformat) printf("Error: file format isn't valid!\n");
        if (!vpath) printf("Error: File path is invalid!\n");
        if (!vclose) printf("Error: Error closing the File!\n");
        if (!vmemory) game->memory_error = 1;
    }
    return new_board;
}

void check_if_done_and_print(Game* game){
    if (game->state == game_state_solve) check_if_done(game);
    else game_print(game);
}
