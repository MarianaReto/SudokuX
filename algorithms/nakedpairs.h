//
// Created by Asus on 2020-01-11.
//

#ifndef LP_AED_FASE1_NAKEDPAIRS_H
#define LP_AED_FASE1_NAKEDPAIRS_H

#include "../backtracking.h"

int naked_pairs(SUDOKU sudoku);

int naked_pairs_row(SUDOKU sudoku, int row, int myCol, int val1, int val2);

int naked_pairs_col(SUDOKU sudoku, int row, int col, int val1, int val2);

int *naked_pairs_sqr(SUDOKU sudoku, int row, int col, int myRow, int myCol, int val1, int val2, int found[]);

int *naked_pairs_diag_main(SUDOKU sudoku, int row, int col, int myRow, int myCol, int val1, int val2, int found[]);

int *naked_pairs_diag_sec(SUDOKU sudoku, int row, int col, int myRow, int myCol, int val1, int val2, int found[]);

void naked_pairs_replace(SUDOKU *sudoku, int row1, int col1, int row2, int col2, int val1, int val2);

int exists_pairs(SUDOKU sudoku, int pairs[4]);

#endif //LP_AED_FASE1_NAKEDPAIRS_H
