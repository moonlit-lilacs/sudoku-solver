#include "solver.h"


sparse_matrix* create_DLX_matrix(int sudoku[GRID_SIZE][GRID_SIZE]) {

    sparse_matrix* s_matrix = malloc(sizeof(sparse_matrix));
    s_matrix->rows = GRID_SIZE*GRID_SIZE*GRID_SIZE;
    s_matrix->cols = GRID_SIZE*GRID_SIZE*4;
    //printf("setting s_matrix to zero\n");
    for(int r = 0; r < s_matrix->rows; r++){
        for(int c = 0; c < s_matrix->cols; c++){
            s_matrix->matrix[r][c] = 0;
        }
    }
    
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            int num = sudoku[row][col];
            //printf("have num %d\n", num);
            if (num) {
                int constraints[4];
                index_constraints(row, col, num, constraints);
                int target_row = (row * GRID_SIZE + col) * UNIQUE_NUMS + (num);
                for (int i = 0; i < 4; i++) {
                    s_matrix->matrix[target_row][constraints[i]] = 1;
                    //printf("s_matrix[%d][%d] = %d\n", target_row, constraints[i], s_matrix->matrix[target_row][constraints[i]]);
                }

            } else {         
                for (int num = 0; num < GRID_SIZE; num++) {
                    int constraints[4];
                    int target_row = (row * GRID_SIZE + col) * UNIQUE_NUMS + (num);
                    index_constraints(row, col, num, constraints);
                    for (int i = 0; i < 4; i++) {
                    s_matrix->matrix[target_row][constraints[i]] = 1;
                    //printf("s_matrix[%d][%d] = %d\n", target_row, constraints[i], s_matrix->matrix[target_row][constraints[i]]);
                    }
                }
            }

        }
    }
    return s_matrix;
}

column_node* create_dancing_links(sparse_matrix* matrix){
    
    column_node* anchor_node = malloc(sizeof(column_node));
    
    anchor_node->ind = -1;
    anchor_node->header.left = (node *) anchor_node;
    anchor_node->header.right = (node *) anchor_node;
    anchor_node->header.up = (node *) anchor_node;
    anchor_node->header.down = (node *) anchor_node;
    anchor_node->header.column = anchor_node;

    column_node* last_column = anchor_node;
    
    for(int i = 0; i < matrix->cols; i++){
        column_node* new_column = malloc(sizeof(column_node));
        new_column->ind = i;
        new_column->size = 0;
        new_column->header.column = new_column;

        //standard circularly linked list insertion.
        new_column->header.left = &(last_column->header);
        new_column->header.right = last_column->header.right;
        new_column->header.up = (node *) new_column;
        new_column->header.down = (node *) new_column;

        last_column->header.right->left = (node *) new_column;
        last_column->header.right = (node *) new_column;

        last_column = new_column;
    }

    for(int row = 0; row < matrix->rows; row++){
        node* row_start_node = NULL;
        
        for(int col = 0; col < matrix->cols; col++){
            node* last_node = NULL;
            if(matrix->matrix[row][col] == 1){
                column_node* col_header = anchor_node->header.right->column;

                while(col_header->ind != col){
                    col_header = col_header->header.right->column;
                }
                
                node* new_node = malloc(sizeof(node));
                new_node->column = col_header;
                col_header->size++;
                
                if(row_start_node == NULL){
                    new_node->left = new_node;
                    new_node->right = new_node;
                    row_start_node = new_node;
                }
                
                else{
                    new_node->right = row_start_node;
                    new_node->left = row_start_node->left;
                    row_start_node->left->right = new_node;
                    row_start_node->left = new_node;
                }


                new_node->down = (node *) col_header;
                new_node->up = col_header->header.up;
                col_header->header.up->down = new_node;
                col_header->header.up = new_node;
                
            }

        }
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
    column_node* cursor = n->header.right->column;
    printf("%d\n", n->ind);
    while(cursor != n){
        printf("%d\n", cursor->ind);
        cursor = cursor->header.right->column;
    }
}