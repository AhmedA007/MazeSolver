# Maze Solver

Maze Solver is a C++ program that generates random mazes and allows the player to navigate through them using 'w', 'a', 's', 'd' keys. It measures the time taken to solve the maze and maintains a scoreboard of the fastest times. After completion, a shortest path or solution is shown using Dijkstra's and BFS algorithm.

## Table of Contents

- [Maze Solver](#maze-solver)
  - [Table of Contents](#table-of-contents)
  - [Header File: `project.h`](#header-file-projecth)
  - [Main File: `main.cpp`](#main-file-maincpp)
  - [Usage](#usage)
  - [Citations](#citations)
  - [Authors](#authors)

## Header File: `project.h`

`project.h` contains the core data structures and methods used for generating, solving, and visualizing mazes. It defines the `MazeSolver` class, which includes the following features:

- Generation of random mazes with customizable difficulty levels: easy, hard, and expert.
- A shortest path finder based on breadth-first search (BFS).
- A method for moving through the maze interactively.
- Maze solving with visualization of the shortest path using '*' markers.
- The ability to change maze sizes and generate different mazes.
- Integration with a time measurement function to record and display the time taken to complete the maze.
- Integration with a scoreboard for recording the fastest times.

## Main File: `main.cpp`

The `main.cpp` file is responsible for executing the maze solver game. It provides a user interface for starting the game and utilizes the `MazeSolver` class defined in `project.h`. Here's an overview of what this file does:

- It starts the game when the user is ready by generating a random maze.
- It measures the time taken by the player to complete the maze.
- It records the player's time in a scoreboard file and compares it with the fastest times.
- It provides feedback to the player about their performance, such as whether they set a new record or tied with the fastest time.

The main file uses a combination of C++ standard libraries and user-defined functions to implement the game logic and interact with the `MazeSolver` class.

## Usage

1. Clone the repository
2. Compile and run the program using a C++ compiler.
3. When prompted, enter 'R' or 'r' to start the game.
4. Use 'w', 'a', 's', and 'd' keys to navigate through the maze.
5. Enter 'D' or 'd' when you have completed the maze.
6. The program will display your time and compare it to the fastest times recorded in the scoreboard.

## Citations


1. Timer using Chrono Library: [cplusplus.com forum](https://cplusplus.com/forum/beginner/280938/)
2. Dijkstra's and BFS algorithm: Cracking the Coding Interview by Gayle Laakmann McDowell
3. Color Coded Terminal Output: [Stack Overflow](https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c)

Feel free to customize the game, such as changing maze sizes or adding more features, to suit your preferences.

Enjoy playing and solving mazes with Maze Solver!

## Authors

* **Ahmed Amir** - *Comp Sci Student* - [Ahmed Amir](https://github.com/AhmedA007/) 
