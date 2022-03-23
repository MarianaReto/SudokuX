#include "xwing.h"

/**
 * main function to solve xwing method
 * @param sudoku board
 */
void main_xwing(SUDOKU *sudoku) {
    calculate_hip(sudoku);
    print_hip(*sudoku);
    xwing_solver(sudoku);
    print_hip(*sudoku);
}

/**
 * xwing method solver
 * @param sudoku board
 */
void xwing_solver(SUDOKU *sudoku) {
    int size = sudoku->size;
    for (int row1 = 0; row1 < size; row1++) {
        for (int row2 = 0; row2 < size; row2++) {
            if (row1 != row2) {
                for (int num = 0; num < size; num++) {
                    if (times_candidate_appears_row(*sudoku, row1, num) == 2 &&
                        times_candidate_appears_row(*sudoku, row2, num) == 2) {
                        if (makes_rectangle(*sudoku, row1, row2, num)) {
                            //candidates deleted, proceed to nextSudoku row where xwing is seen
                            break;
                        }
                    }
                }
            }
        }
    }

}

/**
 * checks how many times the selected candidate appears in that row
 * @param sudoku board
 * @param row selected row
 * @param candidate candidate value we're testing
 * @return number of times candidate appears
 */
int times_candidate_appears_row(SUDOKU sudoku, int row, int candidate) {
    ELEMENTO *current = sudoku.firstElemento;

    for (int r = 0; r < row; r++) {
        current = current->s;
    }

    //number of times candidate appears
    int times = 0;
    for (int c = 0; c < sudoku.size; c++) {
        //candidate invalid
        if (current->val == candidate)
            return 0;

        HIP *candidato = current->firstHip;
        //itera todos os candidatos para aquela cell
        for (int i = 0; i < current->numHip; i++) {
            if (candidato->val == candidate) {
                times++;
                break;
            }
            candidato = candidato->nextHip;
        }
    }

    return times;
}

/**
 * checks whether or not the 4 candidates make a rectangle (according to xwing method) and, if so, removes candidate from other rows and columns
 * @param sudoku board
 * @param row1 row where first 2 candidates were found
 * @param row2 row where last 2 candidates where found
 * @param candidate candidate we're testing
 * @return 1 if makes a rectangle
 */
int makes_rectangle(SUDOKU sudoku, int row1, int row2, int candidate) {
    int col1 = 0, col2 = 0, col3 = 0, col4 = 0;
    /*
     * row 1 =  col1 | col2
     *          -----------
     * row 2 =  col3 | col4
     */
    col1 = find_col_first_hip(sudoku, row1, candidate);
    col2 = find_col_last_hip(sudoku, row1, candidate);
    col3 = find_col_first_hip(sudoku, row2, candidate);
    col4 = find_col_last_hip(sudoku, row2, candidate);

    if (col1 == col3 && col2 == col4 && col1 != col2) {
        //remove candidate from other rows
        remove_hip_row_outside_xwing(&sudoku, row1, col1, col2, candidate);
        remove_hip_row_outside_xwing(&sudoku, row2, col3, col4, candidate);

        //remove candidate from other cols
        remove_hip_col_outside_xwing(&sudoku, col1, row1, row2, candidate);
        remove_hip_col_outside_xwing(&sudoku, col2, row1, row2, candidate);
        return 1;

    }

    return 0;
}

/**
 * finds the column where the candidate first appears (it's only called after we check that the candidate appears only twice in that row)
 * @param sudoku board
 * @param row row we're testing
 * @param candidate candidate number we're looking for
 * @return col where candidate first appears, -1 if somehow there was a bug
 */
int find_col_first_hip(SUDOKU sudoku, int row, int candidate) {
    ELEMENTO *current = sudoku.firstElemento;
    for (int r = 0; r < row; r++) {
        current = current->s;
    }

    for (int c = 0; c < sudoku.size; c++) {
        if (has_HIP(*current, candidate))
            return c;
        current = current->e;
    }

    return -1;
}

/**
 * finds the column where the candidate last appears (it's only called after we check that the candidate appears only twice in that row)
 * @param sudoku board
 * @param row row we're testing
 * @param candidate candidate number we're looking for
 * @return col where candidate last appears, -1 if somehow there was a bug
 */
int find_col_last_hip(SUDOKU sudoku, int row, int candidate) {
    ELEMENTO *current = sudoku.firstElemento;
    //vai para a linha
    for (int r = 0; r < row; r++) {
        current = current->s;
    }
    //vai para a ultima posiçao da linha
    for (int c = 0; c < sudoku.size; c++) {
        current = current->e;
    }

    for (int c = 0; c < sudoku.size; c++) {
        if (has_HIP(*current, candidate))
            return c;
        current = current->o;
    }

    return -1;
}

/**
 * check to see if a certain cell has a particular candidate number
 * @param elemento sudoku cell
 * @param candidate candidate number
 * @return 1 if it has the number, 0 if not
 */
int has_HIP(ELEMENTO elemento, int candidate) {
    HIP *candidato = elemento.firstHip;
    //itera todos os candidatos para aquela cell
    for (int i = 0; i < elemento.numHip; i++) {
        if (candidato->val == candidate)
            return 1;
        candidato = candidato->nextHip;
    }
    return 0;
}

/**
 * removes all occurrences of candidate outside that row according to xwing
 * @param sudoku board
 * @param row current row
 * @param col1 column 1 that belongs to xwing
 * @param col2 column 2 that belongs to xwing
 * @param candidate candidate number
 */
void remove_hip_row_outside_xwing(SUDOKU *sudoku, int row, int col1, int col2, int candidate) {
    int size = sudoku->size;
    ELEMENTO *current = sudoku->firstElemento;

    //goes to intended row
    for (int r = 0; r < row; r++) {
        current = current->s;
    }

    for (int col = 0; col < size; col++) {
        if (col != col1 || col != col2) {
            delete_hip(current, candidate);
        }
        current = current->e;
    }
}

/**
 * removes all occurrences of candidate outside that col according to xwing
 * @param sudoku board
 * @param col current col
 * @param row1 row 1 that belongs to xwing
 * @param row2 row 2 that belongs to xwing
 * @param candidate candidate number
 */
void remove_hip_col_outside_xwing(SUDOKU *sudoku, int col, int row1, int row2, int candidate) {
    int size = sudoku->size;
    ELEMENTO *current = sudoku->firstElemento;

    //goes to intended row
    for (int r = 0; r < col; r++) {
        current = current->e;
    }

    for (int row = 0; row < size; row++) {
        if (row != row1 || row != row2) {
            delete_hip(current, candidate);
        }
        current = current->s;
    }
}
