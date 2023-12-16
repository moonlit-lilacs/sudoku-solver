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



    return 0;
}
*/