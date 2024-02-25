#ifndef SOLVER_H
#define SOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudoku.h"

typedef struct node {
    struct node *left, *right, *up, *down;
    struct column_node *column;
} node;


typedef struct column_node{
    node head;
    int size; // number of nodes belonging to the column
    int ind;
    struct column_node *left, *right;
} column_node;

column_node* create_dancing_links(sparse_matrix matrix);
sparse_matrix create_DLX_matrix(int sudoku[GRID_SIZE][GRID_SIZE]);
int index_constraints(int row, int col, int num, int* constraints);
column_node cover_column(column_node col);
column_node uncover_column(column_node col);
sudoku_grid search(sparse_matrix matrix);
void print_circularly_linked_list(column_node* n);


#endif