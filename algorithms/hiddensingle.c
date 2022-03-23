#include "hiddensingle.h"

/**
 * main function to solve sudoku using the hidden single method
 * @param sudoku board
 */
void main_hidden_single(SUDOKU *sudoku) {
    calculate_hip(sudoku);
    fill_cells_with_one_hip(sudoku);
    hidden_single_solver(sudoku);
}

/**
 * solves sudoku using the hidden single method
 * @param sudoku board
 */
void hidden_single_solver(SUDOKU *sudoku) {
    int size = sudoku->size;

    ELEMENTO *current = sudoku->firstElemento;
    ELEMENTO *currentRow = current;

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            HIP *candidato = current->firstHip;
            //itera todos os candidatos para aquela cell
            for (int i = 0; i < current->numHip; i++) {
                if (is_hidden_single(*sudoku, row, col, candidato->val)) {
                    current->val = candidato->val;
                    update_hip(sudoku, row, col, candidato->val);
                }
                candidato = candidato->nextHip;
            }
            current = current->e;
        }
        currentRow = currentRow->s;
        current = currentRow;
    }
}

/**
 * determines if the number is a hidden single
 * @param sudoku board
 * @param row current row
 * @param col current col
 * @param num number we're trying to determine if is a hidden single
 * @return 1 if the number is a hidden single
 */
int is_hidden_single(SUDOKU sudoku, int row, int col, int num) {
    int size = sudoku.size;

    //diagonal principal
    if (row == col && hidden_single_diag_main(sudoku, num))
        return 1;

    //diagonal secundaria
    if ((row == col - size) && (col == size - row) && hidden_single_diag_sec(sudoku, num))
        return 1;

    if (hidden_single_row(sudoku, row, num) || hidden_single_col(sudoku, row, num) ||
        hidden_single_sqr(sudoku, row, col, num))
        return 1;

    return 0;
}

/**
 * determines if the number is a hidden single
 * @param sudoku board
 * @param row current row
 * @param num candidate number that could be a hidden single
 * @return 1 if the candidate only appears once in that row
 */
int hidden_single_row(SUDOKU sudoku, int row, int num) {
    int size = sudoku.size;
    ELEMENTO *current = sudoku.firstElemento;

    //gets to current sudoku row
    for (int r = 0; r < row; r++) {
        current = current->s;
    }

    //itera as colunas
    for (int col = 0; col < size; col++) {

        HIP *candidato = current->firstHip;
        //itera todos os candidatos para aquela cell
        for (int i = 0; i < current->numHip; i++) {
            if (candidato->val == num)
                return 0;
            candidato = candidato->nextHip;
        }

        current = current->e;
    }

    return 1;
}

/**
 * determines if the number is a hidden single
 * @param sudoku board
 * @param col current col
 * @param num candidate number that could be a hidden single
 * @return 1 if the candidate only appears once in that col
 */
int hidden_single_col(SUDOKU sudoku, int col, int num) {
    int size = sudoku.size;
    ELEMENTO *current = sudoku.firstElemento;

    //gets to current sudoku col
    for (int r = 0; r < col; r++) {
        current = current->e;
    }

    //itera as linhas
    for (int row = 0; row < size; row++) {

        HIP *candidato = current->firstHip;
        //itera todos os candidatos para aquela cell
        for (int i = 0; i < current->numHip; i++) {
            if (candidato->val == num)
                return 0;
            candidato = candidato->nextHip;
        }

        current = current->s;
    }

    return 1;
}

/**
 * determines if the number is a hidden single
 * @param sudoku board
 * @param row current row
 * @param col current col
 * @param num candidate number that could be a hidden single
 * @return 1 if the candidate only appears once in that col
 */
int hidden_single_sqr(SUDOKU sudoku, int row, int col, int num) {
    int size = sudoku.size;
    int size_square = (int) sqrt(size);
    int row_corner = (row / size_square) * size_square;
    int col_corner = (col / size_square) * size_square;

    ELEMENTO *current = sudoku.firstElemento;

    //vai para a posição inicial do quadrado
    for (int r = 0; r < row_corner; ++r) {
        current = current->s;
    }
    for (int c = 0; c < col_corner; c++) {
        current = current->e;
    }

    ELEMENTO *currentRow = current;

    //iteração do quadrado
    for (int r = row_corner; r < (row_corner + size_square); r++) {
        for (int c = col_corner; c < (col_corner + size_square); c++) {
            HIP *candidato = current->firstHip;
            //itera todos os candidatos para aquela cell
            for (int i = 0; i < current->numHip; i++) {
                if (candidato->val == num)
                    return 0;
                candidato = candidato->nextHip;
            }
            //vai para a coluna seguinte
            current = current->e;
        }
        //vai para a linha seguinte
        currentRow = currentRow->s;
        current = currentRow;
    }

    return 1;
}

/**
 * determines if the number is a hidden single
 * @param sudoku board
 * @param num candidate number that could be a hidden single
 * @return 1 if the candidate only appears once in the main diagonal
 */
int hidden_single_diag_main(SUDOKU sudoku, int num) {
    int size = sudoku.size;

    ELEMENTO *current = sudoku.firstElemento;
    for (int i = 0; i < size; i++) {
        HIP *candidato = current->firstHip;
        //itera todos os candidatos para aquela cell
        for (int j = 0; j < current->numHip; j++) {
            if (candidato->val == num)
                return 0;
            candidato = candidato->nextHip;
        }
        //nextSudoku pos
        current = current->se;
    }
    return 1;
}

/**
 * determines if the number is a hidden single
 * @param sudoku board
 * @param num candidate number that could be a hidden single
 * @return 1 if the candidate only appears once in the secondary diagonal
 */
int hidden_single_diag_sec(SUDOKU sudoku, int num) {
    int size = sudoku.size;
    ELEMENTO *current = sudoku.firstElemento;

    //get to ponta + nordeste do sudoku
    while (current->e != NULL) {
        current = current->e;
    }

    for (int i = 0; i < size; i++) {

        HIP *candidato = current->firstHip;
        //itera todos os candidatos para aquela cell
        for (int j = 0; j < current->numHip; j++) {
            if (candidato->val == num)
                return 0;
            candidato = candidato->nextHip;
        }

        //nextSudoku pos
        current = current->so;
    }


    return 1;
}