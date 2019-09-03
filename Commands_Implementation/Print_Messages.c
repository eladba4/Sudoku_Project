#include "../include_file.h"
#define TAB_ "       "

void error_print_param_range(int param_index, int lower_bound, int upper_bound){
    printf("Error: parameter %d is not in range!\n", param_index);
    printf("%sexpected number from %d to %d\n", TAB_, lower_bound, upper_bound);
}
void error_print_invalid_state(){
    printf("Error: invalid command for the current game state!\n");
}
void error_print_num_of_params(int correct_num_of_params){
    printf("Error: Command has incorrect number of parameters!\n");
    if (correct_num_of_params == -1) printf("       expect 0 or 1 parameters\n");
    else printf("%sexpected %d parameters\n", TAB_, correct_num_of_params);
}

void error_print_board_erroneuos(){
    printf("Error: board is erroneous!\n");
}
void error_print_cell_fixed(){
    printf("Error: cell if fixed!\n");
}
void error_print_cell_not_empty(){
    printf("Error: cell already contains value!\n");
}
void error_print_grb(){
    printf("GUROBI ERROR OCCURRED! Exit...\n");
}

void error_print_board_unsolvable(){
    printf("Error: Board is unsolvable!\n");
}

void error_print_save(){
    printf("Error: Failed to save the board!\n");
}

void error_print_correct_state_init()
{
	printf("%sCommand can run in Init state\n", TAB_);
}
void error_print_correct_state_solve()
{
	printf("%sCommand can run in Solve state\n", TAB_);
}
void error_print_correct_state_edit()
{
	printf("%sCommand can run in Edit state\n", TAB_);
}

void error_print_empty_undo()
{
    printf("Error: nothing to undo!\n");
}

void error_print_empty_redo()
{
    printf("Error: nothing to redo!\n");
}

void error_print_memory(){
    printf("MEMORY ERROR OCCURRED! Exit...\n");
}

void error_print_exit(){
    printf("Exit game, BYE!\n");
}
void error_print_len(){
    printf("Error: Command length should be at most 256 characters!\n");
}
void error_print_cmd_name(){
    printf("Error: Invalid command name!\n");
}

void error_print_mark_errors_range(){
    printf("Error: parameter 1 is invalid!\n");
    printf("%sexpect 0 or 1\n", TAB_);
}
