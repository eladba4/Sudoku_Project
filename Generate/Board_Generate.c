#include "../include_file.h"

#define MAKE_COMP_HAPPY_BOARDGENRATE

int get_rand_option(int *options, int len) {
    int rand_idx;
    if (len == 0) return -1;
    rand_idx = rand()%len;
    return options[rand_idx];
}
int get_random_valid_option(Board* board, int i , int j){
    int num_of_options = 0, option, result;
    int *options = malloc(board_get_N(board)*sizeof(int));
    if (!options) return 0;
    for (option = 1; option <= board_get_N(board); option++){
        if (board_is_valid_option(board, i, j, option)) {
            options[num_of_options] = option;
            num_of_options++;
        }
    }
    result = get_rand_option(options, num_of_options);
    free(options);
    return result;
}
Cell *gen_all_empty_cells(Board *board) {
    int i,j, N = board_get_N(board), result_ptr = 0;
    Cell *result = malloc(sizeof(Cell) * board->num_of_empty);
    if (!result) return NULL;
    for (i = 1; i<= N; i++)
        for(j = 1; j<=N; j++) {
            if (board_is_empty(board, i, j)) {
                result[result_ptr].i = i;
                result[result_ptr].j = j;
                result_ptr++;
            }
        }
    return result;
}
int choose_and_fill_empty_cell(Board *board, Cell *cells) {
    int choose_idx = rand()%(board->num_of_empty), value,
            i = cells[choose_idx].i , j = cells[choose_idx].j;
    cells[choose_idx].i = cells[board->num_of_empty-1].i;
    cells[choose_idx].j = cells[board->num_of_empty-1].j;
    value = get_random_valid_option(board, i, j);
    if (value == 0) return 0;
    if (value == -1) return -1;
    board_set(board, i, j ,value);
    return 1;
}
int fill_X_empty_cells(Board *board, int x) {
    Cell *all_empty_cells;
    int state = 1;
    all_empty_cells = gen_all_empty_cells(board);
    if (!all_empty_cells) return 0;
    while (x>0) {
        state = choose_and_fill_empty_cell(board, all_empty_cells);
        if (state == 0) return 0;
        if (state == -1) break;
        x--;
    }
    free(all_empty_cells);
    return state;
}


Cell *gen_all_non_empty_cells(Board *board) {
    int i,j, N = board_get_N(board), result_ptr = 0,
        num_non_empty_cells = N*N - board->num_of_empty;
    Cell *cell;
    Cell *result = malloc(num_non_empty_cells * sizeof(Cell));
    if (!result) return NULL;
    for (i = 1; i<= N; i++)
        for(j = 1; j<=N; j++) {
            if (!board_is_empty(board, i, j)) {
                cell = malloc(sizeof(Cell));
                if (!cell) return NULL;
                result[result_ptr].i = i;
                result[result_ptr].j = j;
                result_ptr++;
            }
        }
    return result;
}
int choose_and_empty_cell(Board *board, Cell *cells) {
    int N = board_get_N(board),
        num_of_non_empty = N*N - board->num_of_empty,
        choose_idx = rand()%num_of_non_empty,
        i = cells[choose_idx].i , j = cells[choose_idx].j;
    cells[choose_idx].i = cells[num_of_non_empty-1].i;
    cells[choose_idx].j = cells[num_of_non_empty-1].j;
    board_set_empty(board, i, j);
    return 1;
}
int keep_Y_cells(Board *board, int y) {
    Cell *all_non_empty_cells;
    int state;
    all_non_empty_cells = gen_all_non_empty_cells(board);
    if (!all_non_empty_cells) return 0;
    while (y>0) {
        state = choose_and_empty_cell(board, all_non_empty_cells);
        if (state == 0) return 0;
        if (state == -1) break;
        y--;
    }
    free(all_non_empty_cells);
    return state;
}
#ifdef _GRB_

int board_puzzle_inside(Game *game, int x, int y, int *count, int *grb_error) {
    /*
     * return : 1 - operation succeed,
     *          0 - mem failed,
     *         -1 - chosen cell has no legal value or grb_error.
     */
    Board* new_board;
    int state = 1 ,sol_found,
        N = board_get_N(game->board);
    (*count)++;
    new_board = board_clone(game->board);
    if (!new_board) return 0;
    state = fill_X_empty_cells(new_board, x);
    if (state == 0) return 0;
    if (state == -1) {board_free(new_board); return -1;}
    if (!solvers_ILP(new_board, &sol_found, grb_error)) return 0;
    if (*grb_error || !sol_found) {board_free(new_board); return -1;}
    state = keep_Y_cells(new_board, N*N - y);
    if (state == 0) return 0;
    if (state == -1) {board_free(new_board); return -1;}
    if (!game_board_copy(game, new_board)) return 0;
    board_free(new_board);
    return 1;
}

int board_puzzle_clean_board(Game *game) {
    int N = board_get_N(game->board), i, j;
    for (i = 1; i<=N; i++)
        for (j = 1; j<=N; j++)
            if (!game_set(game, i, j, 0)) return 0;
    return 1;
}

int board_puzzle(Game* game, int x, int y, int *grb_error){
    /*
     * do generate command as specified in project pdf.
     * return 1 - all mem allocation succeed,
     *        0 - mem problem occurred.
     *        -1 - reached 1000 iterations.
     */
    int count = 0, state;
    *grb_error = 0;
    if (y == 0) {
        if (!board_puzzle_clean_board(game)) return 0;
        return 1;
    }
    while (count < 1000) {
        state = board_puzzle_inside(game, x, y, &count, grb_error);
        if (state == 0) return 0;
        if (state == 1) return 1;
        if (*grb_error) return 1;
    }
    return -1;

}

#endif
