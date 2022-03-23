#ifndef LP_AED_FASE1_BACKTRACKING_H
#define LP_AED_FASE1_BACKTRACKING_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX36 36

typedef struct hipotese {
    int val;
    struct hipotese *nextHip;
} HIP;

typedef struct elemento {
    int val;
    struct elemento *n, *no, *ne, *s, *so, *se, *o, *e;
    int numHip;
    HIP *firstHip;
} ELEMENTO;

typedef struct sudoku {
    int size;
    ELEMENTO *firstElemento;
    struct sudoku *nextSudoku;
} SUDOKU;

typedef struct jogo {
    int nBoards;
    SUDOKU *firstSudoku;
} JOGO;


void input_sud(SUDOKU *sudoku, int size);

int fill_sud(SUDOKU *sudoku, int row, int col);

int is_legal(SUDOKU sudoku, int row, int col, int val);

int is_row_ok(SUDOKU sudoku, int row, int col, int val);

int is_col_ok(SUDOKU sudoku, int row, int col, int val);

int is_sqr_ok(SUDOKU sudoku, int row, int col, int val);

int is_diag_main_ok(SUDOKU sudoku, int row, int val);

int is_diag_sec_ok(SUDOKU sudoku, int row, int col, int val);

int main_solver(SUDOKU *sudoku);

void generate_random(SUDOKU *sudoku, int size);

int noZeros(SUDOKU sudoku);

int uniform(int val_min, int val_max);

#endif //LP_AED_FASE1_BACKTRACKING_H
