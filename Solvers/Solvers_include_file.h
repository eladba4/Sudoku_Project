/*
 * Created by Owner on 8/8/2019.
 */

#ifndef SOLVER_INPUT_INCLUDE_FILE_H_
#define SOLVER_INPUT_INCLUDE_FILE_H_
#include "../include_file.h"

int solvers_autofill(Game* game);
int solvers_recurrent_autofill(Board* board);
int solvers_get_number_of_solutions(Board* board);
#include "LP/LP_include_file.h"

#endif
