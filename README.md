# Reverse Game of Life - SAT Solver

## Description

This project implements a solution to the Reverse Game of Life problem using a MaxSAT solver. The goal is to determine a previous configuration of a Game of Life grid that evolves into a given current state, while minimizing the number of alive cells in the previous configuration. The project leverages SAT-based techniques and optimization algorithms to efficiently solve the problem for small grids.

## Prerequisites

- C Compiler (e.g., GCC)
- MaxSAT Solver (Open-WBO or equivalent)

## Installation

1. Clone this repository:

```
git clone https://github.com/yourusername/reverse-game-of-life.git
cd reverse-game-of-life
```

2. Install Open-WBO or your preferred MaxSAT solver and ensure it is accessible in your PATH.

3. Build the project and Open-WBO:

```
./compila-tudo.sh
```

## Usage

### Input Format

- The input is a text file containing the number of rows and columns of the grid, followed by the current grid configuration.

- Each cell is represented as 1 (alive) or 0 (dead).

Example for a 4x4 grid:

```
4 4
0 1 0 1
1 0 1 0
0 1 0 1
1 0 1 0
```

### Running the Program

- Prepare the input file with the current grid state.

- Run the program to generate the SAT file:

```
./reverse_game_of_life input.txt
```

- The program will output the previous grid configuration that minimizes the number of alive cells.

### Example Workflow

Input Grid:

```
4 6
0 0 0 0 0 0
0 0 1 1 0 0
0 0 0 1 1 0
0 0 0 0 0 0
```

Output Previous Configuration:

```
4 6
0 0 0 0 0 0
0 0 1 1 0 0
0 0 0 1 0 0
0 0 0 1 0 0
```

## Code Structure

- `main.c`: The entry point of the application.
  
- `helper.c`: Helper functions for SAT encoding.
  
- `helper.h`: Header file for helper functions.
  
- `compila-tudo.sh`: Script to compile both the project and Open-WBO.
  
- `README.md`: Documentation for the project.

## Limitations

- The project is designed for grids up to 20x20 due to computational constraints.

- Requires manual setup of the MaxSAT solver and handling of intermediate files.

- Execution of the SAT Solver is limited to 280 seconds and 8GB of memory. If it exceeds these limits, the last solution found will be printed.
