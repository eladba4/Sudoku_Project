/*
 * Created by Owner on 8/8/2019.
 */
#include "../include_file.h"

typedef enum{p_int, p_double, p_str, p_null} Param_Type;

void parser_free_command_parts(char **command_parts);
char** parser_generate_command_parts();
int parser_get_command_parts(char** command_parts, int *valid_len, int *EOF_found);
void parser_clear_input_until_line_sep(int* EOF_found);
void parser_get_parts_from_line(char *line, char **command_parts);
void parser_get_line(char* line, int* valid_len, int* EOF_found);
char** parser_generate_command_parts();
void parser_free_command_parts(char **command_parts);

/**General Parsing Auxiliary Functions **/
int parser_is_digit(char c) {
    if ((int)'0' <= (int)c && (int)'9' >= (int)c) return 1;
    return 0;
}
int parser_is_white_space(char c) {
    if (c == '\t' || c == ' ') return 1;
    return 0;
}
int parser_is_small_alphabet(char c){
    return (((int)c >= (int)('a')) && ((int)(c) <= (int)('z')));
}

/*Command Parts to Command*/
Param_Type parser_get_param_type(char* param){
    int found_point = 0, i = 0;
    char current_char = param[i];
    Param_Type type = p_int;
    if (current_char == '\0') return p_null;
    if (current_char == '-') i++;
    while (current_char!='\0') {
        if (!parser_is_digit(current_char)) {
            if (current_char == '.' && !found_point) found_point = 1;
            else {type = p_str; break;}
        }
        i++; current_char = param[i];
    }
    if (type == p_int && found_point) type = p_double;
    return type;
}

void parser_get_param_str(Command *command, char *param) {
    int i;
    command->count_str++;
    if (command->count_str > MAX_STRING_PARAMS_IN_COMMAND) {return;}
    for (i = 0; param[i]!='\0'; i++) command->path[i] = param[i];
    return;
}
void parser_get_param_int(Command *command, char *param) {
    command->count_int++;
    if (command->count_int > MAX_INT_PARAMS_IN_COMMAND) {return;}
    sscanf(param, "%d", &(command->params[command->count_int-1]));
    return;
}
void parser_get_param_double(Command *command, char *param) {
    command->count_double++;
    if (command->count_double > MAX_DOUBLE_PARAMS_IN_COMMAND) {return;}
    sscanf(param, "%lf", &(command->prob));
    return;
}


void parser_get_next_param_from_parts(char **command_parts, Command *command, int *found_param, int i) {
    Param_Type type = parser_get_param_type(command_parts[i]);
    if ((type != p_null) && (i == 1) &&
    (command->type == cmd_type_save ||
    command->type == cmd_type_solve ||
    command->type == cmd_type_edit)) {
        parser_get_param_str(command, command_parts[i]);
        command->param_order[0] = 's';
        return;
    }
    if (type == p_null) *found_param = 0;
    if (type == p_str)  {
        parser_get_param_str(command, command_parts[i]);
        command->param_order[i-1] = 's';
    }
    if (type == p_int) {
        parser_get_param_int(command, command_parts[i]);
        command->param_order[i-1] = 'i';
    }
    if (type == p_double) {
        parser_get_param_double(command, command_parts[i]);
        command->param_order[i-1] = 'd';
    }
}
void parser_get_params_from_parts(char **command_parts, Command *command) {
    int found_param = 1, i = 1;
    while (found_param && i < MAX_PARAMS_IN_COMMAND+1){
        parser_get_next_param_from_parts(command_parts, command, &found_param, i);
        i++;
    }
}
Command_Type parser_get_command_type_from_parts(char** command_parts, int *valid_len){
    if (!*valid_len) return cmd_type_invalid_len;
    return command_type_string_to_command_type(command_parts[0]);
}
Command* parser_get_command_from_user(int *EOF_found){
    /*
     * get input form user and put it's values into a Command struct.
     * Return:
     *     NULL - if memory error.
     *     pointer to Command  - else.
     */
    char** command_parts;
    Command* command;
    int valid_len;
    command_parts = parser_generate_command_parts();
    if (!command_parts) return NULL;
    command = command_generate();
    if (!command) return NULL;
    if (!parser_get_command_parts(command_parts, &valid_len, EOF_found)) return NULL;
    command->type = parser_get_command_type_from_parts(command_parts, &valid_len);
    parser_get_params_from_parts(command_parts, command);
    parser_free_command_parts(command_parts);
    return command;

}


