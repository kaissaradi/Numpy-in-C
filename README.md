# NumPy in C

This project is a simplified implementation of a multidimensional array library in C, inspired by NumPy. The goal is to provide a learning experience for implementing core functionalities of array operations and memory management in C, with a focus on type safety and basic parallelization using OpenMP.

## Project Structure

The project is organized as follows:

```plaintext
numpy-in-c/
├── src/                  # Source files
│   ├── main.c            # Main entry point
│   ├── array.c           # Core array functions and operations
│   └── memory.c          # Memory management and error handling
├── include/              # Header files
│   ├── array.h           # Core array structure and operations
│   └── memory.h          # Memory management and error handling
├── tests/                # Unit tests
│   └── test_array.c      # Tests for core array functions
├── examples/             # Example usage
│   └── example_basic.c   # Basic usage examples
├── Makefile              # Makefile for building the project
├── .gitignore            # Git ignore file
├── LICENSE               # License file
└── README.md             # Project README file
```

## Features

- **Core Array Functions**: Create and manipulate multidimensional arrays.
- **Array Operations**: Perform element-wise addition and multiplication.
- **Memory Management**: Efficient memory management with custom memory pools.
- **Parallel Processing**: Use OpenMP for parallelized array operations.

## Getting Started

### Prerequisites

- C compiler (e.g., GCC)
- OpenMP (optional, for parallel operations)

### Building the Project

You can build the project using the provided Makefile.

#### Using Makefile

1. Build the project:
    ```sh
    make
    ```

2. Run the executable:
    ```sh
    ./main
    ```

3. Clean the build:
    ```sh
    make clean
    ```

## Example Usage

The project includes an example usage file `example_basic.c` to demonstrate how to use the array library.

### Running the Example

1. Ensure the project is built by running `make`.
2. Run the example:
    ```sh
    ./main
    ```

The example will:
- Create two arrays `a` and `b` with the shape {2, 3}.
- Initialize the arrays with sample data.
- Perform element-wise addition and multiplication.
- Print the results of the operations.

### Example Output

You should see output similar to the following:

```
Array a:
[0.000000, 1.000000, 2.000000]
[3.000000, 4.000000, 5.000000]

Array b:
[0.000000, 2.000000, 4.000000]
[6.000000, 8.000000, 10.000000]

Result of addition:
[0.000000, 3.000000, 6.000000]
[9.000000, 12.000000, 15.000000]

Result of multiplication:
[0.000000, 2.000000, 8.000000]
[18.000000, 32.000000, 50.000000]
```

## Learning Objectives

- Understand the basics of creating and managing multidimensional arrays in C.
- Learn to implement core array operations with type safety.
- Gain experience with memory management techniques to improve performance.
- Explore parallelization with OpenMP to optimize array operations.

Feel free to explore and modify the code to deepen your understanding of these concepts. If you encounter any issues or have questions, please don't hesitate to ask!
