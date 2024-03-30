# Traveling Salesman Problem Solver

This C++ program implements three algorithms to solve the Traveling Salesman Problem (TSP): Nearest Neighbor, 2-Opt Swap, and Lattice Annealing.

## Table of Contents

- [Introduction](#introduction)
- [Usage](#usage)
- [Algorithms Used](#algorithms-used)
- [Code Structure](#code-structure)
- [Input File Format](#input-file-format)
- [Example Output](#example-output)

## Introduction

The Traveling Salesman Problem (TSP) is a classic problem in computer science and optimization. Given a set of cities and the distances between them, the goal is to find the shortest possible route that visits each city exactly once and returns to the starting city.

This program demonstrates three different algorithms to solve the TSP and provides an example of how to use them.

## Usage

1. Ensure you have a graph file named `size10.graph` in the same directory as the executable. The graph file should contain the distances between cities.
2. Compile the program using a C++ compiler. For example:

   g++ -o tsp_solver tsp_solver.cpp
   
3. Run the compiled executable:
   
   ./tsp_solver


## Algorithms Used

### Nearest Neighbor Algorithm

The Nearest Neighbor algorithm starts at a random city and repeatedly visits the nearest unvisited city until all cities are visited. This heuristic provides a quick initial solution but may not always be optimal.

### 2-Opt Swap Algorithm

The 2-Opt Swap algorithm attempts to improve the initial solution by iteratively swapping pairs of edges in the path if it results in a shorter total distance. This process continues until no further improvements can be made.

### Lattice Annealing Algorithm

The Lattice Annealing algorithm is a variant of simulated annealing that randomly swaps pairs of edges based on a temperature parameter. As the temperature decreases, the likelihood of accepting swaps that increase the total distance decreases, leading to a more optimal solution.

## Code Structure

- `main()`: Entry point of the program. Reads the graph from the file, initializes the initial solution, and applies the three algorithms sequentially.
- `nearestNeighbor()`: Implements the Nearest Neighbor algorithm to generate an initial solution.
- `twoOptSwap()`: Implements the 2-Opt Swap algorithm to improve the initial solution.
- `latticeAnnealing()`: Implements the Lattice Annealing algorithm to further optimize the solution.
- `Solution` struct: Stores the path and cost of a solution.

## Input File Format

The input graph file (`size10.graph` in this case) should follow a specific format where each line represents the distances between cities. For an N-city problem, the file should have N lines, and each line should contain N space-separated integers representing the distances from the corresponding city to all other cities.

## Example Output

After running the program, it will output the optimized path, optimized cost, and the time taken to find the solution in milliseconds.

Optimized path: 0 1 2 3 4 5 6 7 8 9 0
Optimized cost: 1234
Time taken: 500 milliseconds



Adjust the parameters and algorithms as needed for different problem sizes and optimization requirements.

Feel free to modify the code, input files, and parameters to suit your specific TSP instances and optimization goals.





