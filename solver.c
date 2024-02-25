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

Node* create_dancing_links(sparse_matrix matrix){
    
    Node* anchor_node;

    
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

ColumnNode cover_column(ColumnNode col){

}

ColumnNode uncover_column(ColumnNode col){
    
}