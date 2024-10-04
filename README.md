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

Build the project:

```sh
make
```

Run the executable:

```sh
./main
```

Clean the build:

```sh
make clean
```

## Example Usage

The project includes an example usage file `example_basic.c` to demonstrate how to use the array library.

### Running the Example

Ensure the project is built by running `make`.

Run the example:

```sh
./main
```

The example will:
- Create two arrays `a` and `b` with the shape {3, 4}.
- Initialize the arrays with sample data.
- Perform element-wise addition and multiplication.
- Print the results of the operations.

### Example Output

You should see output similar to the following:

```
==================================================
 Multidimensional Array Operations in C
==================================================
--------------------------------------------------
Creating memory pool of size 240 bytes...
Memory pool created successfully.
--------------------------------------------------
Allocating and initializing array 0...
Array 0 allocated and initialized successfully.
Allocating and initializing array 1...
Array 1 allocated and initialized successfully.
Allocating and initializing array 2...
Array 2 allocated and initialized successfully.
Arrays allocated and initialized successfully.
--------------------------------------------------
Initializing arrays with custom functions...
Arrays initialized successfully.
--------------------------------------------------
Array A:
     1.00      2.00      3.00      4.00 
     5.00      6.00      7.00      8.00 
     9.00     10.00     11.00     12.00 

Array B:
     0.00      2.00      4.00      6.00 
     8.00     10.00     12.00     14.00 
    16.00     18.00     20.00     22.00 
--------------------------------------------------
Performing array addition...
Array addition performed successfully.
--------------------------------------------------
Result of A + B:
     1.00      4.00      7.00     10.00 
    13.00     16.00     19.00     22.00 
    25.00     28.00     31.00     34.00 
--------------------------------------------------
Performing array multiplication...
Array multiplication performed successfully.
--------------------------------------------------
Result of A * B:
     0.00      4.00     12.00     24.00 
    40.00     60.00     84.00    112.00 
   144.00    180.00    220.00    264.00 
--------------------------------------------------
Cleaning up...
Cleanup completed successfully.
==================================================
 Program completed successfully.
==================================================
```

## Testing

### Running Tests

Ensure the project is built by running `make`.

Compile the tests:

```sh
gcc -o tests/test_array tests/test_array.c src/array.c src/memory.c -Iinclude -fopenmp
```

Run the tests:

```sh
./tests/test_array
```

### Test Output

You should see output similar to the following:

```
test_create_array (1D): PASSED (1D array - Size: 5, Dimensions: 1)
test_create_array (2D): PASSED (2D array - Size: 6, Dimensions: 2)
test_create_invalid_array (NULL shape): PASSED (Invalid array creation (NULL shape))
test_add_arrays: PASSED (Addition result array - Size: 6)
test_add_invalid_arrays: PASSED (Addition with invalid dimensions)
test_multiply_arrays: PASSED (Multiplication result array - Size: 6)
test_multiply_invalid_arrays: PASSED (Multiplication with invalid dimensions)
test_memory_pool: PASSED (Memory pool - Blocks allocated: Yes, Yes)
test_memory_pool_exceed: PASSED (Memory pool exceed - Blocks allocated: Yes, Yes, No)
```

## Learning Objectives

- Understand the basics of creating and managing multidimensional arrays in C.
- Learn to implement core array operations with type safety.
- Gain experience with memory management techniques to improve performance.
- Explore parallelization with OpenMP to optimize array operations.

## Contributing

Contributions are welcome! Please fork the repository, make changes, and submit a pull request.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgments

- **NumPy**: The inspiration for this project comes from the NumPy library.
- **OpenMP**: The parallelization functionality is implemented using OpenMP.

## Conclusion

Thank you for visiting this project! I hope you find it helpful in your learning journey.
```