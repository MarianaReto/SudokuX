#include <stdlib.h>
#include "backtracking.h"
#include "files.h"
#include "R13/helper.h"

/**
 * main solver for backtracking method
 * @param sudoku
 * @return 1 if solved succesfully
 */
int main_solver(SUDOKU *sudoku) {
    return fill_sud(sudoku, 0, 0);
}


/**
 * manually create a sudoku board
 */
void input_sud(SUDOKU *sudoku, int size) {
    int sud[MAX36][MAX36] = {{0}};

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            scanf(" %d", &sud[i][j]);

    construct_sudoku(sudoku, sud, size);
}

/**
 * backtracking method for solving sudoku
 * @param sudoku
 * @param row current sudoku row
 * @param col current sudoku col
 * @return 1 if insertion possible
 */
int fill_sud(SUDOKU *sudoku, int row, int col) {
    int size = sudoku->size;
    int next_row = (col == size - 1) ? row + 1 : row;
    int next_col = (col + 1) % (size);

    if (row == size) {
        printf("\n\nSolution backtracking:\n");
        print_sudoku(*sudoku);
        save_to_text_sol(*sudoku);
        return 1;
    }

    ELEMENTO *current = sudoku->firstElemento;
    for (int r = 0; r < row; r++) {
        current = current->s;
    }
    for (int c = 0; c < col; c++) {
        current = current->e;
    }

    if (current->val != 0)
        return fill_sud(sudoku, next_row, next_col);

    for (int value = 1; value <= size; value++) {
        current->val = value;

        if (is_legal(*sudoku, row, col, value) && fill_sud(sudoku, next_row, next_col))
            return 1;

        current->val = 0;
    }

    return 0;
}

/**
 * checks if inserting a value is possible in the selected row and col, according to the SudokuX's rules
 * @param sudoku board
 * @param row current row
 * @param col current col
 * @param val value we want to insert
 * @return 1 if insertion is possible
 */
int is_legal(SUDOKU sudoku, int row, int col, int val) {
    int isLegal = (is_row_ok(sudoku, row, col, val) &&
                   is_col_ok(sudoku, row, col, val) &&
                   is_sqr_ok(sudoku, row, col, val));

    if (row == col)
        isLegal = (isLegal && is_diag_main_ok(sudoku, row, val));

    int size = sudoku.size;

    if ((row == col - size) && (col = size - row))
        isLegal = (isLegal && is_diag_sec_ok(sudoku, row, col, val));

    return isLegal;
}

/**
 * checks to see if we can insert value in row
 * @param sudoku board
 * @param row current row
 * @param col current col
 * @param val value we want to insert
 * @return 1 if insertion is possible
 */
int is_row_ok(SUDOKU sudoku, int row, int col, int val) {
    ELEMENTO *currentRow = sudoku.firstElemento;
    //goes to the row we're about to check
    for (int r = 0; r < row; r++) {
        currentRow = currentRow->s;
    }

    int size = sudoku.size;

    ELEMENTO *current = currentRow;
    for (int i = 0; i < size; i++) {
        if (i != col && current->val == val)
            return 0;
        //advances to the nextSudoku item in the row
        current = current->e;
    }
    return 1;
}

/**
 * checks to see if we can insert value in col
 * @param sudoku board
 * @param row current row
 * @param col current col
 * @param val value we want to insert
 * @return 1 if insertion is possible
 */
int is_col_ok(SUDOKU sudoku, int row, int col, int val) {
    ELEMENTO *currentCol = sudoku.firstElemento;
    //finds the column
    for (int c = 0; c < col; ++c) {
        currentCol = currentCol->e;
    }

    int size = sudoku.size;

    ELEMENTO *current = currentCol;
    for (int i = 0; i < size; i++) {
        if (i != row && current->val == val)
            return 0;
        //goes to nextSudoku position
        current = current->s;
    }

    return 1;
}

/**
 * checks to see if we can insert value in square
 * @param sudoku board
 * @param row current row
 * @param col current col
 * @param val value we want to insert
 * @return 1 if insertion is possible
 */
