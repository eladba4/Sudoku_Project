#include "../include_file.h"



/** Auxiliary functions: **/
int board_get_index_in_vector(Board* b, int i, int j) {
    return (i-1)*(board_get_N(b))+(j-1);
}

int board_get_block_idx(Board* b, int i, int j){
    return (i-1) - (i-1)%b->m + (j-1)/b->n + 1;
}

void board_update_count(Board *b, int i, int j, int val, int d) {
    int
    block_idx = board_get_block_idx(b, i, j),
    *cols_count = &(b->cols_values_count[board_get_index_in_vector(b, j, val)]),
    *rows_count = &(b->rows_values_count[board_get_index_in_vector(b, i, val)]),
    *blocks_count = &(b->blocks_values_count[board_get_index_in_vector(b, block_idx, val)]);
    if (val == 0) return;
    *cols_count+= d ; *rows_count+= d ; *blocks_count+= d;
}

char* generate_seperator(Board* board) {
    /*
     * generate seperator for printing board.
     * if malloc failed return NULL.
     */
    int N = board_get_N(board), sep_size = 4*N+board->m+1, i;
    char* seperator = malloc((sep_size+1) * sizeof(char));
    if (!seperator) return NULL;
    for (i = 0 ; i < sep_size ; i++) seperator[i] = '-';
    seperator[sep_size] = '\0';
    return seperator;

}
void print_cell(Board* board, int i, int j, int mark_errors) {
    int fixed = 0, error = 0;
    if (board_is_empty(board, i, j)) {
        printf("    "); return;
    }
    if (board_is_fixed(board, i, j))
        fixed = 1;
    if (board_is_error(board, i, j) && mark_errors)
        error = 1;
    printf(" ");
    printf("%2d", board_get(board, i, j));

    if (fixed)
        printf(".");
    else{
        if (error) printf("*");
        else printf(" ");
    }
}
void array_copy(int* copy_from, int* copy_to, int len) {
    int i;
    for (i = 0 ; i<len; i++) copy_to[i] = copy_from[i];
}

/** end of Auxiliary functions **/

Board* board_generate(int m, int n)
{
    /*
     * return poiner to board.
     * if calloc failed return NULL.
     */
    Board* b; int N = m*n;
    b = (Board*)malloc(sizeof(Board));
    if (!b) return NULL;
    b->nums = (int*)calloc(N*N,sizeof(int));
    if (!b->nums) return NULL;
    b->blocks_values_count = (int*)calloc(N*N,sizeof(int));
    if (!b->blocks_values_count) return NULL;
    b->rows_values_count = (int*)calloc(N*N,sizeof(int));
    if (!b->rows_values_count) return NULL;
    b->cols_values_count = (int*)calloc(N*N,sizeof(int));
    if (!b->cols_values_count) return NULL;
    b->m = m;
    b->n = n;
    b->num_of_empty = N*N;
    return b;
}
void board_free(Board* b)
{
    if (!b) return;
    free(b->rows_values_count);
    free(b->cols_values_count);
    free(b->blocks_values_count);
    free(b->nums);
    free(b);
}
Board* board_clone(Board* board) {
    int n = board->n, m = board->m, N = board_get_N(board);
    Board* result = board_generate(m, n);
    result->num_of_empty = board->num_of_empty;
    if (!result) return NULL;
    array_copy(board->nums, result->nums, N*N);
    array_copy(board->blocks_values_count, result->blocks_values_count, N*N);
    array_copy(board->rows_values_count, result->rows_values_count, N*N);
    array_copy(board->cols_values_count, result->cols_values_count, N*N);
    return result;
}

