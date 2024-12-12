use ratatui::{
    crossterm::event::{self, KeyCode, KeyEventKind}, 
    backend::CrosstermBackend, Terminal
};
use crossterm::{
    event::{DisableMouseCapture, EnableMouseCapture, MouseEventKind}, 
    terminal::{disable_raw_mode, enable_raw_mode, EnterAlternateScreen, LeaveAlternateScreen}, 
    ExecutableCommand
};
mod grid;
use grid::Grid;

enum AppState {
    Set,
    Next,
}

fn main() -> std::io::Result<()> {
    enable_raw_mode()?;
    std::io::stdout().execute(EnterAlternateScreen)?;
    std::io::stdout().execute(EnableMouseCapture)?; 
    let backend = CrosstermBackend::new(std::io::stdout());
    let mut terminal = Terminal::new(backend)?;
    terminal.clear()?;

    //initialising the grid
    let tui_size = terminal.size()?;
    let tui_rows = tui_size.width;
    let tui_cols = tui_size.height;
    let mut grid = Grid::new(tui_rows.into(), tui_cols.into());

    let mut app_state = AppState::Set;
    loop {
        terminal.draw(|frame| {
            frame.render_widget( &grid, frame.area());
        })?;

        let new_event = event::read()?;

        match app_state {
            AppState::Set => {
                match new_event {
                    event::Event::Mouse(mouse) => {
                        match mouse.kind {
                            MouseEventKind::Down(button) => {
                                match button {
                                    event::MouseButton::Left => {
                                        grid.set(vec![(mouse.column as usize, mouse.row as usize)])
                                    }
                                    _ => {}
                                }
                            }
                            _ => {}
                        }
                    }
                    event::Event::Key(key) => {
                        if key.kind == KeyEventKind::Press && key.code == KeyCode::Enter {
                            app_state = AppState::Next;
                        }
                    }
                    _ => {}
                }
            },
            AppState::Next => {
                match new_event {
                    event::Event::Key(key) => {
                        if key.kind == KeyEventKind::Press && key.code == KeyCode::Right {
                            grid.next();
                        } else {
                            break;
                        }
                    }
                    _ => {}
                }

            }
        }
    }

    std::io::stdout().execute(DisableMouseCapture)?;
    std::io::stdout().execute(LeaveAlternateScreen)?;
    disable_raw_mode()?;
    terminal.show_cursor()?;
    ratatui::restore();
    Ok(())
}
