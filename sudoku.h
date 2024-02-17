#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <string.h>

#define GRID_SIZE 9
#define BOX_SIZE 3
#define BOX_PER_COL 3
#define BOX_PER_ROW 3
#define NUMBER_SUM 45

typedef struct {

    int matrix[GRID_SIZE][GRID_SIZE];

} sudoku_grid;

typedef struct {

    int nums[81];

} game_state;

typedef struct {

    //for standard sudoku, this will be 729x324
    int matrix[GRID_SIZE*GRID_SIZE*GRID_SIZE][GRID_SIZE*GRID_SIZE*GRID_SIZE*4];

} sparse_matrix;


int print_grid(sudoku_grid grid);
int populate_grid(sudoku_grid *grid, game_state state);

#endif