int board_get(Board* b, int i, int j)
{
    int result = b->nums[board_get_index_in_vector(b, i, j)];
    if (result<0) result = result * -1;
    return result;
}
void board_set(Board* b, int i, int j, int new_val)
{
    int old_val = board_get(b, i, j);
    int fix = board_is_fixed(b, i, j);
    if (fix) new_val *= -1;
    b->nums[board_get_index_in_vector(b, i, j)] = new_val;
    if (old_val != 0) board_update_count(b, i, j, old_val, -1);
    if (new_val != 0) board_update_count(b, i, j, new_val, 1);
    if (old_val == 0 && new_val!=0) b->num_of_empty--;
    if (old_val != 0 && new_val == 0) b->num_of_empty++;
    return;
}

void board_fix(Board* b, int i, int j)
{
    int value = b->nums[board_get_index_in_vector(b, i, j)];
    if (value > 0)
        b->nums[board_get_index_in_vector(b, i, j)] = -1 * value;
}
void board_unfix(Board* b, int i, int j)
{
    int value = b->nums[board_get_index_in_vector(b, i, j)];
    if (value < 0)
        b->nums[board_get_index_in_vector(b, i, j)] = -1 * value;
}
void board_unfix_all(Board* b)
{
    int i, j, N = board_get_N(b);
    for (i = 1 ; i <= N; i++)
        for (j = 1 ; j <= N; j++)
            board_unfix(b , i, j);
}
void board_set_empty(Board* b, int i, int j) {
    board_set(b, i,j,0);
}

int board_is_fixed(Board* b, int i, int j)
{
    int value = b->nums[board_get_index_in_vector(b, i, j)];
    if (value < 0)
        return 1;
    else
        return 0;
}
int board_is_empty(Board* b, int i, int j) {
    return board_get(b, i, j) == 0;
}
int board_is_error(Board* b, int i, int j)
{
    int value = board_get(b, i, j),
        block_idx = board_get_block_idx(b, i, j);
    if (value == 0) return 0;
    if (b->blocks_values_count[board_get_index_in_vector(b, block_idx, value)] > 1) return 1;
    if (b->rows_values_count[board_get_index_in_vector(b, i, value)] > 1) return 1;
    if (b->cols_values_count[board_get_index_in_vector(b, j, value)] > 1) return 1;
    return 0;
}
int board_is_valid_option(Board* board, int i , int j, int value) {
    /*
     * check if values is a valid option in the cell i,j
     * don't change board.
     */
    int result = 1,
        cell_value = board_get(board, i, j);
    board_set(board, i, j, value);
    if (board_is_error(board, i ,j)) result = 0;
    board_set(board, i, j, cell_value);
    return result;
}
int board_has_errors(Board* b) {
    int i, j, N = board_get_N(b);
    for (i = 1; i<=N; i++)
        for (j = 1; j<=N; j++) {
            if (board_is_error(b, i, j)) return 1;
        }
    return 0;
}
int board_print(Board* board, int mark_errors) {
    /*
     * return 0 if failed (malloc fail)
     * 1 - if succeed
     */
    char* seperator = generate_seperator(board);
    int i , j, N = board_get_N(board),
            n = board->n, m = board->m;
    if (!seperator) return 0;
    printf("%s", seperator);
    for (i = 1 ; i <= N; i++) {
        printf("\n|");
        for (j = 1 ; j<=N; j++) {
            print_cell(board, i, j, mark_errors);
            if (j%n == 0)
                printf("|");

        }
        if (i%m == 0) printf("\n%s", seperator);
    }
    printf("\n");
    free(seperator);
    return 1;
}
int board_get_N(Board* b)
{
    return (b->m)*(b->n);
}
int board_is_full(Board* b){
    return b->num_of_empty == 0;
}
int board_get_col_count(Board* b, int idx, int val){
    return b->cols_values_count[board_get_index_in_vector(b, idx, val)];
}
int board_get_row_count(Board* b, int idx, int val){
    return b->rows_values_count[board_get_index_in_vector(b, idx, val)];
}
int board_get_block_count(Board* b, int idx, int val){
    return b->blocks_values_count[board_get_index_in_vector(b, idx, val)];
}
