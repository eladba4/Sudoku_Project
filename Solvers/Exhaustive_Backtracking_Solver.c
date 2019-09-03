/*
 * Created by Owner on 8/8/2019.
 */

#include "../include_file.h"

typedef struct {
    int i,j,first_visit,can_edit;
} Params;

int do_iteration(Stack *stack, Board *board, int *solutions_counter);

int is_valid_option_set_if_valid(Board *board, int x, int y, int option);

int next_x(int n, int x, int y);

int next_y(int n, int x, int y);

Params *generate_next_params(int n, int x, int y);

void params_free(Params* params);

int solvers_get_number_of_solutions(Board* board) {
    /*
     * return number of solutions.
     * if malloc failed return -1
     */
    int solutions_counter = 0, remove;
    Stack* stack = stack_generate();
    if (!stack) return -1;
    if (board_has_errors(board)) return 0;
    if (!stack_push(stack, generate_next_params(board_get_N(board), 1, 0)))
        {stack_free(stack); return -1;};
    while (!stack_is_empty(stack)) {
        remove = do_iteration(stack, board, &solutions_counter);
        if (remove == 1) params_free((Params*)stack_pop(stack));
        if (remove == -1) return -1;

    }
    stack_free(stack);
    return solutions_counter;
}



int next_y(int n, int x, int y) {
    x = x+1; /*want to get x to match next_x*/
    return y%n + 1;
}

int next_x(int n, int x, int y) {
    if (y<n) return x;
    return x+1;
}

int is_valid_option_set_if_valid(Board *board, int x, int y, int option) {
    int result = 1, value = board_get(board, x, y);
    board_set(board, x, y, option);
    if (board_is_error(board, x, y)) {
        result = 0;
        board_set(board, x, y, value);
    }
     return result;
}

int do_iteration(Stack *stack, Board *board, int *solutions_counter) {
    /*
     * assume stack isn't empty!
     * return 1 if should remove
     * 0 if shouldn't remove
     * -1 if malloc failed
     */
    int remove = 1, N = board_get_N(board),
            max_range = N+1;
    int x, y, option;
    Params* params = (Params*)stack_peek(stack);
    Params* next_params;
    x = params->i ; y = params->j ;
    /*if we reached beyond the end - we found new solution!*/
    if (x>N) {
        solutions_counter[0]++;
        return 1;
    }
    /*if it's first visit - we should check if we can change this cell*/
    if (params->first_visit && board_is_empty(board, x, y))
        params->can_edit = 1;

    if (!params->can_edit) {
        if (params->first_visit) {
            next_params = generate_next_params(N, x, y);
            if (!next_params) return -1;
            if (!stack_push(stack, next_params)) return -1;
            remove = 0;
        }
    }
    else {
        /*go over other options*/
        option = board_get(board, x, y) + 1;
        while (option<max_range) {
            if (is_valid_option_set_if_valid(board, x, y, option)) {
                next_params = generate_next_params(N, x, y);
                if (!next_params) return -1;
                if (!stack_push(stack, next_params)) return -1;
                remove = 0;
                break;
            }
            option++;
        }
        if (remove) board_set_empty(board, x, y);
    }
    params->first_visit = 0;
    return remove;
}

Params *generate_next_params(int N, int x, int y) {
    /*
     * return next params.
     * if malloc failed return NULL.
     */
    Params* params;
    params = (Params*)malloc(sizeof(Params));
    if (!params) return NULL;
    params->i = next_x(N, x, y); params->j= next_y(N, x, y);
    params->first_visit = 1; params->can_edit = 0;
    return params;
}

void params_free(Params* params) {free(params);}
