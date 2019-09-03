/*
 * Created by Owner on 8/8/2019.
 */

#ifndef USER_INPUT_INCLUDE_FILE_H_
#define USER_INPUT_INCLUDE_FILE_H_

#define MAX_CHARS_IN_COMMAND 256
#define MAX_PARTS_IN_COMMAND 6


Command* parser_get_command_from_user(int *EOF_found);
int parser_is_white_space(char c);


#endif
