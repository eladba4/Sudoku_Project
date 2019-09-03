/*
 * Game.c
 *
 *  Created on: Aug 7, 2019
 *      Author: Owner
 */

#include "../include_file.h"
int game_add_as_next_step(Game* game, int i, int j, int old_val, int new_val);


/*Game Struct functions*/
Game* game_generate(){
    Game* result = malloc(sizeof(Game));
    if (!result) return NULL;
    result->board = NULL;
    result->mark_errors = 0;
    result->memory_error = 0;
    result->grb_error = 0;
    result->exit_game = 0;
    result->state = game_state_init;
    result->pNode = ll_generate_start_node();
    if (!result->pNode) return NULL;
    return result;
}
void game_free(Game* game){
    if (game->board) board_free(game->board);
    if (game->pNode) ll_command_free(game->pNode);
    free(game);
}

int game_set(Game* game, int i, int j, int new_val) {
    /*
     * set the i,j cell in game->board to new_val.
     * assume:
     *     game->board is initialized,
     *     game isn't on init mode.
     *     i,j,new_val all valid.
     * Return:
     *     0 - memory failed.
     *     1 - else.
     */
    int old_val = board_get(game->board, i, j);
    if (old_val == new_val) return 1;
    board_set(game->board, i, j, new_val);
    if (!game_add_as_next_step(game, i, j, old_val, new_val)) return 0;
    return 1;
}
int game_change_state(Game* game, game_state gameState){
    /*
     * clear pNode list, generate new one.
     * change  game->state to gameState.
     * Return:
     *     0 - mem error.
     *     1- succeed.
     */
    if (gameState == game_state_init) {
        board_free(game->board);
        game->board = NULL;
    }
    ll_command_free(game->pNode);
    game->pNode = ll_generate_start_node();
    if (!game->pNode) return 0;
    game->state = gameState;
    return 1;
}
int game_board_copy(Game* game, Board* new_board){
    /*
     * copy new_board to board using game_set.
     * change only game->board.
     * Assume same sizes.
     * Return:
     *     0 - mem error.
     *     1 - succeed.
     */
    int game_val , board_val,
        N = board_get_N(new_board), i, j;
    for (i = 1; i<=N; i++)
        for (j = 1; j<=N; j++) {
            game_val = board_get(game->board, i, j);
            board_val = board_get(new_board, i, j);
            if (game_val == board_val) continue;
            if (!game_set(game, i, j, board_val)) return 0;
        }
    return 1;
}
void game_print(Game* game){
    int mark_errors = game->mark_errors;
    if (game->state == game_state_edit) mark_errors = 1;
    if (game->memory_error || game->grb_error) return;
    if (!board_print(game->board, mark_errors))
        game->memory_error = 1;
}


char* game_state_to_string(game_state gameState){
    if (gameState == game_state_edit) return "edit";
    if (gameState == game_state_solve) return "solve";
    if (gameState == game_state_init) return "init";
    return "";
}



/*Redo - Undo functions*/
/*
 * Add Command to the List:
 *     1. start with game_add_as_next_command(game, cmd_type).
 *     2. each board set during the command preform with game_set.
 *     3. finish with game_remove_command_if_no_change(game).
 */
int game_add_as_next_command(Game* game, Command_Type cmd_type){
    /*
     * Return:
     *     0 - if memory error.
     *     1 - else.
     */
    int result = ll_gen_cut_insert(game->pNode, node_type_command, cmd_type);
    game->pNode = game->pNode->next;
    return result;
}
int game_add_as_next_step(Game* game, int i, int j, int old_val, int new_val){
    /*
     * return 0 if memory error.
     */
    return ll_add_step(game->pNode, i, j, old_val, new_val);
}
void game_remove_command_if_no_change(Game* game){
    LL_Command_Node* cmd_node = game->pNode;
    if (cmd_node->node_type == node_type_start) return;
    if (cmd_node->first_step == NULL) {
        game->pNode = cmd_node->prev;
        ll_cut_tail(game->pNode);
    }
}

void game_print_change(Game* game, int i, int j, int value){
    printf("    Cell : (%d, %d) , Old Value: %d, New Value: %d\n",
            j, i, board_get(game->board, i, j), value);
}

void game_do_step(Game *game, LL_Step_Node *pNode, int redo, int print) {
    /*
     * if redo == 0: undo step,
     * else - redo step
     */
    int i = pNode->i, j = pNode->j, value;
    if (redo) value = pNode->new_val;
    else value = pNode->old_val;
    if (print) game_print_change(game, i, j, value);
    board_set(game->board, i, j, value);
}
void game_do_command(Game* game, LL_Command_Node* pNode, int redo, int print){
    /*
     * if redo == 0: undo command,
     * else - redo command
     */
    LL_Step_Node *stepNode = pNode->last_step;
    if (redo) stepNode = pNode->first_step;
    while (stepNode) {
        game_do_step(game, stepNode, redo, print);
        if (redo) stepNode = stepNode->next;
        else stepNode = stepNode->prev;
    }
}


int game_undo(Game* game, int print){
    /*
     * Undo full command in game.
     * if game->pNode->begin_of_command, move pointer to the previous node,
     * then do game_undo_step until reach another begin of command (or NULL).
     * Return:
     *     1 - if any change made.
     *     0 - else.
     */
    LL_Command_Node* node = game->pNode;
    if (node->node_type == node_type_start) return 0;
    game->pNode = node->prev;
    if (print)
        printf("Undo %s:\n", command_type_to_string(node->command_type));
    game_do_command(game, node, 0, print);
    return 1;
}
int game_redo(Game* game, int print){
    /*
     * Redo full command in game.
     * if game->pNode->next == NULL : return 0.
     * Return:
     *     1 - if any change made.
     *     0 - else.
     */
    LL_Command_Node* node = game->pNode, *redo_node;
    if (node->next == NULL) return 0;
    redo_node = node->next;
    game->pNode = redo_node;
    if (print)
        printf("Redo %s:\n", command_type_to_string(redo_node->command_type));
    game_do_command(game, redo_node, 1, print);
    return 1;
}
int game_reset(Game* game){
    /*
     * do game_undo until no change has been made.
     * Return:
     *     1 - made any change.
     *     0 - else.
     */
    int state = 1, first = 1;
    while (state) {
        state = game_undo(game, 0);
        if (first && !state) return 0;
        first = 0;
    }
    return 1;
}
