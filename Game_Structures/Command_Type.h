/*
 * Created by Owner on 8/11/2019.
*/


#ifndef PROJECTFILES_COMMAND_TYPE_H
#define PROJECTFILES_COMMAND_TYPE_H
/*
 * Add new type:
 *      1. add to enum
 *      2. add to command_type_enum_array
 *      3. add to command_type_string_array
 *      4. increase COMMAND_TYPE_KINDS by 1
 */

/*enum definition*/
typedef enum {cmd_type_invalid_len, cmd_type_invalid_command_name, cmd_type_solve,
              cmd_type_edit, cmd_type_mark_errors, cmd_type_print_board, cmd_type_set, cmd_type_validate,
              cmd_type_guess, cmd_type_generate, cmd_type_undo, cmd_type_redo, cmd_type_save,
              cmd_type_hint, cmd_type_guess_hint, cmd_type_num_sols, cmd_type_autofill,
              cmd_type_reset, cmd_type_exit} Command_Type;

/*Global arrays and values*/
#define COMMAND_TYPE_KINDS 19
#define START_INDEX_OF_NON_INVALID_COMMANDS 2

extern Command_Type command_type_enum_array[];
extern char *command_type_string_array[];
extern int command_type_number_of_params[];
extern int command_type_has_path[];

/*Functions*/
int command_type_get_index(Command_Type commandType);
char* command_type_to_string(Command_Type commandType);
Command_Type command_type_string_to_command_type(char* string);

#endif /*PROJECTFILES_COMMAND_TYPE_H*/
