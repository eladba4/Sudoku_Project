/*
 * Game.h
 *
 *  Created on: Aug 7, 2019
 *      Author: Owner
 */

#ifndef GAME_H_
#define GAME_H_
#include "../include_file.h"
typedef enum {game_state_init, game_state_edit, game_state_solve} game_state;
char* game_state_to_string(game_state gameState);

typedef struct {
	game_state state;
	Board* board;
    int mark_errors;
    int memory_error;
    int grb_error;
    int exit_game;
    LL_Command_Node* pNode;
} Game;

Game* game_generate();
void game_free();



int game_add_as_next_command(Game* game, Command_Type cmd_type);
void game_remove_command_if_no_change(Game* game);


int game_set(Game* game, int i, int j, int new_val);
int game_change_state(Game* game, game_state gameState);
int game_board_copy(Game* game, Board* new_board);
void game_print(Game* game);

int game_undo(Game* game, int print);
int game_redo(Game* game, int print);
int game_reset(Game* game);










#endif /* GAME_H_ */
