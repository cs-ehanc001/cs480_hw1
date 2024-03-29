# Square Puzzle Solver

## Build Instructions

This project is tested using GCC 11, using libstdc++-11.
Older versions of GCC *will* fail to build the project.

```sh
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel 4
```
The name of the resulting executable is `square_puzzle_solver`.

If desired, unit tests can be run with the command: `cmake --build . --target test`

## Usage

Search type is specified with the flags "bfs", "dfs", or "ucs".
Depth-first search is implemented with a maximum search depth of 20 nodes, with the root node considered depth 0.
Uniform-cost search is implemented using the h1 metric, which is minimizing the number of misplaced tiles.
Position of arguments does matter. Malformed arguments will be diagnosed, and a help message will be presented.

```
./square_puzzle_solver --bfs [path to input file]
./square_puzzle_solver --dfs [path to input file]
./square_puzzle_solver --ucs [path to input file]
```

## Input File Specification

The input file must contain an initial board state in the following form:

- Numbers on tiles represented in hexadecimal (1, 2, 3, ..., D, E, F)
- Empty space represented with '_'
- Whitespace is ignored
- Extension is not enforced

A sample file, `./inputs/asst.dat` encodes the initial state provided in the assignment PDF.
