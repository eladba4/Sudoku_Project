/*
 * Created by Owner on 8/11/2019.
*/

#include "../include_file.h"


void autofill_cell(Game *game,Board* board, Board *helper_board, int i, int j, int *change_made) {
    /*
     * check if cell i,j is empty and has only 1 valid option - IN HELPER BOARD.
     * if both true - set cell i,j in board to valid option.
     * return 1 if something changed, 0 else.
     */
    int valid_option = 0,
            option, N = board_get_N(helper_board);
    if (!board_is_empty(helper_board, i, j)) return;
    for (option = 1 ; option <= N ; option++) {
        if (board_is_valid_option(helper_board , i, j, option)) {
            if (valid_option) return;
            valid_option = option;
        }
    }
    if (valid_option) {
        *change_made = 1;
        if (game) {
            if (!game_set(game, i, j, valid_option))
                {game->memory_error = 1; return;}
        }
        else board_set(board, i, j, valid_option);
    }
}



int solvers_autofill(Game* game) {
    /*
     * solver_autofill:
     * Assume board has no error values
     * put values into cells that has only 1 valid value
     * CHANGES BOARD
     * Return - 1 if made any change is board, 0 else.
     */
    Board* board = game->board;
    Board* helper_board = board_clone(board);
    int i, j, N = board_get_N(helper_board),
    change_made = 0;
    for (i = 1 ; i<=N; i++)
        for (j = 1; j<=N; j++)
            autofill_cell(game, NULL, helper_board, i, j, &change_made);
            if (game->memory_error == 1) return 0;
    board_free(helper_board);
    return change_made;
}

int solvers_recurrent_autofill(Board* board) {
    /*
     * do autofill on board, until no change made, or found invalid value.
     * Return - 1 if made any change is board, 0 else.
     */
    int change_made = 1, result = 0, i, j, N = board_get_N(board);
    while (change_made) {
        change_made = 0;
        for (i = 1 ; i<=N; i++)
            for (j = 1; j<=N; j++)
                autofill_cell(NULL, board, board, i, j, &change_made);
        if (change_made) result = 1;
    }
    return result;
}

