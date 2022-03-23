#include "nakedpairs.h"
#include "helper.h"

/**
 * attempts to solve board using naked pairs method
 * @param sudoku board
 * @return 1 once done
 */
int naked_pairs(SUDOKU sudoku) {
    int size = sudoku.size;

    ELEMENTO *currentRow = sudoku.firstElemento;
    ELEMENTO *current = currentRow;

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (current->numHip == 2) {

                int val1 = find_one(sudoku, r, c, size + 1);
                int val2 = find_one(sudoku, r, c, val1 + 1);

                // check line
                int col = naked_pairs_row(sudoku, r, c, val1, val2);
                if (col != -1) {
                    naked_pairs_replace(&sudoku, r, c, r, col, val1, val2);
                    return 1;
                }

                // check cols
                int row = naked_pairs_col(sudoku, r, c, val1, val2);
                if (row != -1) {
                    naked_pairs_replace(&sudoku, r, c, row, c, val1, val2);
                    return 1;
                }

                // check square
                int sqrt[2] = {-1, -1};
                naked_pairs_sqr(sudoku, r, c, r, c, val1, val2, sqrt);
                if (sqrt[0] != -1 && sqrt[1] != -1) {
                    naked_pairs_replace(&sudoku, r, c, sqrt[0], sqrt[1], val1, val2);
                    return 1;
                }

                // check main diag
                int mainDiag[2] = {-1, -1};
                naked_pairs_diag_main(sudoku, r, c, r, c, val1, val2, mainDiag);
                if (mainDiag[0] != -1 && mainDiag[1] != -1) {
                    naked_pairs_replace(&sudoku, r, c, mainDiag[0], mainDiag[1], val1, val2);
                    return 1;
                }

                // check sec diag
                int secDiag[2] = {-1, -1};
                naked_pairs_diag_sec(sudoku, r, c, r, c, val1, val2, secDiag);
                if (secDiag[0] != -1 && secDiag[1] != -1) {
                    naked_pairs_replace(&sudoku, r, c, secDiag[0], secDiag[1], val1, val2);
                    return 1;
                }
            }
            current = current->e;
        }
        currentRow = currentRow->s;
        current = currentRow;
    }

    return 0;
}

/**
 * attempts the naked pairs method on a row
 * @param sudoku board
 * @param row current row
 * @param myCol col the candidate is in
 * @param val1 candidate #1
 * @param val2 candidate #2
 * @return -1 if not possible
 */
int naked_pairs_row(SUDOKU sudoku, int row, int myCol, int val1, int val2) {
    int size = sudoku.size;
    ELEMENTO *current = sudoku.firstElemento;

    //gets to current sudoku row
    for (int r = 0; r < row; r++) {
        current = current->s;
    }

    //itera as colunas
    for (int col = 0; col < size; col++) {
        if (current->numHip == 2 && col != myCol) {
            HIP *currenthip = current->firstHip;
            HIP *nexthip = currenthip->nextHip;

            if (currenthip->val == val1 && nexthip->val == val2)
                return col;
        }

        current = current->e;
    }

    return -1;
}

/**
 * attempts the naked pairs method on a col
 * @param sudoku board
 * @param myRow row the candidate is in
 * @param col current col
 * @param val1 candidate #1
 * @param val2 candidate #2
 * @return -1 if not possible
 */
int naked_pairs_col(SUDOKU sudoku, int myRow, int col, int val1, int val2) {
    int size = sudoku.size;
    ELEMENTO *current = sudoku.firstElemento;

    //gets to current sudoku col
    for (int r = 0; r < col; r++) {
        current = current->e;
    }

    //itera as linhas
    for (int row = 0; row < size; row++) {
        if (current->numHip == 2 && row != myRow) {
            HIP *currenthip = current->firstHip;
            HIP *nexthip = currenthip->nextHip;

            if (currenthip->val == val1 && nexthip->val == val2)
                return row;

        }
    }

    return -1;
}

/**
 * attempts the naked pairs method on a square
 * @param sudoku board
 * @param row current row
 * @param col current col
 * @param myRow row the candidate is in
 * @param myCol col the candidate is in
 * @param val1 candidate #1
 * @param val2 candidate #2
 * @param found naked pair found
 * @return NULL if not possible
 */
int *naked_pairs_sqr(SUDOKU sudoku, int row, int col, int myRow, int myCol, int val1, int val2, int found[]) {
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


    for (int r = row_corner; r < (row_corner + size_square); r++) {
        for (int c = col_corner; c < (col_corner + size_square); c++) {
            if (myRow != r && myCol != c) {
                if (current->numHip == 2) {
                    HIP *currenthip = current->firstHip;
                    HIP *nexthip = currenthip->nextHip;
                    if (currenthip->val == val1 && nexthip->val == val2) {
                        found[0] = r;
                        found[1] = c;
                        return found;
                    }
                }
            }
            //vai para a coluna seguinte
            current = current->e;
        }
        //vai para a linha seguinte
        currentRow = currentRow->s;
        current = currentRow;
    }

    return NULL;
}

/**
 * attempts the naked pairs method on a diagonal
 * @param sudoku board
 * @param row current row
 * @param col current col
 * @param myRow row the candidate is in
 * @param myCol col the candidate is in
 * @param val1 candidate #1
 * @param val2 candidate #2
 * @param found naked pair found
 * @return NULL if not possible
 */
