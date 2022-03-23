#include "helper.h"
#include "nakedpairs.h"


/**
 * converts sudoku from matrix into structs
 * @param sudoku struct
 * @param sudokuMatrix original sudoku matrix
 * @param size size of sudoku
 */
void construct_sudoku(SUDOKU *sudoku, int sudokuMatrix[][MAX36], int size) {

    ELEMENTO *cima = NULL;
    ELEMENTO *anterior = NULL;

    if (!(size == 9 || size == 16 || size == 25 || size == 36)) {
        printf("\n DIMENSAO INVALIDA");
        return;
    }

    sudoku->firstElemento = NULL;
    sudoku->size = size;
    sudoku->nextSudoku = NULL;

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            ELEMENTO *atual = malloc(sizeof(ELEMENTO));
            atual->val = sudokuMatrix[row][col];
            atual->n = NULL;
            atual->no = NULL;
            atual->ne = NULL;
            atual->s = NULL;
            atual->so = NULL;
            atual->se = NULL;
            atual->o = NULL;
            atual->e = NULL;
            atual->firstHip = NULL;
            atual->numHip = 0;

            // 1º Elemento da Matriz;
            if (sudoku->firstElemento == NULL) {
                sudoku->firstElemento = atual;
                cima = atual;
                anterior = atual;
            }

            // 1º Elemento da Linha;
            if ((row > 0) && (col == 0)) {
                atual->n = cima;            //|
                cima->s = atual;            //|-> Linkar N

                atual->ne = cima->e;        //|
                if (cima->e != NULL)          //|
                    cima->e->so = atual;    //|-> Linkar NE

                cima = cima->s;
                anterior = cima;
            }

            // Restantes Elementos;
            if (col > 0) {
                anterior->e = atual;
                atual->o = anterior;        //|
                //|-> Linkar O

                atual->no = anterior->n;    //|
                if (row != 0) {                 //|
                    anterior->n->se = atual; //|-> Linkar NO

                    atual->n = anterior->ne;        //|
                    anterior->ne->s = atual;        //|-> Linkar N

                    atual->ne = anterior->ne->e;    //|
                    if (col != size - 1)      //|
                        anterior->ne->e->so = atual;//|-> Linkar NE


                }
                anterior = anterior->e;
            }
        }

    }
}

/**
 * prints sudoku board
 * @param sudoku board
 */
void print_sudoku(SUDOKU sudoku) {
    printf("\n");
    ELEMENTO *print = sudoku.firstElemento;
    ELEMENTO *linha = sudoku.firstElemento;

    for (int row = 0; row < sudoku.size; row++) {
        for (int col = 0; col < sudoku.size; col++) {
            printf(" %2d ", print->val);
            print = print->e;
        }
        linha = linha->s;
        print = linha;
        printf("\n");
    }
}

/**
 * improved sudoku solving method
 * @param sudoku board
 */
void main_helper(SUDOKU *sudoku) {
    printf("\nCALCULATING HIP");
    calculate_hip(sudoku);
    print_hip(*sudoku);
    solver_tactics(*sudoku);
}

/**
 * calcula todos os numeros candidatos para as celulas que se encontram por preencher
 * @param sudoku board
 */
void calculate_hip(SUDOKU *sudoku) {
    int size = sudoku->size;
    ELEMENTO *currentRow = sudoku->firstElemento;
    ELEMENTO *current = currentRow;


    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (current->val == 0) {
                for (int value = 1; value <= size; value++) {
                    if (is_legal(*sudoku, row, col, value)) {
                        HIP *temp = malloc(sizeof(HIP));
                        temp->val = value;
                        current->numHip++;
                        if (current->firstHip == NULL) {
                            temp->nextHip = current->firstHip;
                            current->firstHip = temp;
                        } else {
                            HIP *currentHip = current->firstHip;
                            while (currentHip->nextHip != NULL)
                                currentHip = currentHip->nextHip;
                            temp->nextHip = currentHip->nextHip;
                            currentHip->nextHip = temp;
                        }
                    }

                }

            } else {
                current->numHip = 0;
                current->firstHip = NULL;
            }
            //avança para o próximo elemento da linha
            current = current->e;
        }
        //avança para o 1º elemento da linha seguinte
        currentRow = currentRow->s;
        current = currentRow;
    }
}

/**
 * finds cells with only 1 number possibility
 * @param sudoku
 * @return
 */
int alone_number(SUDOKU sudoku) {
    int size = sudoku.size;
    int altered = 0;
    ELEMENTO *currentRow = sudoku.firstElemento;
    ELEMENTO *current = currentRow;

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {

            // Only one possibility
            if (current->numHip == 1) {
                int value = find_one(sudoku, row, col, 1);

                if (is_legal(sudoku, row, col, value)) {
                    current->val = value;
                    //update_hip(hip, row, col, value, size);
                    calculate_hip(&sudoku);
                    altered = 1;
                }
            }
        }
        currentRow = currentRow->s;
        current = currentRow;
    }

    return altered;
}

/**
 * imprime todos os numeros candidatos de todas as celulas que se encontram por preencher
 * @param sudoku board
 */
