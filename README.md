# Raylib Bubbles

**TODO: gif here**

## Description

**Raylib Bubbles** is a compact puzzle game following the classic bubble shooter game concept. It relies on the [Raylib](https://www.raylib.com/) library for rendering and input handling.

The game is written in C++11 and is built with CMake. It is intended to be a **well structured example of a game written with Raylib**.

### Quick Start

+ [Installation](#installation)
+ [Overview](#overview)
+ [Build Details](#build-details)
+ [Technical Summary](#technical-summary)

### Installation

To get started, follow these steps:

+ Clone the repository with `git clone https://github.com/magnetrwn/raylib-bubbles.git`.
+ Install Raylib, which can be done on Debian by running `sudo apt install raylib`.
+ Build with `./build.sh`, and check the `build` directory for the executable, or the zipped build `bubbles_build[timestamp].zip`.
+ Run `./bubbles` to start the game.

For instructions on how to play, see the [instructions file](build/INSTRUCTIONS.md) in the build folder.

### Overview

To summarize the structure of the project, here is a short description of each header file, pretty much top to bottom:

+ `include/window.hpp`: Manages the window and contains the Raylib game loop.
+ `include/action.hpp`: Acts as a queue for animations to be applied consecutively, while keeping track of their state.
+ `include/game.hpp`: **TODO**
+ `include/board.hpp`: Provides a way to build an hexagonal grid of bubbles and to manipulate it through a straightforward API.
+ `include/util.hpp`: Contains static utilities.

An extended description of each building block of the game can be found in the [Technical Summary](#technical-summary) section.

### Build Details

The `build` folder contains all files to bundle with the compiled executable. After running `./build.sh`, which will run `cmake` among things, the executable will be placed alongside resources and files to include with it:

+ `res/`: Contains the fonts and textures used in the game.
+ `INSTRUCTIONS.md`: A file containing instructions on how to play the game.

As mentioned earlier, there will also be a zipped build generated in the root project directory, with the name `bubbles_build[timestamp].zip`. It contains all necessary files to run the game.

## Technical Summary

The project is written in C++11 and, while it uses Raylib for rendering graphics, the API has not been mixed in an inseparable manner with the game logic. You will find most uses of Raylib in the `GameWindow` class, in `include/window.hpp`. It is purposefully not difficult to replace Raylib with another library, or to use the game logic in a different context.

### Board

The `GameBoard` class in `include/board.hpp` provides an interface to conveniently access elements of an hexagonal grid through offset coordinates, as in a rectangular grid with a slight right shift on each odd row.

Specifically, the class first allocates a 1D array of `Bubble` objects, which are accessed by internally calculating offsets to the required element.

As in bubble shooter games usually are, when a board with an even number of columns is generated, each odd row will have one less `Bubble` than the even rows. This is internally accounted for, and optimal space allocation and cache locality should be possible.

On changing the state of some cell on the board, the `GameBoard` class will automatically update the number of neighbors of the bubble cell with non-empty bubble color.

Neighbor counting allows efficient popping of bubbles, since the game only checks if a launched bubble that just attached to the board has made the number of neighbors of a bubble reach the minimum for a possible pop, if the color is matching.

If this sounds confusing, looking at [the source code](include/board.hpp) could be more straightforward.

### Bubble

Available as a public member of `GameBoard`, the `Bubble` class is a simple container for bubble color (including empty space) and tracking the number of neighbors with non-empty bubble color. It provides operators to generate self-documenting code, but should not be used outside of the `GameBoard` abstraction.

### Action

An action is something that takes place on the window with bubbles, but is not snapped to the board grid. This is essential to allow effects and animations to be displayed.

The `GameActionMgr` class in `include/action.hpp` handles a queue of actions, which are applied consecutively. Each action has a state, and the queue is abstracted to be processed in the game loop transparently. The state of each action is stepped on every cycle, and eventually *pruned* when the action has left the relevant screen area. The action is removed from the queue when it is done.

More specifically, the queue is made up of `ActionType` objects, which identify each action through an enum class. A possible improvement might be to specialize the ActionType class to only contain necessary struct variables and alter the `step()` method properly through variant visiting, but not in C++11 of course.

There is also a basic container struct `BubbleData`, which holds the state (coordinates, speed and hue) of a bubble during the animation.

**TODO**
