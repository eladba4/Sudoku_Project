/*
 * Created by Owner on 8/11/2019.
*/


#include "../include_file.h"

/*Command Type Helper List - if add new command type should add it to both list in the same index*/
Command_Type command_type_enum_array[] =
        {cmd_type_invalid_len, cmd_type_invalid_command_name, cmd_type_solve,
         cmd_type_edit, cmd_type_mark_errors, cmd_type_print_board, cmd_type_set,
         cmd_type_validate, cmd_type_guess, cmd_type_generate, cmd_type_undo,
         cmd_type_redo, cmd_type_save, cmd_type_hint, cmd_type_guess_hint,
         cmd_type_num_sols, cmd_type_autofill, cmd_type_reset, cmd_type_exit};

char *command_type_string_array[] =
        {"invalid_len", "invalid_command_name", "solve", "edit",  "mark_errors", "print_board",
		"set", "validate", "guess", "generate", "undo", "redo", "save", "hint", "guess_hint",
		"num_solutions", "autofill", "reset", "exit"};
int command_type_number_of_params[] = {0,0,0,0,1,0,3,0,1,2,0,0,0,2,2,0,0,0,0};
int command_type_has_path[] = {0,0,1,-1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0};
/* 0,1 : has path or not,
 * -1 : path is optional */

/* convert command name to its index, if array does not contain the name return 0*/
int command_type_get_index(Command_Type commandType){
	return (int)commandType;
}
char* command_type_to_string(Command_Type commandType) {
    return command_type_string_array[command_type_get_index(commandType)];
}
Command_Type command_type_string_to_command_type(char* string) {
    /*
     * return commmand type from string,
     * if string is no command type return cmd_type_invalid_command_name.
     */
    Command_Type result = cmd_type_invalid_command_name;
    int i;
    for (i = START_INDEX_OF_NON_INVALID_COMMANDS; i < COMMAND_TYPE_KINDS; i++) {
        if (strcmp(string, command_type_string_array[i]) == 0) {
            result = command_type_enum_array[i];
            return result;
        }
    }
    return result;
}