void print_hip(SUDOKU sudoku) {
    ELEMENTO *currentRow = sudoku.firstElemento;
    ELEMENTO *current = currentRow;
    int row = 0, col = 0;
    printf("\nHIPOTESES:\n\n");
    while (currentRow != NULL) {
        while (current != NULL) {

            if (current->numHip > 0) {
                printf("\n Count = %d || Values[%d][%d]:", current->numHip, row, col);
                HIP *hip = current->firstHip;
                for (int i = 0; i < current->numHip; i++) {
                    printf(" %d;", hip->val);
                    hip = hip->nextHip;
                }
            }

            col++;
            current = current->e;
        }

        printf("\n\n");
        currentRow = currentRow->s;
        current = currentRow;
        col = 0;
        row++;
    }
}

/**
 * remove value das hipoteses de todas as celulas da linha
 * @param sudoku board
 * @param row row where the value belongs to
 * @param value value that's going to be removed from candidates
 */
void update_hip_row(SUDOKU *sudoku, int row, int value) {
    int size = sudoku->size;
    ELEMENTO *current = sudoku->firstElemento;

    //vai para a linha que pretendemos atualizar
    for (int r = 0; r < row; r++) {
        current = current->s;
    }


    //itera as colunas
    for (int col = 0; col < size; col++) {
        delete_hip(current, value);
        current = current->e;
    }
}

/**
 * remove value das hipoteses de todas as celulas da coluna
 * @param sudoku board
 * @param col col where the value belongs to
 * @param value value that's going to be removed from candidates
 */
void update_hip_column(SUDOKU *sudoku, int col, int value) {
    int size = sudoku->size;

    ELEMENTO *current = sudoku->firstElemento;

    //vai para a coluna que pretendemos atualizar
    for (int c = 0; c < col; c++) {
        current = current->e;
    }

    //itera as linhas
    for (int row = 0; row < size; row++) {
        delete_hip(current, value);
        current = current->s;
    }
}

/**
 * remove value das hipoteses de todas as celulas do quadrado
 * @param sudoku board
 * @param row row where value belongs to
 * @param col col where value belongs to
 * @param value value that's going to be removed from candidates
 */
void update_hip_sqr(SUDOKU *sudoku, int row, int col, int value) {
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

    ELEMENTO *currentRow = current;


    //itera todas as celulas do quadrado
    for (int r = row_corner; r < (row_corner + size_square); r++) {
        for (int c = col_corner; c < (col_corner + size_square); c++) {
            delete_hip(current, value);
            //vai para a coluna seguinte
            current = current->e;
        }
        //vai para a linha seguinte
        currentRow = currentRow->s;
        current = currentRow;
    }
}

/**
 * remove value das hipoteses de todas as celulas da diagonal principal
 * @param sudoku board
 * @param row row where value belongs to
 * @param col col where value belongs to
 * @param value value that's going to be removed from candidates
 */
void update_hip_diag_main(SUDOKU *sudoku, int row, int col, int value) {
    int size = sudoku->size;

    if (row == col) {
        ELEMENTO *current = sudoku->firstElemento;

        //diagonal principal;
        for (int i = 0; i < size; i++) {
            delete_hip(current, value);
            //nextSudoku pos
            current = current->se;
        }
    }
}

/**
 * remove value das hipoteses de todas as celulas da diagonal secundaria
 * @param sudoku board
 * @param row row where value belongs to
 * @param col col where value belongs to
 * @param value value that's going to be removed from candidates
 */
void update_hip_diag_sec(SUDOKU *sudoku, int row, int col, int value) {
    int size = sudoku->size;

    if ((row == col - size) && (col == size - row)) {
        ELEMENTO *current = sudoku->firstElemento;

        //get to ponta + nordeste do sudoku
        while (current->e != NULL) {
            current = current->e;
        }

        //diagonal secundaria
        for (int i = 0; i < size; i++) {
            delete_hip(current, value);
            //nextSudoku pos
            current = current->so;
        }
    }
}

/**
 * atualiza as hipoteses conforme o valor alterado
 * @param sudoku board
 * @param row linha
 * @param col coluna
 * @param value valor que vai ser removido das hipoteses
 */
void update_hip(SUDOKU *sudoku, int row, int col, int value) {
    update_hip_row(sudoku, row, value);
    update_hip_column(sudoku, col, value);
    update_hip_sqr(sudoku, row, col, value);
    update_hip_diag_main(sudoku, row, col, value);
    update_hip_diag_sec(sudoku, row, col, value);
}

/**
 *
 * @param sudoku board
 * @param row linha
 * @param col coluna
 * @param startingPoint menor numero candidato possivel
 * @return numero candidato
 */
int find_one(SUDOKU sudoku, int row, int col, int startingPoint) {
    int size = sudoku.size;
    if (startingPoint <= size) {
        ELEMENTO *current = sudoku.firstElemento;

        //gets to current sudoku cell
        for (int r = 0; r < row; r++) {
            current = current->s;
        }
        for (int c = 0; c < col; c++) {
            current = current->e;
        }


        HIP *hip = current->firstHip;
        while (hip != NULL) {
            if (hip->val >= startingPoint)
                return hip->val;

            hip = hip->nextHip;
        }
    }
}

