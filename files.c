#include "files.h"
#include "R13/helper.h"

/* GAME */
/**
 * saves sudoku game to txt
 * @param j game
 */
void save_game_to_text(JOGO j) {
    FILE *fp = fopen(TEXTFILE, "w");

    if (fp == NULL)
        perror("Save Game To Text");

    int nSudokus = j.nBoards;
    fprintf(fp, "nSudokus: %d\n", nSudokus);

    SUDOKU *currentSudoku = j.firstSudoku;
    while (currentSudoku != NULL) {

        int size = currentSudoku->size;

        fprintf(fp, "%dx%d\n", size, size);

        ELEMENTO *currentRow = currentSudoku->firstElemento;
        ELEMENTO *currentCel = currentRow;

        while (currentRow != NULL) {
            fprintf(fp, "\n");

            while (currentCel != NULL) {
                fprintf(fp, "%d ", currentCel->val);
                currentCel = currentCel->e;
            }
            currentRow = currentRow->s;
            currentCel = currentRow;
        }

        fprintf(fp, "\n\n");
        currentSudoku = currentSudoku->nextSudoku;
    }

    fclose(fp);
}

/**
 * reads sudoku game from txt
 * @param j game
 */
void read_game_from_text(JOGO *j){
    int nBoards;
    FILE *fp = fopen(TEXTFILE, "r");

    if (fp == NULL)
        perror("Save From TextFile");

    fscanf(fp, "%*s %d\n", &nBoards);

    for(int p=0; p<nBoards; p++){
        int size = 0;
        int board[MAX36][MAX36];

        fscanf(fp, "%d%*c%*c", &size);
        printf("\n\nSIZE BOARD: %d", size);

        for (int k = 0; k < size; k++) {
            fscanf(fp, "\n");
            for (int m = 0; m < size; m++)
                fscanf(fp, "%d ", &board[k][m]);
        }

        SUDOKU *sudoku = malloc(sizeof(SUDOKU));
        construct_sudoku(sudoku, board, size);
        insert_sudoku_into_jogo_list(j, sudoku);
        print_sudoku(*sudoku);
        fscanf(fp, "\n\n");
    }

    fclose(fp);
}

/**
 * saves sudoku game to bin
 * @param j game
 */
void save_game_to_bin(JOGO j) {
    FILE *fp = fopen(BINFILE, "wb");

    if (fp == NULL)
        perror("Save Game To Bin");

    int nBoards = j.nBoards;
    fwrite(&nBoards, sizeof(nBoards), 1, fp);

    SUDOKU *me = j.firstSudoku;
    for(int i=0; i<nBoards; i++){
        int size = me->size;
        fwrite(&size, sizeof(size), 1, fp);


        ELEMENTO *start = me->firstElemento;
        for(int k=0; k<size; k++){
            ELEMENTO *col = start;
            for(int l=0; l<size; l++){
                fwrite(&col->val, sizeof(int), 1, fp);
                col = col->e;
            }
            start = start->s;
        }

        me = me->nextSudoku;
    }
    fclose(fp);
}

/**
 * reads sudoku game from bin
 * @param j game
 */
void read_game_from_bin(JOGO *j) {
    int board[MAX36][MAX36];
    FILE *fp = fopen(BINFILE, "rb");

    if (fp == NULL)
        perror("Read Game From Bin");

    int nBoards;
    fread(&nBoards, sizeof(nBoards), 1, fp);

    for(int i=0; i<nBoards; i++){
        int size = 0;
        fwrite(&size, sizeof(size), 1, fp);

        for(int k=0; k<size; k++)
            for(int l=0; l<size; l++)
                fwrite(&board[k][l], sizeof(int), 1, fp);

        SUDOKU *sudoku = malloc(sizeof(SUDOKU));
        construct_sudoku(sudoku, board, size);
        insert_sudoku_into_jogo_list(j, sudoku);
        print_sudoku(*sudoku);
    }

    fclose(fp);
}


/* BOARD */
/**
 * reads sudoku board from txt
 * @param jogo game where the board will be inserted to
 */
void read_board_from_text(JOGO *jogo) {
    int board[MAX36][MAX36];
    FILE *fp = fopen(TEXTFILE, "r");
    int size = 0;

    if (!fp)
        perror("Read Board From Text");

    fscanf(fp, "%d%*c%*c", &size);

    for (int i = 0; i < size; i++) {
        fscanf(fp, "\n");

        for (int j = 0; j < size; j++)
            fscanf(fp, "%d ", &board[i][j]);

    }

    fclose(fp);

    SUDOKU *sudoku = malloc(sizeof(SUDOKU));
    construct_sudoku(sudoku, board, size);
    print_sudoku(*sudoku);
    insert_sudoku_into_jogo_list(jogo, sudoku);
}

/**
 * saves sudoku board to txt
 * @param sudoku board
 */
void save_board_to_text(SUDOKU sudoku){
    FILE *fp = fopen(TEXTFILE, "r");
    int size = sudoku.size;

    if (!fp)
        perror("Save Board To Text");

    fprintf(fp, "%dx%d", size, size);

    ELEMENTO *start = sudoku.firstElemento;

    for (int i = 0; i < size; i++) {
        fscanf(fp, "\n");

        ELEMENTO *cell = start;
        for (int j = 0; j < size; j++){
            fprintf(fp, "%d ", cell->val);
            cell = cell->e;
        }

        start = start->s;
    }

    fclose(fp);
}

/**
 * saves sudoku board to bin
 * @param sudoku board
 */
void save_board_to_bin(SUDOKU sudoku) {
    FILE *fp = fopen(BINFILE, "wb");

    if (fp == NULL)
        perror("Save Game To Bin");

    int size = sudoku.size;
    ELEMENTO *currentRow = sudoku.firstElemento;
    ELEMENTO *current = currentRow;

    fwrite(&size, sizeof(size), 1, fp);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fwrite(&current->val, sizeof(int), 1, fp);
            current = current->e;
        }
        currentRow = currentRow->s;
        current = currentRow;
    }

    fclose(fp);
}

/**
 * saves sudoku board solved to txt
 * @param sudoku board
 */
void save_to_text_sol(SUDOKU sudoku) {
    FILE *fp = fopen(TEXTFILESOL, "a+");

    if (fp == NULL)
        perror("Save Board Solution To TextFile ");


    int size = sudoku.size;

    ELEMENTO *currentRow = sudoku.firstElemento;
    ELEMENTO *current = currentRow;


    fprintf(fp, "\nSolution:");
    for (int i = 0; i < size; i++) {
        fprintf(fp, "\n");

        for (int j = 0; j < size; j++) {
            fprintf(fp, "%d ", current->val);
            current = current->e;
        }
        currentRow = currentRow->s;
        current = currentRow;
    }
    fprintf(fp, "\n\n");
    fclose(fp);
}