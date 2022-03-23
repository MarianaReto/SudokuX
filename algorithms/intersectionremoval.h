#ifndef LP_AED_FASE1_INTERSECTIONREMOVAL_H
#define LP_AED_FASE1_INTERSECTIONREMOVAL_H

#include "../backtracking.h"
#include "helper.h"

void main_intersection_removal(SUDOKU *sudoku);

void intersection_removal_solver(SUDOKU *sudoku);


void pair_in_box_aligned_row(SUDOKU *sudoku, int row, int col);


void pair_in_box_aligned_col(SUDOKU *sudoku, int row, int col);


void update_hip_row_outside_square(SUDOKU *sudoku, int col_corner, int size_square, int row, int value);


void update_hip_col_outside_square(SUDOKU *sudoku, int row_corner, int size_square, int col, int value);


void update_hip_inside_square(SUDOKU *sudoku, int row_corner, int col_corner, int size_square, int value);

#endif //LP_AED_FASE1_INTERSECTIONREMOVAL_H