void set_to_exit(char *string) {
    string[0] = 'e'; string[1] = 'x';
    string[2] = 'i'; string[3] = 't';
    string[4] = '\0';
}

/*get Command Parts*/
int parser_get_command_parts(char** command_parts, int *valid_len, int *EOF_found){
    /*
     * get command parts from user input.
     * assume that:
     *      1. len(command_parts) = MAX_PARTS_IN_COMMAND
     *      2. for all i : len(command_parts[i]) = MAX_CHARS_IN_COMMAND+1
     *
     * return 0 if malloc failed.
     */

    char *line = malloc((MAX_CHARS_IN_COMMAND+1)* sizeof(char));
    *valid_len = 0;
    if (!line) return 0;
    line[0] = '\0';
    command_parts[0][0] = '\0';
    while (command_parts[0][0] == '\0' && !*EOF_found){
        parser_get_line(line, valid_len, EOF_found);
        if (!*valid_len) {free(line); return 1;}
        parser_get_parts_from_line(line, command_parts);
    }
    if (command_parts[0][0] == '\0') set_to_exit(command_parts[0]);
    free(line);
    return 1;
    }
void parser_clear_input_until_line_sep(int* EOF_found) {
    char c;
    c = getchar();
    while (c!='\n' && c!=EOF) c =  getchar();
    if (c == EOF) *EOF_found = 1;
}
void parser_get_parts_from_line(char *line, char **command_parts) {
    char c;
    int line_index = 0, part_to_write = 0, part_index = 0, i;
    for (i = 0 ; i<MAX_PARTS_IN_COMMAND; i++) command_parts[i][0] = '\0';

    for (line_index = 0 ; line_index<MAX_CHARS_IN_COMMAND
                          && part_to_write<MAX_PARTS_IN_COMMAND; line_index++) {
        c = line[line_index];
        if (c == '\0') {
            command_parts[part_to_write][part_index] = '\0';
            break;
        }
        if (parser_is_white_space(c)) {
            if (part_index>0) {
                command_parts[part_to_write][part_index] = '\0';
                part_index = 0; part_to_write++;
            }
            continue;
        }
        /*now c is not a white space or '\0' - should write to command*/
        command_parts[part_to_write][part_index] = c;
        part_index++;
    }
}
void parser_get_line(char* line, int* valid_len, int* EOF_found) {
    /*
     * line should be at least MAX_CHARS_IN_COMMAND + 1 = 257 length
     * fill line with input chars until '\n' is reached.
     * if has more than MAX_CHARS_IN_COMMAND set valid_len to 0
     * else valid_len set to 0
     */
    char c;
    int i;
    for (i = 0; i < MAX_CHARS_IN_COMMAND+1; i++) {
        c = getchar();
        line[i] = c;
        if (c == EOF) {
            *EOF_found = 1;
            *valid_len = 1;
            line[i] = '\0';
            break;
        }
        if (c == '\n') {
            *valid_len = 1;
            line[i] = '\0';
            break;
        }
    }
    if (!*valid_len ) parser_clear_input_until_line_sep(EOF_found);
}
char** parser_generate_command_parts() {
    /*
     * return command_parts.
     * if NULL returned malloc failed.
     */
    char **command_parts = malloc(MAX_PARTS_IN_COMMAND*sizeof(char*));
    int i;
    if (!command_parts) return NULL;
    for (i = 0 ; i<MAX_PARTS_IN_COMMAND; i++) {
        command_parts[i] = malloc((MAX_CHARS_IN_COMMAND+1) * sizeof(char));
        if (!command_parts[i]) return NULL;
    }
    return command_parts;
}
void parser_free_command_parts(char **command_parts) {
    int i;
    for (i = 0 ; i < MAX_PARTS_IN_COMMAND; i++)
        free(command_parts[i]);
    free(command_parts);
}
