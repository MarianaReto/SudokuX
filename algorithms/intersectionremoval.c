#include "intersectionremoval.h"

/**
 * main function to solve sudoku using the intersection removal methods
 * @param sudoku board
 */
void main_intersection_removal(SUDOKU *sudoku) {
    calculate_hip(sudoku);
    //print_hip(*sudoku);
    intersection_removal_solver(sudoku);
    //print_hip(*sudoku);
}

/**
 * solves board using intersection removal method
 * @param sudoku board
 */
void intersection_removal_solver(SUDOKU *sudoku) {
    int size = sudoku->size;
    int size_square = (int) sqrt(size);
    ELEMENTO *current = sudoku->firstElemento, *currentRow = current;

    for (int row = 0; row < size; row = row + size_square) {
        for (int col = 0; col < size; col = col + size_square) {
            pair_in_box_aligned_row(sudoku, row, col);
            pair_in_box_aligned_col(sudoku, row, col);
            //vai para a coluna seguinte
            current = current->e;
        }
        //vai para a linha seguinte
        currentRow = currentRow->s;
        current = currentRow;
    }
}

/**
 * Does methods according to the intersection removal method
 * A Pair in a box - if they are aligned on a row, n can be removed from the rest of the row.
 * A Pair on a row - if they are all in the same box, n can be removed from the rest of the box.
 * @param sudoku board
 * @param row current row
 * @param col current col
 */
void pair_in_box_aligned_row(SUDOKU *sudoku, int row, int col) {
    int size = sudoku->size;
    int size_square = (int) sqrt(size);
    int row_corner = (row / size_square) * size_square;
    int col_corner = (col / size_square) * size_square;

    ELEMENTO *current = sudoku->firstElemento;

    //vai para a posição inicial do quadrado
    for (int r = 0; r < row_corner; r++) {
        current = current->s;
    }
    for (int c = 0; c < col_corner; c++) {
        current = current->e;
    }

    //vamos iterar as colunas da linha com este nextSudoku
    ELEMENTO *next = current, *currentRow = current;

    //iteração das linhas do quadrado
    for (int r = 0; r < size_square; r++) {
        //iteração das colunas do quadrado
        for (int colcurrent = 0; colcurrent < size_square; colcurrent++) {
            if (next != NULL) {
                for (int colnext = colcurrent + 1; colnext < size_square; colnext++) {
                    //is pair
                    if (current->val == next->val && current != next) {
                        update_hip_row_outside_square(sudoku, col_corner, size_square, row, current->val);
                        update_hip_inside_square(sudoku, row_corner, col_corner, size_square, current->val);
                    }

                    next = next->e;
                }
                //vai para a coluna seguinte
                current = current->e;
                next = current;
            } else
                break;
        }
        currentRow = currentRow->s;
        current = currentRow;
    }

}

/**
 * Does methods according to the intersection removal method
 * A Pair in a box - if they are aligned on a column, n can be removed from the rest of the column.
 * A Pair on a column - if they are all in the same box, n can be removed from the rest of the box.
 * @param sudoku board
 * @param row current row
 * @param col current col
 */
void pair_in_box_aligned_col(SUDOKU *sudoku, int row, int col) {
    int size = sudoku->size;
    int size_square = (int) sqrt(size);
    int row_corner = (row / size_square) * size_square;
    int col_corner = (col / size_square) * size_square;

    ELEMENTO *current = sudoku->firstElemento;

    //vai para a posição inicial do quadrado
    for (int r = 0; r < row_corner; ++r) {
        current = current->s;
    }
    for (int c = 0; c < col_corner; c++) {
        current = current->e;
    }

    //vamos iterar as linhas da coluna com este nextSudoku
    ELEMENTO *next = current, *currentCol = current;

    //iteração das colunas do quadrado
    for (int c = 0; c < size_square; c++) {
        //iteração das linhas do quadrado
        for (int rowcurrent = 0; rowcurrent < size_square; rowcurrent++) {
            if (next != NULL) {
                for (int rownext = rowcurrent + 1; rownext < size_square; rownext++) {

                    //is pair
                    if (current->val == next->val && current != next) {
                        update_hip_col_outside_square(sudoku, row_corner, size_square, col, current->val);
                        update_hip_inside_square(sudoku, row_corner, col_corner, size_square, current->val);
                    }

                    next = next->s;
                }
                //vai para a linha seguinte
                current = current->s;
                next = current->s;
            } else
                break;
        }
        currentCol = currentCol->e;
        current = currentCol;
    }

}

/**
 * pointing pairs
 * @param sudoku board
 * @param col_corner col where square starts
 * @param size_square size of square
 * @param row current row
 * @param value value to be deleted from candidate numbers according to pointing pairs
 */
void update_hip_row_outside_square(SUDOKU *sudoku, int col_corner, int size_square, int row, int value) {
    int size = sudoku->size;
    ELEMENTO *current = sudoku->firstElemento;

    //goes to intended row
    for (int r = 0; r < row; r++) {
        current = current->s;
    }

    for (int col = 0; col < size; col++) {
        if (col < col_corner || col >= col_corner + size_square) {
            delete_hip(current, value);
        }
        current = current->e;
    }
}

/**
 * pointing pairs
 * @param sudoku board
 * @param row_corner row where square starts
 * @param size_square size of square
 * @param col current col
 * @param value value to be deleted from candidate numbers according to pointing pairs
 */
void update_hip_col_outside_square(SUDOKU *sudoku, int row_corner, int size_square, int col, int value) {
    int size = sudoku->size;
    ELEMENTO *current = sudoku->firstElemento;

    //goes to intended row
    for (int r = 0; r < col; r++) {
        current = current->e;
    }

    for (int row = 0; row < size; row++) {
        if (row < row_corner || row >= row_corner + size_square) {
            delete_hip(current, value);
        }
        current = current->s;
    }
}

/**
 * Box/Line Reduction
 * @param sudoku board
 * @param row_corner row where square starts
 * @param col_corner col where square starts
 * @param size_square size of square
 * @param value value to be deleted from candidate numbers according to box/line reduction
 */
void update_hip_inside_square(SUDOKU *sudoku, int row_corner, int col_corner, int size_square, int value) {
    ELEMENTO *current = sudoku->firstElemento;

    //vai para a posição inicial do quadrado
    for (int row = 0; row < row_corner; row++) {
        current = current->s;
    }
    for (int col = 0; col < col_corner; col++) {
        current = current->e;
    }

    ELEMENTO *currentRow = current;

    for (int row = 0; row < size_square; row++) {
        for (int col = 0; col < size_square; col++) {
            delete_hip(current, value);
            //vai para a coluna seguinte
            current = current->e;
        }
        //vai para a linha seguinte
        currentRow = currentRow->s;
        current = currentRow;
    }
}