#ifndef LP_AED_FASE1_FILES_H
#define LP_AED_FASE1_FILES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "backtracking.h"

#define TEXTFILE "file.txt"
#define TEXTFILESOL "sol.txt"
#define BINFILE "file.bin"


void save_to_text(JOGO j);


void read_board_from_text(JOGO *jogo);

void save_to_bin(SUDOKU sudoku);

void read_from_bin(JOGO *j);

void save_to_text_sol(SUDOKU sudoku);

void read_game_from_text(JOGO *j);

void save_board_to_text(SUDOKU sudoku);

void save_game_to_text(JOGO j);

void save_game_to_bin(JOGO j);

void read_game_from_bin(JOGO *j);

#endif //LP_AED_FASE1_FILES_H
