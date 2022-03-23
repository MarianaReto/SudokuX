#ifndef LP_AED_FASE1_HIDDENSINGLE_H
#define LP_AED_FASE1_HIDDENSINGLE_H

#include "../backtracking.h"
#include "helper.h"

void main_hidden_single(SUDOKU *sudoku);

void hidden_single_solver(SUDOKU *sudoku);

int hidden_single_row(SUDOKU sudoku, int row, int num);

int hidden_single_col(SUDOKU sudoku, int col, int num);

int hidden_single_sqr(SUDOKU sudoku, int row, int col, int num);

int hidden_single_diag_main(SUDOKU sudoku, int num);

int hidden_single_diag_sec(SUDOKU sudoku, int num);

int is_hidden_single(SUDOKU sudoku, int row, int col, int num);

#endif //LP_AED_FASE1_HIDDENSINGLE_H
