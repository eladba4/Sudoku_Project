CC = gcc

COMMANDS_IMPLEMENTATION = $(COMMANDS) Print_Messages.o general_command.o
COMMANDS = autofill.o edit.o exit.o generate.o guess.o guess_hint.o hint.o mark_errors.o num_solutions.o print_board.o save.o set.o solve.o undo_redo_reset.o validate.o

GAME_STRUCTURES = Board.o Command.o Command_Type.o Game.o Stack.o $(DOUBLY_LINKED_LIST)
DOUBLY_LINKED_LIST = Doubly_Linked_List.o
READ_WRITE_FILE = load_file.o save_file.o
USER_INPUT = Parser.o
GENERATE = Board_Generate.o

VARIABLES = Variables.o Generic_Board.o vCell.o
LP = $(VARIABLES) ILP_Solver.o grb_helper.o LP_guess.o
SOLVERS = $(LP) Autofill_Solver.o Exhaustive_Backtracking_Solver.o


OBJS = main.o main_aux.o $(GAME_STRUCTURES) $(READ_WRITE_FILE) $(SOLVERS) $(USER_INPUT) $(GENERATE) $(COMMANDS_IMPLEMENTATION)
EXEC = sudoku-console
GUROBI_COMP = -I/usr/local/lib/gurobi563/include
GUROBI_LIB = -L/usr/local/lib/gurobi563/lib -lgurobi56
COMP_FLAG = -ansi -O3 -Wall -Wextra -Werror -pedantic-errors $(GUROBI_COMP)

all: $(OBJS)
	$(CC) $(OBJS) $(GUROBI_LIB) -o sudoku-console

main.o: main.c include_file.h
	$(CC) $(COMP_FLAG) -c $*.c
main_aux.o: main_aux.c include_file.h
	$(CC) $(COMP_FLAG) -c $*.c

Print_Messages.o: Commands_Implementation/Print_Messages.c Commands_Implementation/Print_Messages.h Commands_Implementation/Commands_Implementation_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/$*.c
general_command.o: Commands_Implementation/general_command.c Commands_Implementation/Commands_Implementation_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/$*.c

autofill.o: Commands_Implementation/Commands/autofill.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
edit.o: Commands_Implementation/Commands/edit.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
exit.o: Commands_Implementation/Commands/exit.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
generate.o: Commands_Implementation/Commands/generate.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
guess.o: Commands_Implementation/Commands/guess.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
guess_hint.o: Commands_Implementation/Commands/guess_hint.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
hint.o: Commands_Implementation/Commands/hint.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
mark_errors.o: Commands_Implementation/Commands/mark_errors.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
num_solutions.o: Commands_Implementation/Commands/num_solutions.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
print_board.o: Commands_Implementation/Commands/print_board.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
save.o: Commands_Implementation/Commands/save.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
set.o: Commands_Implementation/Commands/set.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
solve.o: Commands_Implementation/Commands/solve.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
undo_redo_reset.o: Commands_Implementation/Commands/undo_redo_reset.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c
validate.o: Commands_Implementation/Commands/validate.c Commands_Implementation/Commands/Commands_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Commands_Implementation/Commands/$*.c





Board.o: Game_Structures/Board.c Game_Structures/Board.h Game_Structures/Game_Structures_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Game_Structures/$*.c
Command.o: Game_Structures/Command.c Game_Structures/Command.h Game_Structures/Game_Structures_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Game_Structures/$*.c
Command_Type.o: Game_Structures/Command_Type.c Game_Structures/Command_Type.h Game_Structures/Game_Structures_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Game_Structures/$*.c
Doubly_Linked_List.o: Game_Structures/Doubly_Linked_List/Doubly_Linked_List.c Game_Structures/Doubly_Linked_List/Doubly_Linked_List.h Game_Structures/Game_Structures_include_file.h include_file.h	
	$(CC) $(COMP_FLAG) -c Game_Structures/Doubly_Linked_List/$*.c
Game.o: Game_Structures/Game.c Game_Structures/Game.h Game_Structures/Game_Structures_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Game_Structures/$*.c
Stack.o: Game_Structures/Stack.c Game_Structures/Stack.h Game_Structures/Game_Structures_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Game_Structures/$*.c

load_file.o: Read_Write_File/load_file.c Read_Write_File/Read_Write_File_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Read_Write_File/$*.c
save_file.o: Read_Write_File/save_file.c Read_Write_File/Read_Write_File_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Read_Write_File/$*.c

Variables.o: Solvers/LP/Variables/Variables.c Solvers/LP/Variables/Variables.h include_file.h
	$(CC) $(COMP_FLAG) -c Solvers/LP/Variables/$*.c
Generic_Board.o: Solvers/LP/Variables/Generic_Board.c Solvers/LP/Variables/Generic_Board.h include_file.h
	$(CC) $(COMP_FLAG) -c Solvers/LP/Variables/$*.c
vCell.o: Solvers/LP/Variables/vCell.c Solvers/LP/Variables/vCell.h include_file.h
	$(CC) $(COMP_FLAG) -c Solvers/LP/Variables/$*.c


ILP_Solver.o: Solvers/LP/ILP_Solver.c Solvers/LP/LP_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Solvers/LP/$*.c
LP_guess.o: Solvers/LP/LP_guess.c Solvers/LP/LP_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Solvers/LP/$*.c
grb_helper.o: Solvers/LP/grb_helper.c Solvers/LP/LP_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Solvers/LP/$*.c

Autofill_Solver.o: Solvers/Autofill_Solver.c Solvers/Solvers_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Solvers/$*.c
Exhaustive_Backtracking_Solver.o: Solvers/Autofill_Solver.c Solvers/Solvers_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c Solvers/$*.c


Parser.o: User_Input/Parser.c User_Input/User_Input_include_file.h include_file.h
	$(CC) $(COMP_FLAG) -c User_Input/$*.c




Board_Generate.o: Generate/Board_Generate.c Generate/Board_Generate.h include_file.h
	$(CC) $(COMP_FLAG) -c Generate/$*.c







clean:
	rm -f $(OBJS) $(EXEC)
