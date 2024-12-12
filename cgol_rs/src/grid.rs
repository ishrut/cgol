use ratatui::style::{Style, Stylize};
use ratatui::widgets::Widget;

#[derive(Debug, Clone)]
pub struct Grid {
    data: Vec<Vec<bool>>,
    rows: usize,
    cols: usize,
}

impl Grid {
    pub fn new(rows: usize, cols: usize) -> Self {
        let data = vec![vec![false; cols]; rows];
        Self { data, rows, cols }
    }

    pub fn show(&self) {
        for i in 0..self.rows {
            for j in 0..self.cols {
                match self.data[i][j] {
                    true => print!("#"),
                    false => print!(" "),
                }
            }
            print!("\n")
        }
    }

    pub fn set(&mut self, indices: Vec<(usize, usize)>) {
        for item in indices {
            if item.0 > self.rows && item.1 > self.cols {
                panic!("provided indices out of bounds")
            } else {
                self.data[item.0][item.1] = true;
            }
        }
    }

    pub fn alive_count(&self) -> usize {
        let mut alive = 0;
        for i in 0..self.rows {
            for j in 0..self.cols {
                if self.data[i][j] == true {
                    alive += 1;
                }
            }
        }
        alive
    }
    
    fn get_alive(data: Vec<&bool>) -> usize {
        let mut alive = 0;
        for item in data {
            if *item == true {
                alive += 1;
            }
        }
        alive
    }

    fn get_new_state(state: &bool, alive: usize) -> bool {
        if *state == true {
            if alive < 2 {
                return false
            } else if alive == 2 || alive == 3 {
                return true
            } else {
                return false
            }
        } else {
            if alive == 3 {
                return true
            } else {
                return *state
            }
        }
    }
}

impl Iterator for Grid {
    type Item = Self;
    fn next(&mut self) -> Option<Self> {
        let mut new_grid = Self::new(self.rows, self.cols);
        for i in 0..self.rows {
            for j in 0..self.cols {
                //check for neighbours
                if i == 0 {
                    //check for top row
                    if j == 0 {
                        //check top left element
                        let alive = Self::get_alive(vec![
                            &self.data[i][j+1],
                            &self.data[i+1][j],
                            &self.data[i+1][j+1],
                        ]);
                        let new_state = Self::get_new_state(&self.data[i][j], alive);
                        new_grid.data[i][j] = new_state;
                    } else if j == self.cols - 1 {
                        //check for top right element
                        let alive = Self::get_alive(vec![
                            &self.data[i][j-1],
                            &self.data[i+1][j],
                            &self.data[i+1][j-1],
                        ]);
                        let new_state = Self::get_new_state(&self.data[i][j], alive);
                        new_grid.data[i][j] = new_state;
                    } else {
                        //check for top middle elements
                        let alive = Self::get_alive(vec![
                            &self.data[i][j-1],
                            &self.data[i][j+1],
                            &self.data[i+1][j-1],
                            &self.data[i+1][j],
                            &self.data[i+1][j+1],
                        ]);
                        let new_state = Self::get_new_state(&self.data[i][j], alive);
                        new_grid.data[i][j] = new_state;
                    }
                } else if i == self.rows - 1 {
                    //check for bottom row
                    if j == 0 {
                        //check for bottom left element
                        let alive = Self::get_alive(vec![
                            &self.data[i][j+1],
                            &self.data[i-1][j],
                            &self.data[i-1][j+1],
                        ]);
                        let new_state = Self::get_new_state(&self.data[i][j], alive);
                        new_grid.data[i][j] = new_state;
                    } else if j == self.cols -1 {
                        //check for bottom right element
                        let alive = Self::get_alive(vec![
                            &self.data[i][j-1],
                            &self.data[i-1][j],
                            &self.data[i-1][j-1],
                        ]);
                        let new_state = Self::get_new_state(&self.data[i][j], alive);
                        new_grid.data[i][j] = new_state;
                    } else {
                        //check for bottom middle elements
                        let alive = Self::get_alive(vec![
                            &self.data[i][j+1],
                            &self.data[i][j-1],
                            &self.data[i-1][j-1],
                            &self.data[i-1][j],
                            &self.data[i-1][j+1],
                        ]);
                        let new_state = Self::get_new_state(&self.data[i][j], alive);
                        new_grid.data[i][j] = new_state;
                    }
                } else {
                    //checking for middle rows
                    if j == 0 {
                        //check for middle left element
                        let alive = Self::get_alive(vec![
                            &self.data[i][j+1],
                            &self.data[i-1][j],
                            &self.data[i-1][j+1],
                            &self.data[i+1][j],
                            &self.data[i+1][j+1],
                        ]);
                        let new_state = Self::get_new_state(&self.data[i][j], alive);
                        new_grid.data[i][j] = new_state;
                    } else if j == self.cols - 1 {
                        //check for middle right element
                        let alive = Self::get_alive(vec![
                            &self.data[i][j-1],
                            &self.data[i-1][j],
                            &self.data[i-1][j-1],
                            &self.data[i+1][j],
                            &self.data[i+1][j-1],
                        ]);
                        let new_state = Self::get_new_state(&self.data[i][j], alive);
                        new_grid.data[i][j] = new_state;
                    } else {
                        //check for middle middle elements
                        let alive = Self::get_alive(vec![
                            &self.data[i][j+1],
                            &self.data[i][j-1],
                            &self.data[i-1][j-1],
                            &self.data[i-1][j],
                            &self.data[i-1][j+1],
                            &self.data[i+1][j-1],
                            &self.data[i+1][j],
                            &self.data[i+1][j+1],
                        ]);
                        let new_state = Self::get_new_state(&self.data[i][j], alive);
                        new_grid.data[i][j] = new_state;
                    }
                }
            }
        }
        *self = new_grid;       
        Some(self.clone())
    } 
}

impl Widget for &Grid {
    fn render(self, _area: ratatui::prelude::Rect, buf: &mut ratatui::prelude::Buffer) {
        for i in 0..self.rows as u16 {
            for j in 0..self.cols as u16 {
                if self.data[i as usize][j as usize] == true {
                    buf.set_string(i, j, "#", Style::new().green());
                } else {
                    buf.set_string(i, j, " ", Style::new());
                }
            }
        }
    }
}
