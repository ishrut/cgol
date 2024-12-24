# Conway's Game of Life - Rust vs C
---

## Overview
A very simple tui app is made using John Conway's game of life algorithm in C and rust.
The purpose of this project is to compare the look and feel of each of those languages.
The algorithm implemented in both languages are the same, although I tried to do it in the language's 'way of doing things'.
The tui allows setting of initial states and then generate the next frames.
In rust the ratatui crate was used and in C termbox2.h was used.
In this way, I can compare the work done to solve the same problem in both languages including using external libraries.

## Usage
Build the binaries and then run.
Start by setting the initial states using your mouse to click on the screen.
Then press Enter to validate the initial state.
Right arrow to advance to next frame and any other key to exit.
!!Be careful when pressing other keys when setting initial states as it might cause unexpected behaviours as only the cases above are handled.

## Key Takeaways
* The rust binary is bigger than the C binary, most likely due to no shared libraries in rust.
* I used the same bounds checking algorithm for both code. There are more elegant solutions to it though.
* It was much quicker and easier to code in C.
* However, at my level it would be naive to say I don't have skill issues so I don't know if I am blowing my foot off and where.
* The complexity of the rust code was largely due to ratatui's crate and needing the crossterm backend.
* I also used the iterator trait so that I can make use of rust features. It is not the optimal solution here.
* It was easier to code the core algorithm in rust but I have been coding in rust for a longer time.
* Ratatui is clearly has much more features than termbox2.h justifying the complexity of the crate's usage.
* The ease of C was due to the simplicity of the termbox2.h library as compared to rust's ratatui.
* C just looks much more gorgeous than rust. Personal opinion.
