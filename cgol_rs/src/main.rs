use crossterm::{
    event::{DisableMouseCapture, EnableMouseCapture, Event, MouseEventKind},
    terminal::{disable_raw_mode, enable_raw_mode, EnterAlternateScreen, LeaveAlternateScreen},
    ExecutableCommand,
};
use ratatui::{
    backend::CrosstermBackend,
    crossterm::event::{self, KeyCode, KeyEventKind},
    Terminal,
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
    let mut grid = Grid::new(tui_size.width.into(), tui_size.height.into());

    let mut app_state = AppState::Set;
    loop {
        terminal.draw(|frame| {
            frame.render_widget(&grid, frame.area());
        })?;

        let new_event = event::read()?;

        if let AppState::Set = app_state {
            handle_set_events(new_event, &mut grid, &mut app_state);
        } else {
            if let None = handle_next_events(new_event, &mut grid) {
                break;
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

fn handle_set_events(event: Event, grid: &mut Grid, app_state: &mut AppState) {
    if let event::Event::Mouse(mouse) = event {
        if let MouseEventKind::Down(button) = mouse.kind {
            if let event::MouseButton::Left = button {
                grid.set(vec![(mouse.column as usize, mouse.row as usize)])
            }
        }
    } else if let event::Event::Key(key) = event {
        if key.kind == KeyEventKind::Press && key.code == KeyCode::Enter {
            *app_state = AppState::Next;
        }
    }
}

fn handle_next_events(event: Event, grid: &mut Grid) -> Option<()> {
    if let event::Event::Key(key) = event {
        if key.kind == KeyEventKind::Press && key.code == KeyCode::Right {
            grid.next();
        } else {
            return None;
        }
    }
    Some(())
}
