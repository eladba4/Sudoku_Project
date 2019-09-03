/*
 * Board.h
 *
 *  Created on: Aug 7, 2019
 *      Author: Owner
 */

#ifndef BOARD_H_
#define BOARD_H_

typedef struct{
    int m;
    int n;
    int * nums;
    int * blocks_values_count;
    int * rows_values_count;
    int * cols_values_count;
    /*
     * blocks/rows/cols_values_count[i][j] -
     * count of value j in block/row/col i.
     */
    int num_of_empty;
    /*
     * num_of_errors = count of i,j such that blocks/rows/cols_values_count[i][j]>1
     */
} Board;

Board* board_generate(int m, int n);
int board_get(Board* b, int i, int j);
void board_set (Board* b, int i, int j, int new_val);
int board_is_fixed(Board* b, int m, int n);
int board_print(Board* b, int mark_errors);
int board_has_errors(Board* b);
int board_is_error(Board* b, int i, int j);
int board_get_N(Board* b);
int board_is_empty(Board* b, int i, int j);
void board_set_empty(Board* b, int i, int j);
void board_free(Board* b);
Board* board_clone(Board* board);
int board_is_valid_option(Board* board, int i , int j, int value);
void board_fix(Board* b, int i, int j);
void board_unfix(Board* b, int i, int j);
void board_unfix_all(Board* b);
int board_is_full(Board* b);
int board_get_col_count(Board* b, int idx, int val);
int board_get_row_count(Board* b, int idx, int val);
int board_get_block_count(Board* b, int idx, int val);
#endif /* BOARD_H_ */
