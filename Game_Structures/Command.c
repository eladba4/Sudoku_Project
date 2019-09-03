/*
 * Command.c
 *
 *  Created on: Aug 7, 2019
 *      Author: Owner
 */
#include "../include_file.h"

Command* command_generate() {
    Command* result = (Command*)malloc(sizeof(Command));
    if (!result) return NULL;
    result->count_str= 0; result->count_int = 0;
    result->prob = -1; result->count_double = 0;
    result->params = calloc(sizeof(int) , MAX_PARAMS_IN_COMMAND);
    if (!result->params) return NULL;
    result->path = calloc(sizeof(char), MAX_CHARS_IN_COMMAND+1);
    if (!result->params) return NULL;
    result->param_order = calloc(sizeof(char), MAX_PARAMS_IN_COMMAND);
    if (!result->param_order) return NULL;
    return result;
}
void command_free(Command* command){
    if (!command) return;
    free(command->params);
    free(command->path);
    free(command->param_order);
    free(command);
}

int check_number_of_params(Command* command) {
    /*
     * Check if command got the right number of parameters.
     * Ignore pararmeter types.
     */
    int index = command_type_get_index(command->type);
    int total_params = command->count_double + command->count_int + command->count_str;
    int correctNumOfParams;
    if (command_type_has_path[index] < 0) {
        if (total_params <= command->count_str) return 1;
        error_print_num_of_params(-1);
        return 0;
    }
    correctNumOfParams = command_type_has_path[index] +
                             command_type_number_of_params[index];
    if (total_params == correctNumOfParams) return 1;
    error_print_num_of_params(correctNumOfParams);
    return 0;
}

