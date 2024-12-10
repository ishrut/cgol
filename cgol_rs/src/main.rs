use ratatui::crossterm::event::{self, KeyCode, KeyEventKind};
mod grid;
use grid::Grid;

fn main() -> std::io::Result<()> {
    let mut terminal = ratatui::init();
    terminal.clear()?;

    //initialising the grid
    let tui_size = terminal.size()?;
    let tui_rows = tui_size.width;
    let tui_cols = tui_size.height;
    let mut grid = Grid::new(tui_rows.into(), tui_cols.into());
    //setting initial states
    grid.set(vec![
        (4, 2), 
        (4, 3),
        (4, 4), 
        (3, 4),
        (2, 3),
    ]);

    loop {
        terminal.draw(|frame| {
            frame.render_widget( &grid, frame.area());
        })?;

        if let event::Event::Key(key) = event::read()? {
            if key.kind == KeyEventKind::Press && key.code == KeyCode::Right {
                grid.next();
            } else {
                break;
            }
        }
    }

    ratatui::restore();
    Ok(())
}
