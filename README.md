# 3D Heat Conduction Solver (Gauss-Seidel Method)

##  Project Overview
This numerical methods project computes the steady-state temperature distribution across a three-dimensional slab. It utilizes the Gauss-Seidel iterative technique to solve the governing 3D heat conduction equations. The program is written entirely in C, demonstrating proficiency in implementing complex mathematical algorithms, grid-based calculations, and iterative convergence loops without relying on high-level numerical libraries.

##  Core Features
* **Numerical Analysis:** Implements the Gauss-Seidel method for solving linear systems of equations derived from physical heat transfer principles.
* **3D Grid Computation:** Iterates through a three-dimensional spatial grid to update nodal temperatures until a specified convergence tolerance is met.
* **C Programming Logic:** Utilizes multi-dimensional arrays, nested loops, and memory-efficient data types for fast execution.

## 🛠️ Tech Stack & Tools
* **Language:** C
* **Development Environment:** Visual Studio Code
* **Compiler:** MinGW-w64 (GCC)

##  Compilation & Execution
To compile and run this solver locally, open your terminal and run:

```bash
gcc [YOUR_FILE_NAME].c -o heat_solver
./heat_solver
