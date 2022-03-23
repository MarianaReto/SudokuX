#include "files.h"
#include "backtracking.h"
#include "R13/helper.h"
#include "R13/hiddensingle.h"
#include "R13/intersectionremoval.h"
#include "R13/xwing.h"
#include "R13/nakedpairs.h"

/**
 * @authors Mariana Reto
 */

void test_save_files() {
    int size = 9;

    int sud1[MAX36][MAX36] = {
            {0, 0, 0, 2, 1, 3, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 7, 0, 5},
            {0, 3, 0, 0, 0, 0, 6, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0},
            {7, 0, 0, 0, 0, 8, 0, 0, 0},
            {0, 1, 0, 0, 0, 9, 0, 0, 0},
            {9, 0, 1, 0, 0, 4, 5, 0, 8},
            {0, 0, 2, 0, 6, 5, 0, 0, 4},
            {0, 0, 0, 8, 0, 0, 0, 0, 0},
    };

    int sud2[MAX36][MAX36] = {
            {8, 0, 0, 0, 7, 0, 0, 0, 4},
            {1, 6, 0, 0, 3, 0, 0, 0, 0},
            {2, 0, 0, 0, 1, 0, 3, 0, 5},
            {0, 9, 0, 0, 2, 0, 0, 4, 1},
            {0, 0, 8, 0, 0, 0, 2, 0, 0},
            {6, 0, 0, 0, 0, 0, 7, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 6, 0},
            {0, 5, 0, 0, 4, 0, 0, 0, 0},
            {0, 0, 3, 0, 0, 0, 0, 0, 0}
    };

    SUDOKU sudokustruct1 = {0, NULL, NULL};
    SUDOKU sudokustruct2 = {0, NULL, NULL};

    construct_sudoku(&sudokustruct1, sud1, size);
    construct_sudoku(&sudokustruct2, sud2, size);

    print_sudoku(sudokustruct1);
    print_sudoku(sudokustruct2);
    JOGO j = {0, NULL};
    create_array_sudokus(&j, 1);
    insert_sudoku_into_jogo_list(&j, &sudokustruct1);
    //insert_sudoku_into_jogo_list(&j, &sudokustruct2);

    save_game_to_text(j);
    //save_to_bin(sudokustruct1);
}

void test_read_files() {
    JOGO jogoSudoku = {0, NULL};
    JOGO jogoSudoku2 = {0, NULL};
    JOGO jogoSudoku3 = {0, NULL};


    //read_board_from_text(&jogoSudoku);
    //read_board_from_text(&jogoSudoku);
    //save_game_to_text(jogoSudoku);


    read_game_from_text(&jogoSudoku2);
    save_game_to_bin(jogoSudoku3);
    read_game_from_bin(&jogoSudoku3);

    int nBoards = jogoSudoku2.nBoards;
    printf("\nNumber of BoardS: %d\n", nBoards);
}

void test_generate() {
    SUDOKU board = {0, NULL, NULL};
    generate_random(&board, 25);
    printf("\n\n\t\t TEST RANDOM GENERATE:\n");
    print_sudoku(board);
}

