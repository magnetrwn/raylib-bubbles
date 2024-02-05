# Raylib Bubbles

## Description

**Raylib Bubbles** is a compact puzzle game following the classic bubble shooter game concept. It relies on the [Raylib](https://www.raylib.com/) library for rendering and input handling.

## Quick Start

To get started, follow these steps:

+ Clone the repository with `git clone https://github.com/magnetrwn/raylib-bubbles.git`.
+ Install Raylib, which can be done on Debian by running `sudo apt install raylib`.
+ Build with `./build.sh`, and check the `build` directory for the executable, or the zipped build `bubbles_build[timestamp].zip`.
+ Run `./bubbles` to start the game.

For instructions on how to play, see the [instructions file](build/INSTRUCTIONS.md) in the build folder.

## Files

To summarize the operation of the project, here is a short description of each header file, pretty much top to bottom:

+ `include/window.hpp`: Manages the window and contains the Raylib game loop.
+ `include/action.hpp`: Acts as a queue for animations to be applied consecutively, while keeping track of their state.
+ `include/game.hpp`: **TODO**
+ `include/board.hpp`: Provides a way to build an hexagonal grid of bubbles and to manipulate it through a straightforward API.
+ `include/util.hpp`: Contains static utilities.

## Building

The `build` folder contains all files to bundle with the compiled executable. After running `./build.sh`, which will run `cmake` among things, the executable will be placed alongside resources and files to include with it:

+ `res/`: Contains the fonts and textures used in the game.
+ `INSTRUCTIONS.md`: A file containing instructions on how to play the game.

## Technical Summary

The project is written in C++14 and, while it uses Raylib for rendering graphics, the API has not been mixed in an inseparable manner with the game logic. You will find most uses of Raylib in the `GameWindow` class, in `include/window.hpp`. It is purposefully not difficult to replace Raylib with another library, or to use the game logic in a different context.

**TODO**
