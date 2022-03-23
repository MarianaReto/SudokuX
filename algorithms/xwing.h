#ifndef LP_AED_FASE1_XWING_H
#define LP_AED_FASE1_XWING_H

#include "../backtracking.h"
#include "helper.h"

void main_xwing(SUDOKU *sudoku);

void xwing_solver(SUDOKU *sudoku);

int times_candidate_appears_row(SUDOKU sudoku, int row, int candidate);

int makes_rectangle(SUDOKU sudoku, int row1, int row2, int candidate);

int has_HIP(ELEMENTO elemento, int candidate);

int find_col_first_hip(SUDOKU sudoku, int row, int candidate);

int find_col_last_hip(SUDOKU sudoku, int row, int candidate);

void remove_hip_row_outside_xwing(SUDOKU *sudoku, int row, int col1, int col2, int candidate);

void remove_hip_col_outside_xwing(SUDOKU *sudoku, int col, int row1, int row2, int candidate);


#endif //LP_AED_FASE1_XWING_H