void test_solver() {
    int sud1[MAX36][MAX36] = {
            {3, 0, 6, 5, 0, 8, 4, 0, 0},
            {5, 2, 0, 0, 0, 0, 0, 0, 0},
            {0, 8, 7, 0, 0, 0, 0, 3, 1},
            {0, 0, 3, 0, 1, 0, 0, 8, 0},
            {9, 0, 0, 8, 6, 3, 0, 0, 5},
            {0, 5, 0, 0, 9, 0, 6, 0, 0},
            {1, 3, 0, 0, 0, 0, 2, 5, 0},
            {0, 0, 0, 0, 0, 0, 0, 7, 4},
            {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    int sud2[MAX36][MAX36] = {
            {0, 0, 0, 2, 1, 3, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 7, 0, 5},
            {0, 3, 0, 0, 0, 0, 6, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0},
            {7, 0, 0, 0, 0, 8, 0, 0, 0},
            {0, 1, 0, 0, 0, 9, 0, 0, 0},
            {9, 0, 1, 0, 0, 4, 5, 0, 8},
            {0, 0, 2, 0, 6, 5, 0, 0, 4},
            {0, 0, 0, 8, 0, 0, 0, 0, 0},
    };

    int sud3[MAX36][MAX36] = {
            {8, 0, 0, 0, 7, 0, 0, 0, 4},
            {1, 6, 0, 0, 3, 0, 0, 0, 0},
            {2, 0, 0, 0, 1, 0, 3, 0, 5},
            {0, 9, 0, 0, 2, 0, 0, 4, 1},
            {0, 0, 8, 0, 0, 0, 2, 0, 0},
            {6, 0, 0, 0, 0, 0, 7, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 6, 0},
            {0, 5, 0, 0, 4, 0, 0, 0, 0},
            {0, 0, 3, 0, 0, 0, 0, 0, 0}
    };

    int sudPairs1[MAX36][MAX36] = {
            {4, 0, 0, 0, 0, 0, 9, 3, 8},
            {0, 3, 2, 0, 9, 4, 1, 0, 0},
            {0, 9, 5, 3, 0, 0, 2, 4, 0},
            {3, 7, 0, 6, 0, 9, 0, 0, 4},
            {5, 2, 9, 0, 0, 1, 6, 7, 3},
            {6, 0, 4, 7, 0, 3, 0, 9, 0},
            {9, 5, 7, 0, 0, 8, 3, 0, 0},
            {0, 0, 3, 9, 0, 0, 4, 0, 0},
            {2, 4, 0, 0, 3, 0, 7, 0, 9},
    };

    int sudPairs2[MAX36][MAX36] = {
            {0, 9, 6, 4, 0, 2, 8, 3, 5},
            {0, 3, 8, 9, 5, 0, 4, 2, 6},
            {5, 4, 2, 6, 8, 3, 0, 0, 9},
            {4, 2, 9, 5, 3, 6, 0, 0, 8},
            {8, 1, 3, 2, 9, 0, 5, 6, 4},
            {6, 7, 5, 0, 4, 8, 3, 9, 2},
            {2, 5, 4, 0, 0, 9, 6, 8, 3},
            {9, 8, 7, 3, 6, 5, 2, 4, 0},
            {3, 6, 1, 8, 2, 4, 9, 5, 0},
    };


    // SOLVERS
    int size = 9;
    SUDOKU sudokuBackTrack = {0, NULL, NULL};
    SUDOKU sudokuHiddenSingle = {0, NULL, NULL};
    SUDOKU sudokuIntersectionRemoval = {0, NULL, NULL};
    SUDOKU sudokuNakedPairs = {0, NULL, NULL};


    construct_sudoku(&sudokuBackTrack, sud3, size);
    print_sudoku(sudokuBackTrack);
    printf("\n\n\t\t TEST BACKTRACKING SOLVER");
    main_solver(&sudokuBackTrack);

    /*
    construct_sudoku(&sudokuHiddenSingle, sudPairs2, size);
    print_sudoku(sudokuHiddenSingle);
    printf("\n\n\t\t TEST NON BACKTRACKING SOLVER");
    main_hidden_single(&sudokuHiddenSingle);
    print_sudoku(sudokuHiddenSingle);


    main_intersection_removal(&sudokuIntersectionRemoval);
    print_sudoku(sudokuIntersectionRemoval);


    construct_sudoku(&sudokuNakedPairs, sudPairs1, size);
    print_sudoku(sudokuNakedPairs);
    naked_pairs(sudokuNakedPairs);
    print_sudoku(sudokuNakedPairs);



    construct_sudoku(&sudokuIntersectionRemoval, sudPairs2, size);
    print_sudoku(sudokuIntersectionRemoval);
    main_xwing(&sudokuIntersectionRemoval);
    print_sudoku(sudokuIntersectionRemoval);*/
}

int main() {
    //test_save_files();
    //test_read_files();
    //test_generate();
    test_solver();
}