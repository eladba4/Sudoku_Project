#ifndef PROJECTFILES_PRINT_MESSAGES_H
#define PROJECTFILES_PRINT_MESSAGES_H
void error_print_param_range(int param_index, int lower_bound, int upper_bound);
void error_print_invalid_state();
void error_print_num_of_params(int correct_num_of_params);
void error_print_board_erroneuos();
void error_print_cell_fixed();
void error_print_cell_not_empty();
void error_print_grb();
void error_print_board_unsolvable();
void error_print_save();
void error_print_correct_state_init();
void error_print_correct_state_solve();
void error_print_correct_state_edit();
void error_print_empty_redo();
void error_print_empty_undo();
void error_print_memory();
void error_print_exit();
void error_print_len();
void error_print_cmd_name();
void error_print_mark_errors_range();
#endif
