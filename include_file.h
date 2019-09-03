/*
 * include_file.c
 *
 *  Created on: Aug 7, 2019
 *      Author: Owner
 */

#ifndef INCLUDE_FILE_
#define INCLUDE_FILE_

#define _GRB_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "Game_Structures/Game_Structures_include_file.h"
#include "Generate/Board_Generate.h"
#include "Solvers/Solvers_include_file.h"
#include "User_Input/User_Input_include_file.h"
#include "Read_Write_File/Read_Write_File_include_file.h"
#include "Commands_Implementation/Commands_Implementation_include_file.h"
void main_aux_run_game(Game* game);

#ifdef _TEST_
#include "Tests/Tests_include_file.h"
#endif


#endif

