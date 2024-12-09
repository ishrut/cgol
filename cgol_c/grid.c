#include <stdlib.h>
#include <stdio.h>
#include "grid.h"

grid grid_init(int rows, int cols) {
    int **data = (int**)malloc(rows * sizeof(int*));
    for (int i=0; i<rows; i++) {
        *(data+i) = (int*)malloc(cols * sizeof(int));
    }
    for(int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            *(*(data+i)+j) = 0;
        }
    }
    grid ret_grid;
    ret_grid.data = data;
    ret_grid.rows = rows;
    ret_grid.cols = cols;
    return ret_grid;
}

void grid_free(grid* matrix) {
    for (int i=0; i<matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
}

int grid_set(grid* matrix, int x, int y) {
    if (x >= matrix->rows - 1 || y >= matrix->cols - 1) {
        return 1;
    }
    matrix->data[x][y] = 1;
    return 0;
}

void grid_show(grid* matrix) {
    for (int i=0; i<matrix->rows; i++) {
        for (int j=0; j<matrix->cols; j++) {
            if (matrix->data[i][j] == 0) {
                printf(" ");
            } else {
                printf("#");
            }
        }
        printf("\n");
    }
}

int grid_num_alive(grid* matrix) {
    int num_alive = 0;
    for (int i=0; i<matrix->rows; i++) {
        for (int j=0; j<matrix->cols; j++) {
            if (matrix->data[i][j] == 1) {
                num_alive ++;
            }
        }
    }
    return num_alive;
}

int grid_state(int*  state, int* alive) {
    if (*state == 1) {
        if (*alive < 2) {
            return 0;
        } else if (*alive == 2 || *alive == 3) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (*alive == 3) {
            return 1;
        } else {
            return *state;
        }
    }
}

int grid_next(grid* matrix) {
    grid new_grid = grid_init(matrix->rows, matrix->cols);
    for (int i=0; i<matrix->rows; i++) {
        for (int j=0; j<matrix->cols; j++) {
            //check for neighbours
            if (i == 0) {
                //check for top row
                if (j == 0) {
                    //check top left element
                    int alive = 0;
                    if (matrix->data[i][j+1] == 1) { alive++; }
                    if (matrix->data[i+1][j] == 1) { alive ++; }
                    if (matrix->data[i+1][j+1] == 1) { alive ++; }
                    int new_state = grid_state(&matrix->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                } else if (j == matrix->cols - 1) {
                    //check for top right element
                    int alive = 0;
                    if (matrix->data[i][j-1] == 1) { alive++; }
                    if (matrix->data[i+1][j] == 1) { alive ++; }
                    if (matrix->data[i+1][j-1] == 1) { alive ++; }
                    int new_state = grid_state(&matrix->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                } else {
                    //check for top middle elements
                    int alive = 0;
                    if (matrix->data[i][j-1] == 1) { alive++; }
                    if (matrix->data[i][j+1] == 1) { alive++; }
                    if (matrix->data[i+1][j-1] == 1) { alive++; }
                    if (matrix->data[i+1][j] == 1) { alive++; }
                    if (matrix->data[i+1][j+1] == 1) { alive++; }
                    int new_state = grid_state(&matrix->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                }
            } else if (i == matrix->rows - 1) {
                //check for bottom row
                if (j == 0) {
                    //check for bottom left element
                    int alive = 0;
                    if (matrix->data[i][j+1] == 1) { alive++; }
                    if (matrix->data[i-1][j] == 1) { alive++; }
                    if (matrix->data[i-1][j+1] == 1) { alive++; }
                    int new_state = grid_state(&matrix->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                } else if (j == matrix->cols -1) {
                    //check for bottom right element
                    int alive = 0;
                    if (matrix->data[i][j-1] == 1) { alive++; }
                    if (matrix->data[i-1][j] == 1) { alive++; }
                    if (matrix->data[i-1][j-1] == 1) { alive++; }
                    int new_state = grid_state(&matrix->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                } else {
                    //check for bottom middle elements
                    int alive = 0;
                    if (matrix->data[i][j+1] == 1) { alive++; }
                    if (matrix->data[i][j-1] == 1) { alive++; }
                    if (matrix->data[i-1][j-1] == 1) { alive++; }
                    if (matrix->data[i-1][j] == 1) { alive++; }
                    if (matrix->data[i-1][j+1] == 1) { alive++; }
                    int new_state = grid_state(&matrix->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                }
            } else {
                //checking for middle rows
                if (j == 0) {
                    //check for middle left element
                    int alive = 0;
                    if (matrix->data[i][j+1] == 1) { alive++; }
                    if (matrix->data[i-1][j] == 1) { alive++; }
                    if (matrix->data[i-1][j+1] == 1) { alive++; }
                    if (matrix->data[i+1][j] == 1) { alive++; }
                    if (matrix->data[i+1][j+1] == 1) { alive++; }
                    int new_state = grid_state(&matrix->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                } else if (j == matrix->cols - 1) {
                    //check for middle right element
                    int alive = 0;
                    if (matrix->data[i][j-1] == 1) { alive++; }
                    if (matrix->data[i-1][j] == 1) { alive++; }
                    if (matrix->data[i-1][j-1] == 1) { alive++; }
                    if (matrix->data[i+1][j] == 1) { alive++; }
                    if (matrix->data[i+1][j-1] == 1) { alive++; }
                    int new_state = grid_state(&matrix->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                } else {
                    //check for middle middle elements
                    int alive = 0;
                    if (matrix->data[i][j+1] == 1) { alive++; }
                    if (matrix->data[i][j-1] == 1) { alive++; }
                    if (matrix->data[i-1][j-1] == 1) { alive++; }
                    if (matrix->data[i-1][j] == 1) { alive++; }
                    if (matrix->data[i-1][j+1] == 1) { alive++; }
                    if (matrix->data[i+1][j-1] == 1) { alive++; }
                    if (matrix->data[i+1][j] == 1) { alive++; }
                    if (matrix->data[i+1][j+1] == 1) { alive++; }
                    int new_state = grid_state(&matrix->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                }
            }
        }
    }
    grid_free(matrix);
    matrix->data = new_grid.data;
    int alives = grid_num_alive(matrix);
    if (alives == 0) {
        return 1;
    } else {
        return 0;
    }
}
