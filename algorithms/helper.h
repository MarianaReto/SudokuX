#ifndef LP_AED_FASE1_HELPER_H
#define LP_AED_FASE1_HELPER_H

#include "../backtracking.h"


void print_sudoku(SUDOKU sudoku);

void construct_sudoku(SUDOKU *sudoku, int sudokuMatrix[][MAX36], int size);

void main_helper(SUDOKU *sudoku);

void calculate_hip(SUDOKU *sudoku);

int alone_number(SUDOKU sudoku);

int find_one(SUDOKU sudoku, int row, int col, int startingPoint);

int solver_tactics(SUDOKU sudoku);

void update_hip(SUDOKU *sudoku, int row, int col, int value);

void update_hip_row(SUDOKU *sudoku, int row, int value);

void update_hip_column(SUDOKU *sudoku, int col, int value);

void update_hip_sqr(SUDOKU *sudoku, int row, int col, int value);

void update_hip_diag_main(SUDOKU *sudoku, int row, int col, int value);

void update_hip_diag_sec(SUDOKU *sudoku, int row, int col, int value);

void print_hip(SUDOKU sudoku);

void fill_cells_with_one_hip(SUDOKU *sudoku);

void delete_hip(ELEMENTO *current, int value);

void insert_sudoku_into_jogo_list(JOGO *j, SUDOKU *sudoku);

void create_array_sudokus(JOGO *j,int size);

void remove_sudoku_from_jogo_list(JOGO *j);

#endif //LP_AED_FASE1_HELPER_H