# Raylib Bubbles

[![CodeFactor](https://www.codefactor.io/repository/github/magnetrwn/raylib-bubbles/badge)](https://www.codefactor.io/repository/github/magnetrwn/raylib-bubbles) [![DeepSource](https://app.deepsource.com/gh/magnetrwn/raylib-bubbles.svg/?label=active+issues&show_trend=true&token=k0LxdMtn2JdcCFcNwl_0DyZp)](https://app.deepsource.com/gh/magnetrwn/raylib-bubbles/) [![DeepSource](https://app.deepsource.com/gh/magnetrwn/raylib-bubbles.svg/?label=resolved+issues&show_trend=true&token=k0LxdMtn2JdcCFcNwl_0DyZp)](https://app.deepsource.com/gh/magnetrwn/raylib-bubbles/) [![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fmagnetrwn%2Fraylib-bubbles&count_bg=%239757D0&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=hits&edge_flat=false)](https://hits.seeyoufarm.com)

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

The game is structured in a way that allows for easy modification and extension.

The following libraries are used in the project:

+ **[Raylib](https://www.raylib.com/)**: Graphics and input.
+ **[inipp.h](https://github.com/mcmtroffaes/inipp)**: Configuration file parsing (header-only).

To summarize the structure of the project, here is a short description of each header file, pretty much top to bottom:

+ **`include/window.hpp`**: Manages the window and contains the Raylib game loop. **This is the only header that interacts with Raylib, all others are independent and repurposable.**
+ **`include/action.hpp`**: Acts as a list for animations to be applied concurrently and detached to the game state, while keeping track of their action state and referencing the board.
+ **`include/game.hpp`**: **TODO**
+ **`include/board.hpp`**: Provides a way to build an hexagonal grid of bubbles and to manipulate it through a straightforward API.
+ **`include/util.hpp`**: Contains static utilities.

An extended description of each building block of the game can be found in the [Technical Summary](#technical-summary) section.

### Build Details

The `build` folder contains all files to bundle with the compiled executable. After running `./build.sh`, which will run `cmake` among things, the executable will be placed alongside resources and files to include with it:

+ `res/`: Contains the fonts and textures used in the game.
+ `bubbles`: The compiled executable.
+ `bubbles.ini`: The configuration file for the game.
+ `INSTRUCTIONS.md`: A file containing instructions on how to play the game.
+ `LICENSE`: The license file for the game, same as the project license.

As mentioned earlier, there will also be a zipped build generated in the root project directory, with the name `bubbles_build[timestamp].zip`. It contains all necessary files to run the game.

**Note:** The build resources such as fonts and textures may fall under a different license, please check the related folders for license information.

## Technical Summary

The project is written in C++11 and, while it uses Raylib for rendering graphics, the API has not been mixed in an inseparable manner with the game logic. You will find **all uses of Raylib are located in the `GameWindow` class**, in `include/window.hpp`. It is purposefully not difficult to replace Raylib with another library, or to use the game logic in a different context.

### [Board](include/board.hpp)

The `GameBoard` class in `include/board.hpp` provides an interface to conveniently access elements of an hexagonal grid through offset coordinates, as in a rectangular grid with a slight right shift on each odd row.

Specifically, the class first allocates a 1D array of `Bubble` objects, which are accessed by internally calculating offsets to the required element.

As in bubble shooter games usually are, when a board with an even number of columns is generated, each odd row will have one less `Bubble` than the even rows. This is internally accounted for, and optimal space allocation and cache locality should be possible.

On changing the state of some cell on the board, the `GameBoard` class will automatically update the number of neighbors of the bubble cell with non-empty bubble color.

Neighbor counting allows efficient popping of bubbles, since the game only checks if a launched bubble that just attached to the board has made the number of neighbors of a bubble reach the minimum for a possible pop, if the color is matching.

### [Bubble](include/board.hpp)

Available as a public member of `GameBoard`, the `BubbleCell` class is a simple container for bubble color (including empty space) and tracking the number of neighbors with non-empty bubble color. It provides operators to generate self-documenting code, but should not be used outside of the `GameBoard` abstraction.

### [Action](include/action.hpp)

An action is something that takes place on the window with bubbles, but is not snapped to the board grid. This is essential to allow effects and animations to be displayed.

The `GameActionMgr` class in `include/action.hpp` handles a queue of actions, which are applied consecutively. Each action has a state, and the queue is abstracted to be processed in the game loop transparently. The state of each action is stepped on every cycle, and eventually *pruned* when the action has left the visible screen area, or `pruneFlag` is raised. The action is removed from the queue when it is done.

More specifically, the queue is made up of `ActionType` objects, which identify each action through an enum class, while keeping track of their parent manager and allowing to check their state, as well as their board location.

There is also a basic container struct `BubbleData`, which holds the state (coordinates, speed and hue) of a bubble during the animation.

**Note:** The `GameActionMgr` uses a `std::forward_list` to keep track of actions instead of a `std::vector`, because the game loop will cause the manager to iterate over the list and occasionally prune actions. Also, it makes it straightforward by using `std::forward_list::remove_if` with a lambda.

**TODO**
