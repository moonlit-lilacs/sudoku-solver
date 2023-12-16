#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <string.h>

#define GRID_SIZE 9

typedef struct {

    int matrix[GRID_SIZE][GRID_SIZE];

} sudoku_grid;

typedef struct {

    int nums[81];

} game_state;

int print_grid(sudoku_grid grid);
int populate_grid(sudoku_grid *grid, game_state state);

#endif
