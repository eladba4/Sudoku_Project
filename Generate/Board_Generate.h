
#ifndef PROJECTFILES_BOARD_GENERATE_H
#define PROJECTFILES_BOARD_GENERATE_H

typedef struct{
    int i;
    int j;
} Cell;

#ifdef _GRB_
int board_puzzle(Game* game, int x, int y, int *grb_error);
#endif /*GRB*/




#endif /*PROJECTFILES_BOARD_GENERATE_H*/
