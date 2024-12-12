#define TB_IMPL
#include "../include/termbox2.h"
#include "../include/grid.h"

void tui_print(Grid* matrix);

int main() {
    struct tb_event ev;
    tb_init();
    tb_set_input_mode(TB_INPUT_MOUSE);
    int tui_rows = tb_width();
    int tui_cols = tb_height();

    Grid grid = grid_init(tui_rows, tui_cols);
    tui_print(&grid);

    //gets input from mouse and sets the initial values of the grid
    while (1) {
        tb_poll_event(&ev);
        if (ev.key == TB_KEY_ENTER) {
            break;
        }
        grid_set(&grid, ev.x, ev.y);
        tui_print(&grid);
    }

    //calculates the next values of the grid
    while (1) {
        tb_poll_event(&ev);
        if (ev.key == TB_KEY_ARROW_RIGHT) {
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
                tb_set_cell(i, j, '#', TB_GREEN, 0);
            } else {
                tb_set_cell(i, j, ' ', 0, 0);
            }
        }
    }
    tb_present();
}
