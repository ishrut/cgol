#define TB_IMPL
#include "../include/termbox2.h"
#include "../include/grid.h"

void tui_print(Grid* matrix);

int main() {
    struct tb_event ev;
    tb_init();
    int tui_rows = tb_width();
    int tui_cols = tb_height();

    Grid grid = grid_init(tui_rows, tui_cols);
    //set initial states for the grid
    grid_set(&grid, 4, 2);
    grid_set(&grid, 4, 3);
    grid_set(&grid, 4, 4);
    grid_set(&grid, 3, 4);
    grid_set(&grid, 2, 3);

    tui_print(&grid);
    while (1) {
        tb_poll_event(&ev);
        if (ev.key == 65514) {
            grid_next(&grid);
            tui_print(&grid);
        } else {
            break;
        }
    }

    tb_shutdown();
    grid_free(&grid);

    return 0;
}

void tui_print(Grid* grid) {
    tb_clear();
    for (int i=0; i<grid->rows; i++) {
        for (int j=0; j<grid->cols; j++) {
            if (grid->data[i][j] == 1) {
                tb_printf(i, j, TB_GREEN, 0, "#");
            } else {
                tb_printf(i, j, 0, 0, " ");
            }
        }
    }
    tb_present();
}