int *naked_pairs_diag_main(SUDOKU sudoku, int row, int col, int myRow, int myCol, int val1, int val2, int found[]) {
    int size = sudoku.size;
    if (row == col) {
        ELEMENTO *current = sudoku.firstElemento;
        for (int i = 0; i < size; i++) {
            if (i != myCol && i != myRow) {
                if (current->numHip == 2) {
                    HIP *currenthip = current->firstHip;
                    HIP *nexthip = currenthip->nextHip;
                    if (currenthip->val == val1 && nexthip->val == val2) {
                        found[0] = i;
                        found[1] = i;
                        return found;
                    }
                }
            }
            //nextSudoku pos
            current = current->se;
        }
    }
    return NULL;
}

/**
 * attempts the naked pairs method on a diagonal
 * @param sudoku board
 * @param row current row
 * @param col current col
 * @param myRow row the candidate is in
 * @param myCol col the candidate is in
 * @param val1 candidate #1
 * @param val2 candidate #2
 * @param found naked pair found
 * @return NULL if not possible
 */
int *naked_pairs_diag_sec(SUDOKU sudoku, int row, int col, int myRow, int myCol, int val1, int val2, int found[]) {
    int size = sudoku.size;
    if ((row == col - size) && (col == size - row)) {
        ELEMENTO *current = sudoku.firstElemento;

        //get to ponta + nordeste do sudoku
        while (current->e != NULL) {
            current = current->e;
        }

        for (int i = 0; i < size; i++) {

            int j = size - 1;
            if (i != myRow && j != myCol) {
                if (current->numHip == 2) {
                    HIP *currenthip = current->firstHip;
                    HIP *nexthip = currenthip->nextHip;
                    if (currenthip->val == val1 && nexthip->val == val2) {
                        found[0] = i;
                        found[1] = i;
                        return found;
                    }
                }
            }
            j--;
            //nextSudoku pos
            current = current->so;
        }
    }

    return NULL;
}

/**
 * replaces the naked pairs according to the method
 * @param sudoku board
 * @param row1 row of pair 1
 * @param col1 col of pair 1
 * @param row2 row of pair 2
 * @param col2 col of pair 2
 * @param val1 value of pair 1
 * @param val2 value of pair 2
 */
void naked_pairs_replace(SUDOKU *sudoku, int row1, int col1, int row2, int col2, int val1, int val2) {
    ELEMENTO *primeiro = sudoku->firstElemento;
    ELEMENTO *segundo = primeiro;

    //vai para a posiçao do 1º elemento
    for (int row = 0; row < row1; row++) {
        primeiro = primeiro->s;
    }
    for (int col = 0; col < col1; col++) {
        primeiro = primeiro->e;
    }

    //vai para a posiçao do 2º elemento
    for (int row = 0; row < row2; row++) {
        segundo = segundo->s;
    }
    for (int col = 0; col < col2; col++) {
        segundo = segundo->e;
    }

    //atribui os valores aos elementos
    primeiro->val = val2;
    segundo->val = val1;

    calculate_hip(sudoku);
    /*
    update_hip(hip, row1, col1, val1, size);
    update_hip(hip, row1, col1, val2, size);
    update_hip(hip, row2, col2, val1, size);
    update_hip(hip, row2, col2, val2, size);
     */
}

/**
 * checks for the existence of naked pairs
 * @param sudoku board
 * @param pairs array of naked pairs
 * @return 1 if pairs exists
 */
int exists_pairs(SUDOKU sudoku, int pairs[4]) {
    int size = sudoku.size;

    ELEMENTO *currentRow = sudoku.firstElemento;
    ELEMENTO *current = currentRow;

    for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
            if (current->numHip == 2) {
                int v1 = find_one(sudoku, r, c, 1);
                int v2 = find_one(sudoku, r, c, v1 + 1);

                pairs[0] = r;
                pairs[1] = c;

                int col = naked_pairs_row(sudoku, r, c, v1, v2);
                if (col != -1) {
                    pairs[2] = r;
                    pairs[3] = col;
                    return 1;
                }

                int row = naked_pairs_col(sudoku, r, c, v1, v2);
                if (row != -1) {
                    pairs[2] = row;
                    pairs[3] = c;
                    return 1;
                }

                // check square
                int sqrt[2] = {-1, -1};
                naked_pairs_sqr(sudoku, r, c, r, c, v1, v2, sqrt);
                if (sqrt[0] != -1 && sqrt[1] != -1) {
                    pairs[2] = sqrt[0];
                    pairs[3] = sqrt[1];
                    return 1;
                }

                // check main diag
                int mainDiag[2] = {-1, -1};
                naked_pairs_diag_main(sudoku, r, c, r, c, v1, v2, mainDiag);
                if (mainDiag[0] != -1 && mainDiag[1] != -1) {
                    pairs[2] = mainDiag[0];
                    pairs[3] = mainDiag[1];
                    return 1;
                }

                // check sec diag
                int secDiag[2] = {-1, -1};
                naked_pairs_diag_sec(sudoku, r, c, r, c, v1, v2, secDiag);
                if (secDiag[0] != -1 && secDiag[1] != -1) {
                    pairs[2] = secDiag[0];
                    pairs[3] = secDiag[1];
                    return 1;
                }
            }
            current = current->e;
        }
        currentRow = currentRow->s;
        current = currentRow;
    }

    return 0;
}