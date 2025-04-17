# Fermat-Weber Location Problem Solver

The Fermat-Weber problem seeks to determine the optimal location of facilities (or a single facility) that minimizes the total transportation cost or distance to a set of given points. This has applications in facility location, logistics, urban planning, and network design.

## Prerequisites

- CMake (version 3.10 or higher)
- Gurobi Optimizer (with valid license)
- C++

## Build the sources

1. Clone:

```sh 
git clone https://github.com/lnhutnam/fermat-weber-cpp.git
cd fermat-weber-cpp
```

2. Build with gcc:

```sh 
cmake -B build 
cmake --build build 
```

3. Run 

```sh 
./fermat-weber <instance_type> <model_type>
```
- <instance_type>: Problem instance to solve
  - 1: First predefined problem instance
  - 2: Second predefined problem instance
  - 3: Third predefined problem instance
- <model_type>: Optimization model to use
  - 1: Original model
  - 2: Maculan model

Predefined problems instances:
- Problem 1: A specific configuration with defined coordinates and edges
- Problem 2: Another configuration with different coordinate and edge setup
- Problem 3: A minimal configuration with no predefined edges

Model variations:
- Original Model: Focuses on direct distance minimization. Suitable for simpler facility location scenarios
- Maculan Model: More complex formulation. Provides additional constraints and flexibility. Better for scenarios with multiple facility types
