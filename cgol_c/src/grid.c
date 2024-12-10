#include "../include/grid.h"

Grid grid_init(int rows, int cols) {
    bool **data = (bool**)malloc(rows * sizeof(bool*));
    for (int i=0; i<rows; i++) {
        *(data+i) = (bool*)malloc(cols * sizeof(bool));
    }
    for(int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            *(*(data+i)+j) = 0;
        }
    }
    Grid ret_grid;
    ret_grid.data = data;
    ret_grid.rows = rows;
    ret_grid.cols = cols;
    return ret_grid;
}

void grid_free(Grid* grid) {
    for (int i=0; i<grid->rows; i++) {
        free(grid->data[i]);
    }
    free(grid->data);
}

int grid_set(Grid* grid, int x, int y) {
    if (x >= grid->rows - 1 || y >= grid->cols - 1) {
        return 1;
    }
    grid->data[x][y] = true;
    return 0;
}

void grid_show(Grid* grid) {
    for (int i=0; i<grid->rows; i++) {
        for (int j=0; j<grid->cols; j++) {
            if (grid->data[i][j] == false) {
                printf(" ");
            } else {
                printf("#");
            }
        }
        printf("\n");
    }
}

int grid_num_alive(Grid* grid) {
    int num_alive = 0;
    for (int i=0; i<grid->rows; i++) {
        for (int j=0; j<grid->cols; j++) {
            if (grid->data[i][j] == true) {
                num_alive ++;
            }
        }
    }
    return num_alive;
}

bool grid_state(bool*  state, int* alive) {
    if (*state == true) {
        if (*alive < 2) {
            return false;
        } else if (*alive == 2 || *alive == 3) {
            return true;
        } else {
            return false;
        }
    } else {
        if (*alive == 3) {
            return true;
        } else {
            return *state;
        }
    }
}

void grid_next(Grid* grid) {
    Grid new_grid = grid_init(grid->rows, grid->cols);
    for (int i=0; i<grid->rows; i++) {
        for (int j=0; j<grid->cols; j++) {
            //check for neighbours
            if (i == 0) {
                //check for top row
                if (j == 0) {
                    //check top left element
                    int alive = 0;
                    if (grid->data[i][j+1] == true) { alive++; }
                    if (grid->data[i+1][j] == true) { alive ++; }
                    if (grid->data[i+1][j+1] == true) { alive ++; }
                    bool new_state = grid_state(&grid->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                } else if (j == grid->cols - 1) {
                    //check for top right element
                    int alive = 0;
                    if (grid->data[i][j-1] == 1) { alive++; }
                    if (grid->data[i+1][j] == 1) { alive ++; }
                    if (grid->data[i+1][j-1] == 1) { alive ++; }
                    bool new_state = grid_state(&grid->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                } else {
                    //check for top middle elements
                    int alive = 0;
                    if (grid->data[i][j-1] == 1) { alive++; }
                    if (grid->data[i][j+1] == 1) { alive++; }
                    if (grid->data[i+1][j-1] == 1) { alive++; }
                    if (grid->data[i+1][j] == 1) { alive++; }
                    if (grid->data[i+1][j+1] == 1) { alive++; }
                    bool new_state = grid_state(&grid->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                }
            } else if (i == grid->rows - 1) {
                //check for bottom row
                if (j == 0) {
                    //check for bottom left element
                    int alive = 0;
                    if (grid->data[i][j+1] == 1) { alive++; }
                    if (grid->data[i-1][j] == 1) { alive++; }
                    if (grid->data[i-1][j+1] == 1) { alive++; }
                    bool new_state = grid_state(&grid->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                } else if (j == grid->cols -1) {
                    //check for bottom right element
                    int alive = 0;
                    if (grid->data[i][j-1] == 1) { alive++; }
                    if (grid->data[i-1][j] == 1) { alive++; }
                    if (grid->data[i-1][j-1] == 1) { alive++; }
                    bool new_state = grid_state(&grid->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                } else {
                    //check for bottom middle elements
                    int alive = 0;
                    if (grid->data[i][j+1] == 1) { alive++; }
                    if (grid->data[i][j-1] == 1) { alive++; }
                    if (grid->data[i-1][j-1] == 1) { alive++; }
                    if (grid->data[i-1][j] == 1) { alive++; }
                    if (grid->data[i-1][j+1] == 1) { alive++; }
                    bool new_state = grid_state(&grid->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                }
            } else {
                //checking for middle rows
                if (j == 0) {
                    //check for middle left element
                    int alive = 0;
                    if (grid->data[i][j+1] == 1) { alive++; }
                    if (grid->data[i-1][j] == 1) { alive++; }
                    if (grid->data[i-1][j+1] == 1) { alive++; }
                    if (grid->data[i+1][j] == 1) { alive++; }
                    if (grid->data[i+1][j+1] == 1) { alive++; }
                    bool new_state = grid_state(&grid->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                } else if (j == grid->cols - 1) {
                    //check for middle right element
                    int alive = 0;
                    if (grid->data[i][j-1] == 1) { alive++; }
                    if (grid->data[i-1][j] == 1) { alive++; }
                    if (grid->data[i-1][j-1] == 1) { alive++; }
                    if (grid->data[i+1][j] == 1) { alive++; }
                    if (grid->data[i+1][j-1] == 1) { alive++; }
                    bool new_state = grid_state(&grid->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                } else {
                    //check for middle middle elements
                    int alive = 0;
                    if (grid->data[i][j+1] == 1) { alive++; }
                    if (grid->data[i][j-1] == 1) { alive++; }
                    if (grid->data[i-1][j-1] == 1) { alive++; }
                    if (grid->data[i-1][j] == 1) { alive++; }
                    if (grid->data[i-1][j+1] == 1) { alive++; }
                    if (grid->data[i+1][j-1] == 1) { alive++; }
                    if (grid->data[i+1][j] == 1) { alive++; }
                    if (grid->data[i+1][j+1] == 1) { alive++; }
                    bool new_state = grid_state(&grid->data[i][j], &alive);
                    new_grid.data[i][j] = new_state;
                }
            }
        }
    }
    grid_free(grid);
    grid->data = new_grid.data;
}
