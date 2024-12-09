#define TB_IMPL
#include "termbox2.h.lib"
#include "grid.h"

void tui_print(grid* matrix) {
    tb_clear();
    for (int i=0; i<matrix->rows; i++) {
        for (int j=0; j<matrix->cols; j++) {
            if (matrix->data[i][j] == 1) {
                tb_printf(i, j, TB_GREEN, 0, "#");
            } else {
                tb_printf(i, j, 0, 0, " ");
            }
        }
    }
    tb_present();
}

int main() {
    struct tb_event ev;
    tb_init();
    int tui_rows = tb_width();
    int tui_cols = tb_height();

    grid matrix = grid_init(tui_rows, tui_cols);
    grid_set(&matrix, 4, 2);
    grid_set(&matrix, 4, 3);
    grid_set(&matrix, 4, 4);
    grid_set(&matrix, 3, 4);
    grid_set(&matrix, 2, 3);

    tui_print(&matrix);
    while (1) {
        tb_poll_event(&ev);
        if (ev.key == 65514) {
            grid_next(&matrix);
            tui_print(&matrix);
        } else {
            break;
        }
    }

    tb_shutdown();
    grid_free(&matrix);

    return 0;
}
