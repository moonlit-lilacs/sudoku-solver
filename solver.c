#include "sudoku.h"
#include "solver.h"

int create_DLX_matrix(sudoku_grid grid);
int index_constraints(int row, int col, int num, int* constraints);


int create_DLX_matrix(sudoku_grid grid){
    int constraints_num = 4 * GRID_SIZE * GRID_SIZE;
}


sparse_matrix build_sparse_matrix(int sudoku[GRID_SIZE][GRID_SIZE]) {
    
    sparse_matrix matrix;
    
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            int num = sudoku[row][col];
            if (num) {
                int constraints[4];
                index_constraints(row, col, num - 1, constraints);

                printf("Cell [%d,%d] with number %d: ", row, col, num);
                for (int i = 0; i < 4; i++) {
                    printf("%d ", constraints[i]);
                }
                printf("\n\n");
            } else {         
                for (int num = 0; num < GRID_SIZE; num++) {
                    int constraints[4];
                    index_constraints(row, col, num, constraints);
                    printf("Cell [%d,%d] with number %d: ", row, col, num);
                    for (int i = 0; i < 4; i++) {
                    printf("%d ", constraints[i]);
                    }
                    printf("\n");
                }
            
                printf("\n");
            }

        }
    }
}

int index_constraints(int row, int col, int num, int* constraints) {
    // Calculating constraint indices for a given placement
    constraints[0] = row * GRID_SIZE + col; // Cell constraint
    constraints[1] = GRID_SIZE*GRID_SIZE + (row * GRID_SIZE + num); // Row constraint
    constraints[2] = 2*GRID_SIZE*GRID_SIZE + (col * GRID_SIZE + num); // Column constraint
    constraints[3] = 3*GRID_SIZE*GRID_SIZE + ((row / 3) * 3 + (col / 3)) * GRID_SIZE + num; // Box constraint

    return 0;
}