int is_sqr_ok(SUDOKU sudoku, int row, int col, int val) {

    int size = sudoku.size;

    int size_square = sqrt(size);

    int row_corner = (row / size_square) * size_square;
    int col_corner = (col / size_square) * size_square;

    ELEMENTO *current = sudoku.firstElemento;
    for (int r = 0; r < row_corner; r++) {
        current = current->s;
    }
    for (int c = 0; c < col_corner; ++c) {
        current = current->e;
    }

    ELEMENTO *currentRow = current;

    for (int r = row_corner; r < (row_corner + size_square); r++) {
        for (int c = col_corner; c < (col_corner + size_square); c++) {
            if ((r != row || c != col) && current->val == val)
                return 0;

            current = current->e;
        }
        currentRow = currentRow->s;
        current = currentRow;
    }

    return 1;
}

/**
 * checks to see if we can insert value in main diagonal
 * @param sudoku board
 * @param row current row
 * @param val value we want to insert
 * @return 1 if insertion is possible
 */
int is_diag_main_ok(SUDOKU sudoku, int row, int val) {
    ELEMENTO *current = sudoku.firstElemento;
    int size = sudoku.size;
    for (int i = 0; i < size; i++) {
        if (i != row && current->val == val)
            return 0;
        current = current->se;

    }

    return 1;
}

/**
 * checks to see if we can insert value in secondary diagonal
 * @param sudoku board
 * @param row current row
 * @param col current col
 * @param val value we want to insert
 * @return 1 if insertion is possible
 */
int is_diag_sec_ok(SUDOKU sudoku, int row, int col, int val) {
    int size = sudoku.size;
    ELEMENTO *current = sudoku.firstElemento;
    //get to ponta + nordeste do sudoku
    while (current->e != NULL) {
        current = current->e;
    }

    int r = 0, c = size - 1;
    while (current->so != NULL) {
        if ((r != row || c != col) && current->val == val)
            return 0;
        current = current->so;
        r++;
        c--;
    }
    return 1;
}

/**
 * randomizes a number between the 2 possible numbers
 * @param val_min smallest number that can be randomized
 * @param val_max biggest number that can be randomized
 * @return number (number >= val_min && number <= val_max)
 */
int uniform(int val_min, int val_max) {
    return val_min + rand() % (val_max - val_min + 1);
}

/**
 * fills a random sudoku with 20 numbers
 * @param sudoku board
 * @param size size of sudoku board (9, 16, 25 or 36)
 */
void generate_random(SUDOKU *sudoku, int size) {
    int nNumbers = 20;
    int emptySudokuArray[MAX36][MAX36] = {{0}};

    srand(time(NULL));

    construct_sudoku(sudoku, emptySudokuArray, size);

    ELEMENTO *first = sudoku->firstElemento;
    ELEMENTO *current;

    int count = 0;
    while (count != nNumbers) {
        current = first;

        //picks a random cell
        int row = uniform(0, size - 1);
        int col = uniform(0, size - 1);;

        //goes to the chosen row
        for (int r = 0; r < row; r++) {
            current = current->s;
        }

        //goes to the chosen column
        for (int c = 0; c < col; c++) {
            current = current->e;
        }

        //if the cell is empty, attempts to put a number inside it
        if (current->val == 0) {

            int isValid = 0;
            while (!isValid) {
                int value = uniform(1, size);
                current->val = value;
                isValid = is_legal(*sudoku, row, col, value);
            }

            count++;
        }
    }
}

/**
 * checks to see if sudoku board is already filled
 * @param sudoku board
 * @return 1 if the board is complete
 */
int noZeros(SUDOKU sudoku) {
    ELEMENTO *currentRow = sudoku.firstElemento;
    ELEMENTO *currentCel = currentRow;
    while (currentRow != NULL) {
        while (currentCel != NULL) {
            if (currentCel->val == 0)
                return 0;
            currentCel = currentCel->e;
        }
        currentRow = currentRow->s;
        currentCel = currentRow;
    }
    return 1;
}