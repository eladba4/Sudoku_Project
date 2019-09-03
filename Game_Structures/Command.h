/*
 * Command.h
 *
 *  Created on: Aug 7, 2019
 *      Author: Owner
 */

#ifndef COMMAND_H_
#define COMMAND_H_


#define MAX_STRING_PARAMS_IN_COMMAND 1
#define MAX_DOUBLE_PARAMS_IN_COMMAND 1
#define MAX_INT_PARAMS_IN_COMMAND 3
#define MAX_PARAMS_IN_COMMAND 5

typedef struct {
    Command_Type type;
    int count_int;
    int count_str;
    int count_double;
    double prob;
    /*
     * if prob == -1 didn't get any double value.
     */
    int* params;
    char* path;
    char* param_order;
    /*
     * len = MAX_PARAMS_IN_COMMAND
     * 'i' - int, 'd' = double , 's' = string
     */
} Command;

Command* command_generate();
void command_free(Command* cmd);
int check_number_of_params(Command* command);

#endif /* COMMAND_H_ */
