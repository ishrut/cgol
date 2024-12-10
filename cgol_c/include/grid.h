#ifndef GRID_H
#define GRID_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    bool** data;
    int rows;
    int cols;
} Grid;

//allocates memory for a grid
Grid grid_init(int rows, int cols);
//frees the allocated memory for the grid
void grid_free(Grid* matrix);
//sets the coordinates at x and y to be true or alive,
//returns 1 if success and 0 if failure
int grid_set(Grid* grid, int x, int y);
//prints to the console the grid
void grid_show(Grid* grid);
//computes the next state of the grid,
void grid_next(Grid* matrix);
//gives the total number of alive cells.
int grid_num_alive(Grid* grid);

#endif