/**
 * improved sudoku solving method
 * @param sudoku board
 * @return
 */
int solver_tactics(SUDOKU sudoku) {
    if (noZeros(sudoku)) {
        printf("\nFOUND SOLUTION ON NON BACKTRACKING SOLVER:\n");
        print_sudoku(sudoku);
        return 1;
    }

    // Alone number
    if (alone_number(sudoku))
        return solver_tactics(sudoku);


    // NAKED
    int pairs[4] = {-1, -1, -1, -1};
    if (exists_pairs(sudoku, pairs)) {
        int v1 = find_one(sudoku, pairs[0], pairs[1], 1);
        int v2 = find_one(sudoku, pairs[0], pairs[1], v1 + 1);
        int v3 = find_one(sudoku, pairs[0], pairs[1], 1);
        int v4 = find_one(sudoku, pairs[0], pairs[1], v3 + 1);


        int r1 = pairs[0], c1 = pairs[1];
        ELEMENTO *primeiro = sudoku.firstElemento;
        for (int r = 0; r < r1; r++) {
            primeiro = primeiro->s;
        }
        for (int c = 0; c < c1; c++) {
            primeiro = primeiro->e;
        }
        primeiro->val = v1;

        int r2 = pairs[2], c2 = pairs[3];
        ELEMENTO *segundo = sudoku.firstElemento;
        for (int r = 0; r < r2; r++) {
            segundo = segundo->s;
        }
        for (int c = 0; c < c2; c++) {
            segundo = segundo->e;
        }
        segundo->val = v2;

        calculate_hip(&sudoku);
        if (solver_tactics(sudoku))
            return 1;

        int r3 = pairs[0], c3 = pairs[1];
        ELEMENTO *terceiro = sudoku.firstElemento;
        for (int r = 0; r < r3; r++) {
            terceiro = terceiro->s;
        }
        for (int c = 0; c < c3; c++) {
            terceiro = terceiro->e;
        }
        terceiro->val = v3;

        int r4 = pairs[2], c4 = pairs[3];
        ELEMENTO *quarto = sudoku.firstElemento;
        for (int r = 0; r < r4; r++) {
            quarto = quarto->s;
        }
        for (int c = 0; c < c4; c++) {
            quarto = quarto->e;
        }
        quarto->val = v4;

        calculate_hip(&sudoku);
        if (solver_tactics(sudoku))
            return 1;

    }


    printf("\nTRYING BACKTRACKING");
    return main_solver(&sudoku);
}

/**
 * fills cells with only 1 candidate number
 * @param sudoku board
 */
void fill_cells_with_one_hip(SUDOKU *sudoku) {
    int size = sudoku->size;

    ELEMENTO *current = sudoku->firstElemento;
    ELEMENTO *currentRow = current;

    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (current->numHip == 1) {
                current->val = current->firstHip->val;
                update_hip(sudoku, row, col, current->firstHip->val);
            }
            current = current->e;
        }
        currentRow = currentRow->s;
        current = currentRow;
    }
}

/**
 * deletes candidate number from cell
 * @param current cell where we will be deleting the candidate number
 * @param value candidate number to be removed from cell
 */
void delete_hip(ELEMENTO *current, int value) {
    if (current->numHip > 0) {
        //se estiver na 1ª pos
        if (current->firstHip->val == value) {
            HIP *del = current->firstHip;
            current->firstHip = current->firstHip->nextHip;
            current->numHip--;
            free(del);
        } else {
            HIP *curhip = current->firstHip;
            HIP *nexthip = current->firstHip->nextHip;
            while (curhip != NULL && nexthip != NULL) {
                if (nexthip->val == value) {
                    curhip->nextHip = nexthip->nextHip;
                    current->numHip--;
                    free(nexthip);
                }
                curhip = curhip->nextHip;
                nexthip = nexthip->nextHip;
            }
        }
    }
}

/**
 * inserts sudoku into game
 * @param j game
 * @param sudoku board
 */
void insert_sudoku_into_jogo_list(JOGO *j, SUDOKU *sudoku) {
    //HEAD
    if (j->firstSudoku == NULL) {
        j->firstSudoku = sudoku;

    } else {
        SUDOKU *current = j->firstSudoku;

        while (current->nextSudoku != NULL)
            current = current->nextSudoku;

        current->nextSudoku = sudoku;
    }

    j->nBoards++;
}

/**
 * removes first sudoku from game
 * @param j game
 */
void remove_sudoku_from_jogo_list(JOGO *j) {
    SUDOKU *next = j->firstSudoku->nextSudoku;
    SUDOKU *first = j->firstSudoku;
    j->firstSudoku = next;
    free(first);
}

/**
 * creates an array of sudokus
 * @param j game
 * @param size number of sudoku boards
 */
void create_array_sudokus(JOGO *j, int size) {
    j->nBoards = size;
    j->firstSudoku = (SUDOKU *) malloc(size * sizeof(SUDOKU));
}