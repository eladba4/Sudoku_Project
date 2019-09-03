/*
 * Created by Owner on 8/12/2019.
 */

#include "../include_file.h"

void board_to_file(Board *board, FILE *fptr, game_state state) {
    int i,j, N = board_get_N(board);
    fprintf(fptr ,"%d %d\n", board->m, board->n);
    for (i = 1; i <= N; i++){
        for (j = 1; j<=N; j++) {
            fprintf(fptr, "%d", board_get(board, i, j));
            if ((board_is_fixed(board, i, j)) ||
                (state == game_state_edit && !board_is_empty(board, i, j)) )
                fprintf(fptr, ".");
            if (j<N) fprintf(fptr, " ");
        }
        if (i<N) fprintf(fptr, "\n");
    }
    return;
}

int board_save(Board* board, char *path, game_state state) {
    /*
     * save board to path.
     * return 1 is succeed, 0 else.
     */
    FILE *fptr = fopen(path, "w");
    if (!fptr) return 0;
    board_to_file(board, fptr, state);
    if (fclose(fptr)) return 0;
    return 1;
}

