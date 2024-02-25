#include "solver.h"


sparse_matrix create_DLX_matrix(int sudoku[GRID_SIZE][GRID_SIZE]) {
    
    printf("starting dlx matrix\n");

    sparse_matrix s_matrix;
    s_matrix.rows = GRID_SIZE*GRID_SIZE*GRID_SIZE;
    s_matrix.cols = GRID_SIZE*GRID_SIZE*4;
    printf("setting s_matrix to zero\n");
    for(int r = 0; r < s_matrix.rows; r++){
        for(int c = 0; c < s_matrix.cols; c++){
            s_matrix.matrix[r][c] = 0;
        }
    }
    
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            int num = sudoku[row][col];
            printf("have num %d\n", num);
            if (num) {
                int constraints[4];
                index_constraints(row, col, num, constraints);
                int target_row = (row * GRID_SIZE + col) * UNIQUE_NUMS + (num);
                for (int i = 0; i < 4; i++) {
                    s_matrix.matrix[target_row][constraints[i]] = 1;
                    printf("s_matrix[%d][%d] = %d\n", target_row, constraints[i], s_matrix.matrix[target_row][constraints[i]]);
                }

            } else {         
                for (int num = 0; num < GRID_SIZE; num++) {
                    int constraints[4];
                    int target_row = (row * GRID_SIZE + col) * UNIQUE_NUMS + (num);
                    index_constraints(row, col, num, constraints);
                    for (int i = 0; i < 4; i++) {
                    s_matrix.matrix[target_row][constraints[i]] = 1;
                    printf("s_matrix[%d][%d] = %d\n", target_row, constraints[i], s_matrix.matrix[target_row][constraints[i]]);
                    }
                }
            }

        }
    }
    return s_matrix;
}

column_node* create_dancing_links(sparse_matrix matrix){
    
    column_node* anchor_node = malloc(sizeof(column_node));
    
    anchor_node->ind = -1;
    anchor_node->left = anchor_node;
    anchor_node->right = anchor_node;

    column_node* cursor = anchor_node;
    
    for(int i = 0; i < matrix.cols; i++){
        column_node* column = malloc(sizeof(column_node));
        column->ind = i;

        //standard circularly linked list insertion. because these are only column nodes, we don't need to worry about the vertical circularity yet.
        column->left = cursor;
        column->right = cursor->right;
        cursor->right->left = column;
        cursor->right = column;
        
        cursor = column;
    }
    
    return anchor_node;
}


int index_constraints(int row, int col, int num, int* constraints) {
    // Calculating constraint indices for a given placement
    constraints[0] = row * GRID_SIZE + col; // Cell constraint
    constraints[1] = GRID_SIZE*GRID_SIZE + (row * GRID_SIZE + num); // Row constraint
    constraints[2] = 2*GRID_SIZE*GRID_SIZE + (col * GRID_SIZE + num); // Column constraint
    constraints[3] = 3*GRID_SIZE*GRID_SIZE + ((row / 3) * 3 + (col / 3)) * GRID_SIZE + num; // Box constraint

    return 0;
}

column_node cover_column(column_node col){
    return col;
}

column_node uncover_column(column_node col){
    return col;
}

void print_circularly_linked_list(column_node* n){
    column_node* cursor = n->right;
    printf("%d\n", n->ind);
    while(cursor != n){
        printf("%d\n", cursor->ind);
        cursor = cursor->right;
    }
}