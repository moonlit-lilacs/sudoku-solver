#include "sudoku.h"

int print_grid(sudoku_grid grid){

    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            printf("%d ", grid.matrix[i][j]);
        }
        printf("\n");
    }


    return 0;
}

int populate_grid(sudoku_grid *grid, game_state state){

    int counter = 0;
    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            grid->matrix[i][j] = state.nums[counter];
            counter++;
        }
    }
    printf("Grid populated successfully!\n");
    return 0;
}

int check_solution(sudoku_grid *grid){
    //Sum of digits 1-9 is 45. For any correctly solved column, row, or box, their digits should add up to
    // 45, or NUMBER_SUM.
    int counter = NUMBER_SUM;
    
    // Loop through the rows, checking if their sum is equal to 45. Reset 45 after each row.
    for(int col = 0; col < GRID_SIZE; col++){
        for(int row = 0; row < GRID_SIZE; row++){
            counter -= grid->matrix[row][col];
        }
        if (counter != 0){
            return 0;
        }
        counter = NUMBER_SUM;
    }
    
    //Same thing but with columns.
    for(int row = 0; row < GRID_SIZE; row++){
        for(int col = 0; col < GRID_SIZE; col++){
            counter -= grid->matrix[row][col];
        }
        if (counter != 0){
            return 0;
        }
        counter = NUMBER_SUM;
    }

    //This may be one of the ugliest pieces of code i've ever witten. Please don't judge the quadruply nested
    // for loops too harshly, i promise i'll think of something better eventually.
    for(int box_row = 0; box_row < BOX_PER_ROW; box_row++){
        for(int box_col = 0; box_col < BOX_PER_COL; box_col++){
            for(int row = 0; row < BOX_SIZE; row++){
                for (int col = 0; col < BOX_SIZE; col++){
                    counter -= grid->matrix[(3*box_row)+row][(3*box_col)+col];
                }
                if (counter != 0){
                        return 0;
                }
                counter = NUMBER_SUM;
            }
        }
    }

    //If all checks passed, we must necessarily have a solution, so we return 1.
    return 1;
}

/*
int main() {
    sudoku_grid game1;
    game_state state1;
    int values[81] = {4,9,5,1,7,8,6,3,2,1,0,8,5,3,6,0,7,0,0,0,6,4,0,2,1,0,5,0,5,4,0,0,0,0,1,3,9,0,1,7,2,5,4,0,0,0,0,2,0,0,0,5,0,0,6,8,0,2,0,0,0,0,1,2,0,0,0,0,7,0,5,0,5,0,0,0,0,1,0,0,0};
    memcpy(state1.nums, values, sizeof(values));
    


    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            game1.matrix[i][j] = 0;
        }
    }

    game1.matrix[0][0] = 5;

    //printf("Value at (0,0): %d\n", game1.matrix[0][0]);

    print_grid(game1);
    printf("\n");
    populate_grid(&game1, state1);
    printf("\n");
    print_grid(game1);

    printf("Solved? %d", check_solution(&game1));


    return 0;
}
*/