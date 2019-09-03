/*
 * Created by Owner on 8/12/2019.
 */

#include "../include_file.h"

int get_next_value_from_file(FILE *fptr, Board *board, int i , int j , int *valid_values, int *valid_format) {
    int value, state, N = board_get_N(board);
    char next_char;
    state = fscanf(fptr, "%d", &value);
    if (state<=0) {*valid_format = 0; return 0;}
    if (value<0 || value>N) {*valid_values = 0; return 0;}
    board_set(board, i, j, value);
    next_char = getc(fptr);
    if (next_char == '.') board_fix(board, i, j);
    else {
        if (!parser_is_white_space(next_char) && next_char!=EOF && next_char!='\n')
            {*valid_format = 0; return 0;}
    }
    return 1;
}
void file_to_mn(FILE *fptr, int *valid_mn, int *valid_format, int *m, int *n) {
    int state = fscanf(fptr, "%d", m);
    if (state<=0) {*valid_format = 0 ; return;}
    state = fscanf(fptr, "%d", n);
    if (state<=0) {*valid_format = 0 ; return;}
    if ((*m)*(*n)>=100 || (*m) <=0 || (*m) <=0) {*valid_mn = 0; return;}
    return;
}

int file_is_finished(FILE* fptr) {
    char c;
    while ( (c = getc(fptr)) !=EOF) 
        if (!parser_is_white_space(c) && c != '\n') return 0;
    return 1;
}

Board* file_to_board(FILE* fptr, int *valid_format, int *valid_values, int *valid_mn, int *valid_malloc) {
    /*
     * return board from file, assume file is valid (NOT NULL)
     * if format is invalid return NULL and valid_format = 0.
     */
    int m,n, N, i, j, succeed;
    Board* result = NULL;
    file_to_mn(fptr, valid_mn, valid_format, &m, &n);
    if (!*valid_format || !*valid_mn) return result;
    result = board_generate(m ,n);
    if (!result) {*valid_malloc = 0 ;return NULL;}
    N = board_get_N(result);
    for (i = 1 ; i<=N; i++) {
        for(j = 1 ; j<=N; j++) {
            succeed = get_next_value_from_file(fptr, result, i, j, valid_values, valid_format);
            if (!succeed) {
                board_free(result); return NULL;
            }
        }
    }
    if (!file_is_finished(fptr)) {
        board_free(result);
        *valid_format = 0;
        return NULL;
    }
    return result;
}

Board* board_load(char *path, int *valid_format,int *valid_values,
        int* valid_mn, int* valid_path, int* valid_close, int *valid_malloc) {
    /*
     * return Board* initialized from file path.
     * if path doesn't exits - return NULL
     * if path exists but file format isn't valid - valid_format = 0.
     */
    FILE *fptr = fopen(path, "r");
    Board* board;
    *valid_format = 1; *valid_path = 1;
    *valid_values = 1; *valid_close = 1;
    *valid_malloc = 1; *valid_mn = 1;
    if (!fptr) {*valid_path = 0 ; return NULL;}
    board = file_to_board(fptr, valid_format, valid_values, valid_mn, valid_malloc);
    if (fclose(fptr)) {
        *valid_close = 0;
        board_free(board);
        return NULL;
    }
    return board;
}



