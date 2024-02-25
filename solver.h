#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <string.h>
#include "sudoku.h"

typedef struct Node {
    struct Node *left, *right, *up, *down;
    struct ColumnNode *column;
} Node;


typedef struct ColumnNode{
    Node node;
    int size; // number of nodes belonging to the column
    int ind;
} ColumnNode;

Node* create_dancing_links(sparse_matrix matrix);
sparse_matrix create_DLX_matrix(int sudoku[GRID_SIZE][GRID_SIZE]);
int index_constraints(int row, int col, int num, int* constraints);
ColumnNode cover_column(ColumnNode col);
ColumnNode uncover_column(ColumnNode col);
sudoku_grid search(sparse_matrix matrix);


#endif