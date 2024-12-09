#ifndef GRID_H
#define GRID_H


typedef struct {
    int** data;
    int rows;
    int cols;
} grid;

grid grid_init(int rows, int cols);
void grid_free(grid* matrix);
int grid_set(grid* matrix, int x, int y);
void grid_show(grid* matrix);
int grid_state(int*  state, int* alive);
int grid_next(grid* matrix);
int grid_num_alive(grid* matrix);

#endif
